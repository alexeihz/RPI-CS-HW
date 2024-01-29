//ship.h
using namespace std;
#include <string>

#ifndef SHIP_H__
#define SHIP_H__

class Ship{
	public:
		Ship(string name, int length);
		int getLength();
		string getType();
		bool isHorizontal();
		void setHorizontal();
		
	private:
		bool horizontal;
		string type;
		int len;

};
#endif