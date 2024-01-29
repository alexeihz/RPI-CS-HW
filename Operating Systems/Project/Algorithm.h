#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <cassert>
#include "Process.h"
using namespace std;

class Algorithm{
public:
    Algorithm(const string&name_,int t_cs_,list<Process>ps,int t_slice_, float alpha_ = -1, double lambda_ = -1);
    //stat modifiers
    void addBurst(int burstTime);
    void addWait(int waitTime){
        totalWaitTime+=waitTime; waits++;
    }
    void addContextSwitch(){contextSwitches++;}
    void addPreemption(){preemptions++;}
    void addTotalTime(int elapsed){totaltime=elapsed;}
    void addRRAdd(const string&add){rr_add=add;}
    void addArrived(int elapsed);
    float getAlpha() const { return alpha; }
    Process& getinQueue() { return queue.front(); }

    //accesors
    unsigned int getRemainingProcesses()const {return processes.size();}
    int getTSlice()const{return t_slice;}
    Process& getinCPU(){assert(cpuUsed);return inCPU;}
    const string& getRRadd(){return rr_add;}
    bool isQueueEmpty(){return queue.empty();}
    bool isCPUEmpty()const {return !cpuUsed;}
    bool isSwitching()const{return switching;}

    void startCPUburst(int elapsed);
    void endCPUburst();

    void startIO();
    void finishIO(int elapsed, int cpuburst = 0);

    void preempt(int elapsed);

    void sortQueueByTau() { queue.sort(OrderByTau); }

    bool finishedSim(){return remainingProcesses==0;}
    //returns true if the process that was in the cpu finished its last CPU burst
    bool clearCPU(int elapsed);
    void startSwitching();
    void stopSwitching(){switching=false;}
    //loop through io list and decrement remaining time in io
    void decrementIO(){
        for (list<Process>::iterator it=ioList.begin();it!=ioList.end();it++){
        it->decrementIO();
        }
    }
    void popQueueFront(){

        queue.pop_front();
    }

    void printStartCPUburst(int elapsed)const;
    //print reports after a cpu burst is finished
    void printfinishBurst(int elapsed, int oldTau = 0) const;
    void printqueue()const;
    void printStats()const;
private:
    void addToQueue(Process p,int elapsed);
    string name;
    int bursts;
    int waits;
    int remainingProcesses;
    int totalBurstTime;
    int totalWaitTime;
    int turnaroundTime;
    int contextSwitches;
    int preemptions;
    int t_cs;
    float alpha;
    double lambda;
    string rr_add;
    int t_slice;
    int totaltime;
    list<Process> processes;
    list<Process> queue;
    list<Process> ioList;
    bool switching;
    bool cpuUsed;
    Process inCPU;
    Process switchIn;
};

#endif
