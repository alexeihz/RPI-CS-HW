#include <iostream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <list>
#include <unistd.h>
#include "Algorithm.h"
using namespace std;
//char letter='A';

double next_exp(double lambda, int ub){
  double r=drand48();
  double x=-log(r)/lambda;
  while(x>ub){
    r=drand48();
    x=-log(r)/lambda;
  }
  return x;
}
//create and return vector of Process objects representing each process
list<Process> getProcesses(int n,int seed,double lambda,int ub, bool isUsingTau){
  list<Process> processes;
  char letter='A';
  srand48(seed);
  for(int i=0;i<n;i++){
    Process p(letter++);
    int arrival=floor(next_exp(lambda,ub));
    p.setArrival(arrival);
    int bursts=ceil(100*drand48());
    p.setCPUbursts(bursts);
    // set tau to be 1/lambda
    p.setTau(lambda);
    //get times for each cpu and io burst
    for (int j =0; j<bursts;j++){
      int cputime=ceil(next_exp(lambda,ub));
      p.addCPUTime(cputime);
      if(j<bursts-1){
        int iotime=10*ceil(next_exp(lambda,ub));
        p.addIOTime(iotime);
      }
    }
    #ifdef DEBUG_MODE
      p.printInfo();
    #endif
    processes.push_back(p);
    cout<<"Process "<<p.getName()
      <<" [NEW] (arrival time "<<p.getArrival()<<" ms) "
      <<p.getTotalCPUBursts();
      if(p.getTotalCPUBursts()==1){
        cout<<" CPU burst";
      }
      else{
        cout<<" CPU bursts";
      }
      if (isUsingTau) cout << " (tau " << p.getTau() << "ms)" << endl;
      else cout << endl;
  }
  return processes;
}




void FCFS(int t_cs,Algorithm & alg){

  int elapsed=0;
  int csCount=0;
  int cpuburst=0;
  cout<< "time "<<elapsed<<"ms: Simulator started for FCFS ";
  alg.printqueue();
  while(!alg.finishedSim()){

    //if process in cpu and not switching
    //(aka a process is still running its cpu burst)
    if(!alg.isCPUEmpty() && !alg.isSwitching()){
      cpuburst++;
      //if finished burst,start context switch
      if(cpuburst==alg.getinCPU().getCPUBurstTime()){
        alg.endCPUburst();

        alg.printfinishBurst(elapsed);

        alg.startSwitching();
        csCount=0;
        cpuburst=0;
      }

    }
    //if finished second half of context switching (switching in)
    if(alg.isSwitching() && csCount==t_cs && alg.isCPUEmpty()) {
      alg.addContextSwitch();
      //switch in to cpu
      alg.startCPUburst(elapsed);
      alg.stopSwitching();
      assert(alg.isCPUEmpty()==false);
      csCount=0;
      cpuburst=0;
    }
    //finish io bursts
    alg.finishIO(elapsed);

    //add all arrived process to queue
    alg.addArrived(elapsed);

    //if finished first half of context switching (switch out)
    if(alg.isSwitching() && csCount==(int)t_cs/2 && !alg.isCPUEmpty()){
      //switch out
      bool needsIO = alg.clearCPU(elapsed);

      //start io
      if(needsIO){

        alg.startIO();
      }
      //if nothing in queue, end context switch
      if(alg.isQueueEmpty()){
        alg.stopSwitching();
        csCount=0;
      }

    }
    //if cpu availible and there's a process in the queue
    //and not currently context switching or halfway done(need to switch int)
    // start switching
    if(alg.isCPUEmpty() && !alg.isQueueEmpty()&& (csCount==(int)t_cs/2 ||!alg.isSwitching())){
      alg.startSwitching();
      alg.popQueueFront();
      csCount=t_cs/2;
    }
    elapsed++;
    //if context switching,
    if(alg.isSwitching()){
      csCount++;
    }
    //decrement each io processes's remaining i/o time
    alg.decrementIO();
  }
  elapsed--;
  alg.addTotalTime(elapsed);
  cout<< "time "<<elapsed<<"ms: Simulator ended for FCFS ";
  alg.printqueue();

}


