#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm(const string&name_,int t_cs_,list<Process>ps,int t_slice_, float alpha_, double lambda_){
  name=name_;
  bursts=0;
  totalBurstTime=0;
  totalWaitTime=0;
  contextSwitches=0;
  preemptions=0;
  waits=0;
  t_cs=t_cs_;
  cpuUsed=false;
  switching=false;
  turnaroundTime=0;
  processes=ps;
  t_slice=t_slice_;
  alpha = alpha_;
  lambda = lambda_;
  rr_add="END";
  remainingProcesses=ps.size();
}

void Algorithm::addBurst(int burstTime){

  totalBurstTime+=burstTime;
  turnaroundTime+=burstTime;
  bursts++;
}
void Algorithm::addArrived(int elapsed){
  list<Process>::iterator it=processes.begin();
  //loop through processes that arrived at elapsed time and add to queue
  while(it!=processes.end() && elapsed==it->getArrival()){
    addToQueue(processes.front(),elapsed);
    if(elapsed<=999){
        cout<< "time "<<elapsed<<"ms: Process "<< processes.front().getName();
        if (name == "SJF" || name == "SRT") cout << " (tau " << processes.front().getTau() << "ms)";
        cout << " arrived; placed on ready queue ";
      printqueue();
    }
    it=processes.erase(processes.begin());

  }
}
void Algorithm::startCPUburst(int elapsed){
  Process p=switchIn;

  assert(!cpuUsed);
  int waitend=elapsed-(int)t_cs/2;
  p.endWait(waitend);
  turnaroundTime+=p.getWaitTime();
  addWait(p.getWaitTime());
  inCPU=p;
  cpuUsed=true;
  if(elapsed<=999){
    printStartCPUburst(elapsed);
  }
}
void Algorithm::endCPUburst(){
  assert(cpuUsed);
  addBurst(inCPU.getCPUBurstTime());
  inCPU.finishCPUBurst();
}
//add what was in CPU to iolist and re-sort list
void Algorithm::startIO(){
  assert(inCPU.getTotalCPUBursts()>0);
  ioList.push_back(inCPU);
  ioList.sort(OrderByIOtime);
}
//remove all processes that finished io at elapsed time from io ioList
//add them to the queue
void Algorithm::finishIO(int elapsed, int cpuburst){
  while(!ioList.empty() && ioList.front().getIOBurstTime()==0){

    ioList.front().finishIOBurst();
    addToQueue(ioList.front(),elapsed);

    if ( name == "SRT" && !isCPUEmpty() && ioList.front().getTau() < getinCPU().getTau() - cpuburst ) {
        addPreemption();
        inCPU.preempt(cpuburst);

        // save next process in queue to be switched in
        switching = true;
        switchIn = ioList.front();
        // startSwitching();
        
        if ( elapsed<=999 ) {
            cout << "time " << elapsed << "ms: Process " << ioList.front().getName() 
            << " (tau " << ioList.front().getTau() << "ms)" 
            << " completed I/O; preempting " << getinCPU().getName() << " ";
        }
    }
    else if ( elapsed<=999 ) {
        cout << "time "<<elapsed<<"ms: Process "<< ioList.front().getName(); 
        if (name == "SJF" || name == "SRT") cout << " (tau " << ioList.front().getTau() << "ms)";
        cout <<" completed I/O; placed on ready queue ";
    }

    ioList.pop_front();
    if ( elapsed<=999 ) printqueue();
  }
}

