#include <algorithm>
#include <iostream>
#include "classes.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;

//constructor
Classes::Classes(std::string courseID, std::string department, std::string code, std::string title, std::string classDays, std::string getStartTime, std::string endTime, std::string classRoom){
	this -> ID = courseID;
	this -> dept = department;
	this -> courseCode = code;
	this -> courseTitle = title;
	this -> days = classDays;
	this -> start = getStartTime;
	this -> end = endTime;
	this -> room = classRoom;
}

std::string Classes::getID() const{
	return ID;
}
std::string Classes::getDept() const{
	return dept;
}
std::string Classes::getCourseCode() const{
	return courseCode;
}
std::string Classes::getCourseTitle() const{
	return courseTitle;
}
std::string Classes::getDays() const{
	return days;
}
std::string Classes::getStartTime() const{
	return start;
}
std::string Classes::getEndTime() const{
	return end;
}
std::string Classes::getRoom() const{
	return room;
}

//takes in two different classes and returns the correct class according to the sorting outlined in the homework pdf
Classes sortRoom(Classes classA, Classes classB){
	//a vector of strings so I can use it to determine what days of the week come first
	std::vector<std::string> days {"Monday","Tuesday","Wednesday","Thursday","Friday"};
	std::vector<std::string>::iterator itr;
	std::vector<std::string>::iterator itr2;
	itr = find(days.begin(),days.end(), classA.getDays());
	itr2 = find(days.begin(), days.end(), classB.getDays());
	//if classA starts earlier in the week than classB, return classA and vice versa.
	//goes into another if statement if both classes are on the same day
	if(itr < itr2){
		return classA;
	}
	if(itr > itr2){
		return classB;
	}
	if(itr == itr2){
		//if classA starts in the AM and classB starts in the PM, return classA and vice versa
		//goes into another if statement if both classes start in the AM or PM
		//getStartTime().size()-2 is the 'A' in "AM" or the 'P' in "PM"
		if(classA.getStartTime()[classA.getStartTime().size()-2] < classB.getStartTime()[classB.getStartTime().size()-2]){
			return classA;
		}
		if(classA.getStartTime()[classA.getStartTime().size()-2] > classB.getStartTime()[classB.getStartTime().size()-2]){
			return classB;
		}
		if(classA.getStartTime()[classA.getStartTime().size()-2] == classB.getStartTime()[classB.getStartTime().size()-2]){
			//if classA starts at least 1 hour before classB, return classA and vice versa
			//goes into another if statement if both classes start within the same hour 
			std::string timeA = classA.getStartTime().substr(0,2);
			std::string timeB = classB.getStartTime().substr(0,2);
			int timeNumA = std::stoi(timeA);
			int timeNumB = std::stoi(timeB);
			if(timeNumA == 12 && timeNumA > timeNumB){
				return classA;				
			}
			if(timeNumB == 12 && timeNumA < timeNumB){
				return classB;				
			}
			if(timeNumA < timeNumB){
				return classA;
			}
			if(timeNumA > timeNumB){
				return classB;
			}
			if(timeNumA == timeNumB){
				//if classA starts at least 10 minutes before classB, return classA and vice versa
				//anthing less than 10 minute intervals don't need to be checked because classes only start on them
				//for example they don't start at 12:35, they start at 12:30
				//goes into another if statement if both classes start within the 10 minute interval 
				if(classA.getStartTime()[3] < classB.getStartTime()[3]){
					return classA;
				}
				if(classA.getStartTime()[3] > classB.getStartTime()[3]){
					return classB;
				}
				if(classA.getStartTime()[3] == classB.getStartTime()[3]){
					//if the course code for classA is smaller than the course code for classB, return classA and vice versa
					//goes into another if statement if the course codes are the same
					std::string courseA = classA.getCourseCode().substr(0,4);
					std::string courseB = classB.getCourseCode().substr(0,4);
					int courseNumA = std::stoi(courseA);
					int courseNumB = std::stoi(courseB);
					if(courseNumA < courseNumB){
						return classA;
					}
					if(courseNumA > courseNumB){
						return classB;
					}
					if(courseNumA == courseNumB){
						//if the section number for classA is smaller than the section number for classB, return classA and vice versa
						//finishes here because if the all of theses are the same, then the 2 classes are the same
						std::string secA = classA.getCourseCode().substr(5,2);
						std::string secB = classB.getCourseCode().substr(5,2);
						int secNumA = std::stoi(secA);
						int secNumB = std::stoi(secB);
						if(secNumA < secNumB){
							return classA;
						}
						if(secNumA > secNumB){
							return classB;
						}
						if(secNumA == secNumB){
							if(classA.getDept() < classB.getDept()){
								return classA;
							}
							if(classA.getDept() > classB.getDept()){
								return classB;
							}
						}
					}
				}
			}
		}
	}
}

