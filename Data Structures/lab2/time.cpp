//File Time.cpp

#include <algorithm>
#include <iostream>
#include "time.h"

const int HoursInDay = 24;
const int MinsInHour = 60;
const int SecsInMin = 60;

Time::Time(){
	hours = 0;
	minutes = 0;
	seconds = 0;
}

Time::Time(int hour, int min, int sec){
	hours = hour;
	minutes = min;
	seconds = sec;
}

int Time::getHour() const{
	return hours;
}

int Time::getMin() const{
	return minutes;
}

int Time::getSec() const{
	return seconds;
}

void Time::setHour(int h) {
	hours = h;
}

void Time::setMin(int m) {
	minutes = m;
}

void Time::setSec(int s) {
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