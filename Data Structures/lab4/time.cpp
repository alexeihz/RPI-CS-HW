//File Time.cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include "time.h"
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>

const uintptr_t HoursInDay = 24;
const uintptr_t MinsInHour = 60;
const uintptr_t SecsInMin = 60;

Time::Time(){
	hours = 0;
	minutes = 0;
	seconds = 0;
}

Time::Time(uintptr_t hour, uintptr_t min, uintptr_t sec){
	hours = hour;
	minutes = min;
	seconds = sec;
}

uintptr_t Time::getHour() const{
	return hours;
}

uintptr_t Time::getMin() const{
	return minutes;
}

uintptr_t Time::getSec() const{
	return seconds;
}

void Time::setHour(uintptr_t h) {
	hours = h;
}

void Time::setMin(uintptr_t m) {
	minutes = m;
}

void Time::setSec(uintptr_t s) {
	seconds = s;
}

bool IsEarlierThan(const Time& t1, const Time& t2){
	if(t1.getHour() < t2.getHour()){
		return true;
	}
	if(t1.getHour() == t2.getHour() && t1.getMin() < t2.getMin()) {
		return true;
	}
	if(t1.getHour() == t2.getHour() && t1.getMin() == t2.getMin() && t1.getSec() < t2.getSec()){
		return true;	
	}
	else{
		return false;
	}
}

void Time::PrintAmPm(){
	int twelve = 0;
	if (hours >= 12){
		if (hours != 12){
			twelve = 12;
		}
		if(minutes<10){
			if(seconds<10){
				std::cout << hours -twelve <<":0"<<minutes<<":0"<<seconds<< " pm"<< std::endl;
			}else{
				std::cout << hours -twelve <<":0"<<minutes<<":"<<seconds<< " pm"<< std::endl;
			}
		}else{
			if(seconds<10){
				std::cout << hours -twelve <<":"<<minutes<<":0"<<seconds<< " pm"<< std::endl;
			}else{
				std::cout << hours -twelve <<":"<<minutes<<":"<<seconds<< " pm"<< std::endl;
			}
		}
	}
	if (hours < 12){
		if(hours == 0){
			twelve = 12;
		}
		if(minutes<10){
			if(seconds<10){
				std::cout << hours + twelve <<":0"<<minutes<<":0"<<seconds<< " am"<< std::endl;
			}else{
				std::cout << hours+ twelve <<":0"<<minutes<<":"<<seconds<< " am"<< std::endl;
			}
		}else{
			if(seconds<10){
				std::cout << hours+ twelve <<":"<<minutes<<":0"<<seconds<< " am"<< std::endl;
			}else{
				std::cout << hours+ twelve <<":"<<minutes<<":"<<seconds<< " am"<< std::endl;
			}
		}
	}
}	