void Algorithm::preempt(int elapsed){
  assert(cpuUsed);

  totalBurstTime+=t_slice;
  turnaroundTime+=t_slice;
  if(!isQueueEmpty()){
    inCPU.preempt(t_slice);

    addPreemption();
    if(elapsed<=999){

        cout<<"time "<<elapsed<<"ms: Time slice expired; process " <<inCPU.getName(); 
        if (name == "SJF" || name == "SRT") cout << " (tau " << inCPU.getTau() << "ms)";
        cout << " preempted with "<<inCPU.getCPUBurstTime() <<"ms to go ";
      printqueue();
    }
  }else{
    inCPU.decrementCPUTime(t_slice);
  }

}
bool Algorithm::clearCPU(int elapsed){
  cpuUsed=false;
  if(inCPU.getTotalCPUBursts()==0){
    remainingProcesses--;
    return false;
  }
  if(inCPU.wasPreempted()){
    addToQueue(inCPU, elapsed);
  }
  return !inCPU.wasPreempted();
}
void Algorithm::startSwitching(){
  //cout<<totalWaitTime<<endl;
  switching=true;
  //save next process in queue to be switched in
  if(!queue.empty()){
    switchIn=queue.front();
  }
}
void Algorithm::printStartCPUburst(int elapsed)const{
    cout<<"time "<<elapsed<<"ms: Process "<< inCPU.getName(); 
    if (name == "SJF" || name == "SRT") cout << " (tau " << inCPU.getTau() << "ms)";
    cout << " started using the CPU ";
    if(inCPU.wasPreempted() || name == "SRT"){
        cout << "with "<<inCPU.getCPUBurstTime()<<"ms burst remaining ";
    }
  else{

    cout<<"for "<<inCPU.getCPUBurstTime()<<"ms burst ";
  }
  printqueue();
}
//print reports after a cpu burst is finished
void Algorithm::printfinishBurst(int elapsed, int oldTau)const {
    //if finished last burst
    if(inCPU.getTotalCPUBursts()==0){
        cout<< "time "<<elapsed<<"ms: Process "<<inCPU.getName() << " terminated ";
        printqueue();
    }
    else if (elapsed<=999) {
        cout<< "time "<<elapsed<<"ms: Process "<<inCPU.getName(); 
        if (name == "SJF" || name == "SRT") cout << " (tau " << oldTau << "ms)";
        cout <<" completed a CPU burst; "<<inCPU.getTotalCPUBursts();
        if(inCPU.getTotalCPUBursts()==1){cout<<" burst to go ";}
        else{cout<<" bursts to go ";}
        printqueue();

        // time 67ms: Recalculated tau (78ms) for process A [Q <empty>]
        if (name == "SJF" || name == "SRT") {
            cout<< "time "<< elapsed << "ms: Recalculated tau (" << inCPU.getTau() 
            << "ms) for process " << inCPU.getName() << " ";
            printqueue();
        }

        cout<< "time "<<elapsed<<"ms: Process "<<inCPU.getName();
        cout <<" switching out of CPU; will block on I/O until time "
        <<elapsed+inCPU.getIOBurstTime()+(int)t_cs/2<<"ms ";
        printqueue();
    }
}
void Algorithm::printqueue()const{
  cout<<"[Q";
  if(queue.empty()){
    cout<< " <empty>]"<<endl;
  }
  else{
   for (list<Process>::const_iterator it=queue.begin();it!=queue.end();it++){
     cout<<" "<<it->getName();
   }
   cout<<"]"<<endl;
  }
}
void Algorithm::printStats()const {
  ofstream ostr;
  ostr.open("simout.txt",fstream::out| fstream::app);
  ostr<<"Algorithm "<<name<<endl;
  float avgcpu=(float)totalBurstTime/bursts;
  ostr<<fixed;
  ostr<<"-- average CPU burst time: "<<setprecision(3)<<avgcpu<<" ms"<<endl;

  float avgwait=(float)totalWaitTime/(bursts);
  ostr<<"-- average wait time: "<<setprecision(3)<<avgwait<<" ms"<<endl;
  float avgturnaround=(float)(turnaroundTime+(bursts+preemptions)*t_cs)/bursts;
  ostr<<"-- average turnaround time: "<<setprecision(3)<<avgturnaround<<" ms"<<endl;
  ostr<<"-- total number of context switches: "<<contextSwitches<<endl;
  ostr<<"-- total number of preemptions: "<<preemptions<<endl;
  float cpuTime=100*(float)totalBurstTime/totaltime;
  ostr<<"-- CPU utilization: "<<setprecision(3)<<cpuTime<<"%"<<endl;
  ostr.close();
  // cout<<"bursts: "<<bursts<<endl;
  // cout<<"waits: "<<waits<<endl;
  // cout<<"totalBurstTime: "<<totalBurstTime<<endl;
  // cout<<"totalWaitTime: "<<totalWaitTime<<endl;
}
void Algorithm::addToQueue(Process p,int elapsed){
    if(rr_add=="END"){
        queue.push_back(p);
        queue.back().startWait(elapsed);
    }
    else{
        if(p.wasPreempted()){
          queue.push_back(p);
          queue.back().startWait(elapsed);
        }
        else{
          queue.push_front(p);
          queue.front().startWait(elapsed);
        }
    }
    if (name == "SRT" || name == "SJF") sortQueueByTau();
}
