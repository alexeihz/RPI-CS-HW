#include <string>
#include "ship.h"

Ship::Ship(string name, int length){
	type = name;
	len = length;
	horizontal = true;
}
int Ship::getLength(){
	return len;
}	
string Ship::getType(){
	return type;
}
bool Ship::isHorizontal(){
	return horizontal;
}
void Ship::setHorizontal(){
	if(horizontal == false){
		horizontal = true;
	}
	else{
		horizontal = false;
	}
}