//takes in two different classes and returns the correct class according to the sorting outlined in the homework pdf
Classes sortDept(Classes classA, Classes classB){
	//if the course code for classA is smaller than the course code for classB, return classA and vice versa
	//goes into another if statement if the course codes are the same
	std::string courseA = classA.getCourseCode().substr(0,4);
	std::string courseB = classB.getCourseCode().substr(0,4);
	int courseNumA = std::stoi(courseA);
	int courseNumB = std::stoi(courseB);
	if(courseNumA < courseNumB){
		return classA;
	}
	if(courseNumA > courseNumB){
		return classB;
	}
	if(courseNumA == courseNumB){
		//if the section number for classA is smaller than the section number for classB, return classA and vice versa
		//goes into another if statement if the section numbers are the same
		std::string secA = classA.getCourseCode().substr(5,2);
		std::string secB = classB.getCourseCode().substr(5,2);
		int secNumA = std::stoi(secA);
		int secNumB = std::stoi(secB);
		if(secNumA < secNumB){
			return classA;
		}
		if(secNumA > secNumB){
			return classB;
		}
		if(secNumA == secNumB){
			//a vector of strings so I can use it to determine what days of the week come first
			std::vector<std::string> days {"Monday","Tuesday","Wednesday","Thursday","Friday"};
			std::vector<std::string>::iterator itr;
			std::vector<std::string>::iterator itr2;
			itr = find(days.begin(),days.end(), classA.getDays());
			itr2 = find(days.begin(), days.end(), classB.getDays());
			//if classA starts earlier in the week than classB, return classA and vice versa.
			//goes into another if statement if both classes are on the same day
			if(itr < itr2){
				return classA;
			}
			if(itr > itr2){
				return classB;
			}
			if(itr == itr2){
				//if classA starts in the AM and classB starts in the PM, return classA and vice versa
				//goes into another if statement if both classes start in the AM or PM
				//getStartTime().size()-2 is the 'A' in "AM" or the 'P' in "PM"
				if(classA.getStartTime()[classA.getStartTime().size()-2] < classB.getStartTime()[classB.getStartTime().size()-2]){
					return classA;
				}
				if(classA.getStartTime()[classA.getStartTime().size()-2] > classB.getStartTime()[classB.getStartTime().size()-2]){
					return classB;
				}
				
				if(classA.getStartTime()[classA.getStartTime().size()-2] == classB.getStartTime()[classB.getStartTime().size()-2]){
					//if classA starts at least 1 hour before classB, return classA and vice versa
					//goes into another if statement if both classes start within the same hour 
					std::string timeA = classA.getStartTime().substr(0,2);
					std::string timeB = classB.getStartTime().substr(0,2);
					int timeNumA = std::stoi(timeA);
					int timeNumB = std::stoi(timeB);
					if(timeNumA == 12 && timeNumA > timeNumB){
						return classA;				
					}
					if(timeNumB == 12 && timeNumA < timeNumB){
						return classB;				
					}
					if(timeNumA < timeNumB){
						return classA;
					}
					if(timeNumA > timeNumB){
						return classB;
					}
					if(timeNumA == timeNumB){
						//if classA starts at least 10 minutes before classB, return classA and vice versa
						//anthing less than 10 minute intervals don't need to be checked because classes only start on them
						//for example they don't start at 12:35, they start at 12:30
						//finishes here 
						if(classA.getStartTime()[3] < classB.getStartTime()[3]){
							return classA;
						}
						if(classA.getStartTime()[3] > classB.getStartTime()[3]){
							return classB;
						}
					}
				}
			}
		}
	}
}

