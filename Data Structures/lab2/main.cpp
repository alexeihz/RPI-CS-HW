//File main.cpp

#include <algorithm>
#include <iostream>
#include "time.h"
#include <vector>

int main(){
	Time time1(12,0,0);
	Time time2;
	Time time3(14,5,4);

	//std::cout << time1.getHour() << ":" << time1.getMin() << ":" << time1.getSec() << std::endl;
	//std::cout << time2.getHour() << ":" << time2.getMin() << ":" << time2.getSec() << std::endl;
	time1.PrintAmPm();
	time2.PrintAmPm();
	time3.PrintAmPm();
	
	std::vector<Time> times;
	times.push_back(time1);
	times.push_back(time2);
	times.push_back(time3);
	
	std::sort(times.begin(), times.end(), IsEarlierThan);
	
	for(unsigned int i=0; i<times.size();i++){
		times[i].PrintAmPm();
	}
}