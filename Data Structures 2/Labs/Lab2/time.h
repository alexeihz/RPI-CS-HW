class Time {
public:
	Time();
	Time(int hour, int min, int sec);
	// ACCESSORS
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	
	// MODIFIERS
	void setHour(int hour);
	void setMinute(int min);
	void setSecond(int sec);
	void PrintAMPM();
	
	private: // REPRESENTATION (member variables)
	int hours;
	int minutes;
	int seconds;
};

bool IsEarlierThan(const Time& t1, const Time& t2);