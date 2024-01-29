#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Process.h"
using namespace std;

void Process::printInfo()const {
  cout<<"Process "<< name<<endl;
  cout<<"\tarrival: "<<arrival<<endl;
  cout<<"\tCPU bursts : "<<bursts<<endl;
  cout<<"\tburst times("<<cpuTimes.size()<<"): ";
  for(unsigned int i=0;i< cpuTimes.size();i++){

    cout<<cpuTimes[i];
    if(i!=cpuTimes.size()-1){
      cout<<", ";
    }
  }
  cout<<endl;
  cout<<"\tI/O times("<<ioTimes.size()<<"): ";
  for(unsigned int i=0;i< ioTimes.size();i++){
    cout<<ioTimes[i];
    if(i!=ioTimes.size()-1){
      cout<<", ";
    }
  }
  cout<<endl;
}
//order so process with lowest arrival time is first
bool OrderByArrival(const Process&p1, const Process& p2){
  return (p1.getArrival()<p2.getArrival())||
  (p1.getArrival()==p2.getArrival() &&p1.getName()<p2.getName());
}
//order so process with lowest remaining io time is first
bool OrderByIOtime(const Process&p1, const Process& p2){
  return (p1.getIOBurstTime()<p2.getIOBurstTime())||
  (p1.getIOBurstTime()==p2.getIOBurstTime() &&p1.getName()<p2.getName());
}
//order so process with lowest predicted cpu time (tau) is first
bool OrderByTau(const Process&p1, const Process& p2) {
  return ( p1.getTau()<p2.getTau() ) ||
  ( p1.getTau() == p2.getTau() && p1.getName()<p2.getName() );
}