void RR(int t_cs,Algorithm & alg){
  int elapsed=0;
  int csCount=0;
  int cpuburst=0;
  cout<< "time "<<elapsed<<"ms: Simulator started for RR with time slice "
    <<alg.getTSlice()<<"ms and rr_add to "<<alg.getRRadd() <<" ";
  alg.printqueue();
  while(!alg.finishedSim()){

    //if process in cpu and not switching
    //(aka a process is still running its cpu burst)
    if(!alg.isCPUEmpty() && !alg.isSwitching()){
      cpuburst++;
      //if finished burst, start context switch
      if(cpuburst==alg.getinCPU().getCPUBurstTime()){
        alg.endCPUburst();

        alg.printfinishBurst(elapsed);

        alg.startSwitching();
        csCount=0;
        cpuburst=0;
      }
      //if time in cpu is up and processes are waiting,
      //preempt
      else if(!alg.isQueueEmpty()&&alg.getTSlice()==cpuburst){
        alg.preempt(elapsed);
        alg.startSwitching();
        csCount=0;
        cpuburst=0;
      }
      //if time in cpu is up queue is empty, dont actually preempt
      else if(alg.isQueueEmpty()&&alg.getTSlice()==cpuburst){
        if(elapsed<=999){
          cout<<"time "<<elapsed<<"ms: Time slice expired;"
          <<" no preemption because ready queue is empty ";

          alg.printqueue();
        }
        alg.preempt(elapsed);

        csCount=0;
        cpuburst=0;
      }

    }
    //if finished second half of context switching (switching in)
    if(alg.isSwitching() && csCount==t_cs && alg.isCPUEmpty()) {
      alg.addContextSwitch();
      //switch in to cpu
      alg.startCPUburst(elapsed);
      alg.stopSwitching();
      assert(alg.isCPUEmpty()==false);
      csCount=0;
      cpuburst=0;
    }
    //if finished first half of context switching (switch out)
    if(alg.isSwitching() && csCount==(int)t_cs/2 && !alg.isCPUEmpty()){
      //switch out, if preepted adds back to queue
      bool needsIO = alg.clearCPU(elapsed);

      //start io
      if (needsIO){
        alg.startIO();
      }

      //if nothing in queue, end context switch
      if(alg.isQueueEmpty()){
        alg.stopSwitching();
        csCount=0;
      }

    }
    //finish io bursts
    alg.finishIO(elapsed);

    //add all arrived process to queue
    alg.addArrived(elapsed);

    //if cpu availible and there's a process in the queue
    //and not currently context switching or halfway done(need to switch int)
    // start switching
    if(alg.isCPUEmpty() && !alg.isQueueEmpty()&& (csCount==(int)t_cs/2 ||!alg.isSwitching())){
      alg.startSwitching();
      alg.popQueueFront();
      csCount=(int)t_cs/2;
    }
    elapsed++;
    //if context switching,
    if(alg.isSwitching()){
      csCount++;
    }
    //decrement each io processes's remaining i/o time
    alg.decrementIO();
  }
  elapsed--;
  alg.addTotalTime(elapsed);
  cout<< "time "<<elapsed<<"ms: Simulator ended for RR ";
  alg.printqueue();

}

void SJF(int t_cs, Algorithm & alg) {

    int elapsed=0;
    int csCount=0;
    int cpuburst=0;

    cout << "time " << elapsed << "ms: Simulator started for SJF ";
    alg.printqueue();
    while ( !alg.finishedSim() ) {
      // if process in cpu and not switching
      // (aka a process is still running its cpu burst)
      if ( !alg.isCPUEmpty() && !alg.isSwitching() ) {
          cpuburst++;
          // if finished burst, start context switch
          if ( cpuburst == alg.getinCPU().getCPUBurstTime() ) {
              
              int burstTime = alg.getinCPU().getCPUBurstTime();
              int oldTau = alg.getinCPU().getTau();
              
              alg.endCPUburst();
              alg.getinCPU().updateTau(burstTime, alg.getAlpha());
              alg.printfinishBurst(elapsed, oldTau);
              alg.startSwitching();

              csCount=0;
              cpuburst=0;
          }
      }
      // if finished second half of context switching (switching in)
      if(alg.isSwitching() && csCount==t_cs && alg.isCPUEmpty()) {
        alg.addContextSwitch();
        //switch into cpu
        alg.startCPUburst(elapsed);
        alg.stopSwitching();
        assert(alg.isCPUEmpty()==false);
        csCount=0;
        cpuburst=0;
      }
      // finish io bursts
      alg.finishIO(elapsed);

      // add all arrived process to queue and sort by shortest cpu burst first
      alg.addArrived(elapsed);
      alg.sortQueueByTau(); 

      // if finished first half of context switching (switch out)
      if(alg.isSwitching() && csCount==(int)t_cs/2 && !alg.isCPUEmpty()){
        //switch out
        bool needsIO = alg.clearCPU(elapsed);

        //start io
        if ( needsIO ) {
          alg.startIO();
        }
        //if nothing in queue, end context switch
        if(alg.isQueueEmpty()){
          alg.stopSwitching();
          csCount=0;
        }

      }
      //if cpu availible and there's a process in the queue
      //and not currently context switching or halfway done(need to switch int)
      // start switching
      if(alg.isCPUEmpty() && !alg.isQueueEmpty()&& (csCount==(int)t_cs/2 ||!alg.isSwitching())){
        alg.startSwitching();
        alg.popQueueFront();
        csCount=t_cs/2;
      }
      elapsed++;
      //if context switching,
      if(alg.isSwitching()){
        csCount++;
      }
      //decrement each io processes's remaining i/o time
      alg.decrementIO();
    }
    elapsed--;
    alg.addTotalTime(elapsed);
    cout << "time " << elapsed << "ms: Simulator ended for SJF ";
    alg.printqueue();

}

