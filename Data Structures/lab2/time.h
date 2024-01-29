class Time {
public:
	Time();
	Time(int hour, int min, int sec);
	// ACCESSORS
	int getHour() const;
	int getMin() const;
	int getSec() const;
	
	// MODIFIERS
	void setHour(int hour);
	void setMin(int min);
	void setSec(int sec);
	void PrintAmPm();
	
	private: // REPRESENTATION (member variables)
	int hours;
	int minutes;
	int seconds;
};

bool IsEarlierThan(const Time& t1, const Time& t2);