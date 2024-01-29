#include <string>
#include <vector>
#include <map>

#ifndef CLASSES_H
#define CLASSES_H

class Classes{
	public:
		//constructor 
		Classes(std::string courseID, std::string department, std::string code, std::string title, std::string classDays, std::string startTime, std::string endTime, std::string classRoom);
		//ACCESSOR
		std::string getID() const;
		std::string getDept() const;
		std::string getCourseCode() const;
		std::string getCourseTitle() const;
		std::string getDays() const;
		std::string getStartTime() const;
		std::string getEndTime() const;
		std::string getRoom() const;
		
		
		
	private:
		std::string ID, dept, courseCode, courseTitle, start, end, room, days;
		
};

std::vector<Classes> oneRoom(std::vector<Classes> courses, std::string room);
std::vector<Classes> oneDept(std::vector<Classes> courses, std::string room);
Classes sortRoom(Classes classA, Classes classB);
Classes sortDept(Classes classA, Classes classB);
void printRoom(std::map<std::string,std::vector<Classes> > roomsAndInfo, std::ostream& outfile);
void printDept(std::string department, std::vector<Classes> deptAndInfo, std::ostream& outfile);
void printMostUsedRoom(std::map<std::string,int> roomsAndInfo, std::ostream& outfile);

#endif