void SRT(int t_cs, Algorithm & alg) {
    int elapsed = 0;
    int csCount = 0;
    int cpuburst = 0;

    cout << "time " << elapsed << "ms: Simulator started for SRT ";
    alg.printqueue();

    while ( !alg.finishedSim() ) {
      // if process in cpu and not switching
      // (aka a process is still running its cpu burst)
      if ( !alg.isCPUEmpty() && !alg.isSwitching() ) {
          cpuburst++;
          // if finished burst, start context switch
          if ( cpuburst == alg.getinCPU().getCPUBurstTime() ) {
              
              int burstTime = alg.getinCPU().getCPUBurstTime();
              int oldTau = alg.getinCPU().getTau();
              
              alg.endCPUburst();
              alg.getinCPU().updateTau(burstTime, alg.getAlpha());
              alg.printfinishBurst(elapsed, oldTau);
              alg.startSwitching();

              csCount=0;
              cpuburst=0;
          }
          
            // else if ( !alg.isQueueEmpty() && alg.getinQueue().getCPUBurstTime() < alg.getinCPU().getCPUBurstTime() - cpuburst ) {
            //     // time 31312ms: Process F (tau 659ms) completed I/O; preempting H [Q F]
            //     cout << "time " << elapsed << "ms: Process " << alg.getinQueue().getName() << " (tau " << alg.getinQueue().getTau() << "ms)" 
            //     << " completed I/O; preempting " << alg.getinCPU().getName();
            //     alg.printqueue();

            //     alg.preempt(elapsed);
            //     alg.startSwitching();
            //     csCount=0;
            //     cpuburst=0;
            // }
      }
      // if finished second half of context switching (switching in)
      if(alg.isSwitching() && csCount==t_cs && alg.isCPUEmpty()) {
        alg.addContextSwitch();
        //switch into cpu
        alg.startCPUburst(elapsed);
        alg.stopSwitching();
        assert(alg.isCPUEmpty()==false);
        csCount=0;
        cpuburst=0;
      }
      // finish io bursts and look for preemptions
      alg.finishIO(elapsed, cpuburst);

      // add all arrived process to queue and sort
      alg.addArrived( elapsed );
      alg.sortQueueByTau(); 

      // if finished first half of context switching (switch out)
      if(alg.isSwitching() && csCount==(int)t_cs/2 && !alg.isCPUEmpty()) {
        //switch out
        bool needsIO = alg.clearCPU(elapsed);

        //start io
        if ( needsIO ) {
          alg.startIO();
        }
        //if nothing in queue, end context switch
        if ( alg.isQueueEmpty() ) {
          alg.stopSwitching();
          csCount=0;
        }

      }
      //if cpu availible and there's a process in the queue
      //and not currently context switching or halfway done(need to switch int)
      // start switching
      if (alg.isCPUEmpty() && !alg.isQueueEmpty()&& (csCount==(int)t_cs/2 ||!alg.isSwitching())) {
        alg.startSwitching();
        alg.popQueueFront();
        csCount=t_cs/2;
      }
      elapsed++;
      //if context switching,
      if(alg.isSwitching()){
        csCount++;
      }
      //decrement each io processes's remaining i/o time
      alg.decrementIO();
    }
    elapsed--;
    alg.addTotalTime(elapsed);
    cout << "time " << elapsed << "ms: Simulator ended for SRT ";
    alg.printqueue();

}