//finds all the courses that are in a specific room and returns that vector
std::vector<Classes> oneRoom(std::vector<Classes> courses, std::string room){
	std::vector<Classes> coursesInRoom;
	for(int i = 0; i<courses.size(); i++){
		if(courses[i].getRoom() == room){
			coursesInRoom.push_back(courses[i]);
		}		
	}
	
	return coursesInRoom;
	
	
	
}
//finds all the courses that are in a specific department and returns that vector
std::vector<Classes> oneDept(std::vector<Classes> courses, std::string dept){
	std::vector<Classes> coursesDept;
	for(int i = 0; i<courses.size(); i++){
		if(courses[i].getDept() == dept){
			coursesDept.push_back(courses[i]);
		}		
	}
	
	return coursesDept;	
}


//prints out all courses in each room 
void printRoom(std::map<std::string,std::vector<Classes> > roomsAndInfo, std::ostream& outfile){
	std::map<std::string,std::vector<Classes> >::iterator itr;
	//loops through map of all rooms
	for(itr = roomsAndInfo.begin(); itr!=roomsAndInfo.end(); ++itr){
		outfile << "Room" << " " << itr->first << std::endl;
		//ensures I get the correct spacing by finding the length of the longest class name
		int longestName = 11;
		int longestDay = itr -> second[0].getDays().size();
		for(int j = 0; j < itr -> second.size(); j++){
			if(itr -> second[j].getCourseTitle().size() > longestName){
				longestName = itr -> second[j].getCourseTitle().size();
			}
			if(itr -> second[j].getDays().size() > longestDay){
				longestDay = itr -> second[j].getDays().size();
			}			
		}
		outfile << "Dept  " << "Coursenum  "; 
		outfile << std::left << std::setw(longestName) << "Class Title";
		outfile << "  ";
		outfile << std::left << std::setw(longestDay) << "Day";
		outfile << "  ";
		outfile << "Start Time  " << "End Time" << std::endl;
		
		outfile << "----  " << "---------  "; 
		for(int j = 0; j<longestName; j++){
			outfile << "-";
		}
		outfile << "  ";
		for(int j = 0; j<longestDay; j++){
			outfile << "-";
		}
		outfile << "  ";
		outfile << "----------  " << "--------" << std::endl;
		//prints info about all classes in the room
		for(int j = 0; j<itr -> second.size(); j++){
			outfile << itr -> second[j].getDept() << "  ";
			outfile << std::left << std::setw(9) << itr -> second[j].getCourseCode(); 
			outfile << "  ";
			outfile << std::left << std::setw(longestName) << itr -> second[j].getCourseTitle();
			outfile << "  ";
			outfile << std::left << std::setw(longestDay) << itr -> second[j].getDays();
			outfile << "  ";
			outfile << std::left << std::setw(10) << itr -> second[j].getStartTime(); 
			outfile << "  ";
			outfile << std::left << std::setw(8) << itr -> second[j].getEndTime() << std::endl;
			
		}
		outfile << itr -> second.size() << " entries" << std::endl;
		outfile << std::endl;
	}
}



