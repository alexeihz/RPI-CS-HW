#ifndef Process_H
#define Process_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
using namespace std;

class Process{
public:
  Process(){waitTime=0;preempted=false;}
  Process(const char& n){name=n;waitTime=0;preempted=false;}
  int getArrival()const{return arrival;}
  int getTotalCPUBursts() const {return bursts;}
  const char& getName() const {return name;}
  int getCPUBurstTime()const{return cpuTimes[0];}
  int getIOBurstTime()const{return ioTimes[0];}
  int getWaitTime()const{return waitTime;}
  bool wasPreempted()const{return preempted;}
  void setArrival(int a){arrival=a;}
  void setCPUbursts(int b){bursts=b;}
  void addCPUTime(int time){cpuTimes.push_back(time);}
  void addIOTime(int time){ioTimes.push_back(time);}
  void startWait(int start){ 
  startwait=start;}
  void endWait(int end){
    waitTime=end-startwait;}
  void finishCPUBurst(){
    preempted=false;
    bursts--;
    cpuTimes.erase(cpuTimes.begin());
  }
  void finishIOBurst(){
    preempted=false;
    ioTimes.erase(ioTimes.begin());
  }
  void decrementIO(){ioTimes[0]--;}
  void decrementCPUTime(int time){  cpuTimes[0]-=time;}
  void preempt(int t_slice){
    assert(cpuTimes[0]>t_slice);
    decrementCPUTime(t_slice);
    preempted=true;
  }
  void printInfo()const ;

    int getTau() const {return tau;}
    void setTau(float lambda) { tau = ceil( 1/lambda ); }
    void updateTau(int t, float alpha) { tau = ceil( (alpha * t) + ((1 - alpha) * tau )); }

private:
    int arrival;
    int bursts;
    int tau;
    char name;
    bool preempted;
    vector<int> cpuTimes;
    vector<int> ioTimes;
    int waitTime;
    int startwait;
};

bool OrderByArrival(const Process&p1, const Process& p2);
bool OrderByIOtime(const Process&p1, const Process& p2);
bool OrderByTau(const Process&p1, const Process& p2);



#endif