int main(int argc, char const *argv[]) {
  if (argc<8 || argc>9){
    cerr<< "ERROR: Usage "<<argv[0]<<" number of processes, seed, lambda, upper bound, context switch time, alpha, t_slice [, rr_add]"<<endl;
    return 1;
  }
  int n =stoi(argv[1]);
  int seed=stoi(argv[2]);
  double lambda=stod(argv[3]);
  int ub=stoi(argv[4]);
  int t_cs=stoi(argv[5]);
  float alpha=stof(argv[6]);
  int t_slice=stoi(argv[7]);

  if (n<0 || n>26){
    cerr<< "ERROR: n "<<argv[1]<<" not between 0 and 26"<<endl;
    return 1;
  }
  if(seed<=0){
    cerr<< "ERROR: seed "<<argv[2]<<" not positive"<<endl;
    return 1;
  }
  if(lambda<0){
    cerr<< "ERROR: lambda "<<argv[3]<<" not positive"<<endl;
    return 1;
  }
  if(ub<=0){
    cerr<< "ERROR: upperbound "<<argv[4]<<" not positive"<<endl;
    return 1;
  }
  if (t_cs<0 || t_cs%2!=0){
    cerr<< "ERROR: context switch time "<<argv[5]<<" is not a positive even integer"<<endl;
    return 1;
  }
  if(alpha>=1 || alpha <0){
    cerr<< "ERROR: alpha "<<argv[6]<<" not between 0 and 1"<<endl;
    return 1;
  }
  if(t_slice<=0){
    cerr<< "ERROR: t_slice "<<argv[7]<<" not positive"<<endl;
    return 1;
  }
  string rr_add="END";
  if(argc==9){
    rr_add=argv[8];
    if ( rr_add!="BEGINNING" &&rr_add!="END"){
      cerr<<"ERROR: Invalid rr_add: "<<argv[8]<<", should be BEGINNING or END"<<endl;
      return 1;
    }
  }
  #ifdef DEBUG_MODE
    cout<<"n: "<<n<<endl;
    cout<<"seed: "<<seed<<endl;
    cout<<"lambda: "<<lambda<<endl;
    cout<<"ub: "<<ub<<endl;
    cout<<"t_cs: "<<t_cs<<endl;
    cout<<"alpha: "<<alpha<<endl;
    cout<<"t_slice: "<<t_slice<<endl;
    cout<<"rr_add: "<<rr_add<<endl;

    cout<<endl;
  #endif
  ofstream ostr;
  ostr.open("simout.txt",fstream::out| fstream::trunc);
  ostr.close();
  list<Process> processes=getProcesses(n,seed,lambda,ub, false);
  // list<Process> processes;
  // Process a(letter);
  // Process b(++letter);
  // b.setArrival(4);
  // a.setArrival(1);
  // a.setCPUbursts(1);
  // b.setCPUbursts(1);
  // a.addCPUTime(7);
  // b.addCPUTime(10);
  // processes.push_back(a);
  // processes.push_back(b);

    /* First Come First Served */
    processes.sort(OrderByArrival);
    Algorithm fcfs("FCFS",t_cs,processes,0);
    FCFS(t_cs,fcfs);
    cout<<endl;
    fcfs.printStats();

    /* Shortest Job First */
    processes=getProcesses(n,seed,lambda,ub, true);
    processes.sort(OrderByArrival);
    Algorithm sjf("SJF", t_cs, processes, 0, alpha, lambda);
    SJF(t_cs, sjf);
    cout<<endl;
    sjf.printStats();

    /* Shortest Remianing Time */
    processes=getProcesses(n,seed,lambda,ub, true);
    processes.sort(OrderByArrival);
    Algorithm srt("SRT", t_cs, processes, 0, alpha, lambda);
    SRT(t_cs, srt);
    cout<<endl;
    srt.printStats();

    /* Red Robin */
    processes=getProcesses(n,seed,lambda,ub, false);
    processes.sort(OrderByArrival);
    Algorithm rr("RR",t_cs,processes,t_slice);
    rr.addRRAdd(rr_add);
    RR(t_cs,rr);
    rr.printStats();

  return 0;
}
