#include <cstdio>
#include <algorithm>
#include <iostream>

#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>

class Time {
public:
	Time();
	Time(uintptr_t hour, uintptr_t min, uintptr_t sec);
	// ACCESSORS
	uintptr_t getHour() const;
	uintptr_t getMin() const;
	uintptr_t getSec() const;
	
	// MODIFIERS
	void setHour(uintptr_t hour);
	void setMin(uintptr_t min);
	void setSec(uintptr_t sec);
	void PrintAmPm();
	
	private: // REPRESENTATION (member variables)
	uintptr_t hours;
	uintptr_t minutes;
	uintptr_t seconds;
};

bool IsEarlierThan(const Time& t1, const Time& t2);