void printDept(std::string department, std::vector<Classes> deptAndInfo, std::ostream& outfile){
	outfile << "Dept" << " " << department << std::endl;
	//ensures I get the correct spacing by finding the length of the longest class name
	int longestName = 11;
	int longestDay = deptAndInfo[0].getDays().size();
	for(int j = 0; j < deptAndInfo.size(); j++){
		if(deptAndInfo[j].getCourseTitle().size() > longestName){
			longestName = deptAndInfo[j].getCourseTitle().size();
		}
		if(deptAndInfo[j].getDays().size() > longestDay){
			longestDay =deptAndInfo[j].getDays().size();
		}			
	}
	outfile << "Coursenum  "; 
	outfile << std::left << std::setw(longestName) << "Class Title";
	outfile << "  ";
	outfile << std::left << std::setw(longestDay) << "Day";
	outfile << "  ";
	outfile << "Start Time  " << "End Time" << std::endl;
	
	outfile << "---------  "; 
	for(int j = 0; j<longestName; j++){
		outfile << "-";
	}
	outfile << "  ";
	for(int j = 0; j<longestDay; j++){
		outfile << "-";
	}
	outfile << "  ";
	outfile << "----------  " << "--------" << std::endl;
	//prints info about all classes in the department
	for(int j = 0; j<deptAndInfo.size(); j++){
		outfile << std::left << std::setw(9) << deptAndInfo[j].getCourseCode(); 
		outfile << "  ";
		outfile << std::left << std::setw(longestName) << deptAndInfo[j].getCourseTitle();
		outfile << "  ";
		outfile << std::left << std::setw(longestDay) << deptAndInfo[j].getDays();
		outfile << "  ";
		outfile << std::left << std::setw(10) << deptAndInfo[j].getStartTime(); 
		outfile << "  ";
		outfile << std::left << std::setw(8) << deptAndInfo[j].getEndTime() << std::endl;
		
	}
	outfile << deptAndInfo.size() << " entries" << std::endl;
	outfile << std::endl;
}
	
	
	
void printMostUsedRoom(std::map<std::string,int> roomsAndInfo, std::ostream& outfile){
	std::map<std::string,int>::iterator itr;
	
	int countMost = 0;
	int countLeast = 999;
	std::vector<std::string> mostUsedRoom;
	std::vector<std::string> leastUsedRoom;
	//loops through info to find most used room and least used room
	for(itr = roomsAndInfo.begin(); itr!=roomsAndInfo.end(); ++itr){
		if(itr -> second > countMost){
			mostUsedRoom.erase(mostUsedRoom.begin(),mostUsedRoom.end());
			mostUsedRoom.push_back(itr->first);
			countMost = itr -> second;
		}
		else if(itr -> second == countMost){
			mostUsedRoom.push_back(itr->first);
		}
		
		if(itr -> second < countLeast){
			leastUsedRoom.erase(leastUsedRoom.begin(),leastUsedRoom.end());
			leastUsedRoom.push_back(itr->first);
			countLeast = itr -> second;
		}
		else if(itr -> second == countLeast){
			leastUsedRoom.push_back(itr->first);
		}
	}
	
	//print handling
	if(mostUsedRoom.size() == 1){
		outfile << mostUsedRoom[0] << " is the most used room, being used " << countMost << " time(s)." << std::endl;
	}
	else{
		outfile << mostUsedRoom[0];
		for(int i = 1; i< mostUsedRoom.size(); i++){
			if(i == mostUsedRoom.size()-1){
				outfile << " and " <<mostUsedRoom[i];				
			}
			else{
				if(i == 1){
					outfile << ",";
				}
				outfile << " " << mostUsedRoom[i] << ",";
			}
			
			
		}
		outfile << " are the most used rooms, beinging used " << countMost << " time(s)." << std::endl;
		
	}
	
	if(leastUsedRoom.size() == 1){
		outfile << leastUsedRoom[0] << " is the least used room, being used " << countLeast << " time(s)." << std::endl;
	}
	else{
		outfile << leastUsedRoom[0];
		for(int i = 1; i< leastUsedRoom.size(); i++){
			if(i == leastUsedRoom.size()-1){
				outfile << " and " <<leastUsedRoom[i];
			}
			else{
				if(i == 1){
					outfile << ",";
				}
				outfile << " " << leastUsedRoom[i] << ",";
			}
			
			
		}
		outfile << " are the least used rooms, being used " << countLeast << " time(s)." << std::endl;
		
	}
	
}