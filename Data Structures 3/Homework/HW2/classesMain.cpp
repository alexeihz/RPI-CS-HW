#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "classes.h"
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <utility>
#include <map>
using namespace std;

int main(int argc, char* argv[]){
	std::ifstream infile(argv[1]);
	if (!infile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	
	std::ofstream outfile(argv[2]);
	if (!outfile.good()) {
		std::cerr << "Can't open " << argv[2] << " to write.\n";
		exit(1);
	}
	
	//parse file
	std::vector<Classes> courses;
	std::string line;
	while (infile >> line){
		std::string ID = line;
		infile >> line;
		std::string dept = line;
		infile >> line;
		std::string courseCode = line;
		infile >> line;
		std::string courseTitle = line;
		infile >> line;
		std::string days = line;
		std::vector<std::string> daysVec;
		for(int i = 0; i<days.size(); i++){
			if(days[i] == 'M'){
				daysVec.push_back("Monday");
			}
			if(days[i] == 'T'){
				daysVec.push_back("Tuesday");
			}
			if(days[i] == 'W'){
				daysVec.push_back("Wednesday");
			}
			if(days[i] == 'R'){
				daysVec.push_back("Thursday");
			}
			if(days[i] == 'F'){
				daysVec.push_back("Friday");
			}			
		}
		infile >> line;
		std::string start = line;
		infile >> line;
		std::string end = line;
		infile >> line;
		std::string room = line;
		for(int j = 0; j<daysVec.size(); j++){
			Classes course(ID, dept, courseCode, courseTitle, daysVec[j], start, end, room);
			courses.push_back(course);			
		}		
	}
	//if the file is empty, print this
	if(courses.size() == 0){
		outfile << "No data available." << std::endl;
	}
	else{
		std::string argStr = argv[3];
		if(argStr == "room"){
			if(argc == 5){
				std::string argStr2 = argv[4];
				
				std::vector<Classes> specificRoom = oneRoom(courses, argStr2);
				//vector that will store all sorted rooms
				std::vector<Classes> sortedRoom;
				
				sortedRoom.push_back(specificRoom[0]);
				
				for(int i = 1; i < specificRoom.size(); i++){
					bool runs = false;
					std::vector<Classes>::iterator itr = sortedRoom.begin();
					//loops through sortedRoom
					for(int j = 0; j<sortedRoom.size(); j++){
						Classes sortClass2 = sortRoom(specificRoom[i],sortedRoom[j]);
						//if sortClass2 is the same as specificRoom[i], then specificRoom[i] comes before sortedRoom[j]
						if(sortClass2.getID() == specificRoom[i].getID() && sortClass2.getDept() == specificRoom[i].getDept() && 
						sortClass2.getCourseCode() == specificRoom[i].getCourseCode() && sortClass2.getCourseTitle() == specificRoom[i].getCourseTitle() &&
						sortClass2.getDays() == specificRoom[i].getDays() && sortClass2.getStartTime() == specificRoom[i].getStartTime() &&sortClass2.getEndTime() == specificRoom[i].getEndTime()){ 
							runs = true;
							sortedRoom.insert(itr,1,specificRoom[i]);				
							break;
						}
						++itr;
					}
					//if itr goes through all of sortedRoom
					if(runs == false){
						sortedRoom.push_back(specificRoom[i]);
					}				
				}			
				std::map<std::string,std::vector<Classes> > oof;
				oof[argStr2] = sortedRoom;
				printRoom(oof,outfile);
			
			}
			else{
				
				std::map<std::string,std::vector<Classes> > allRooms;
				
				std::map<std::string,std::vector<Classes> >::iterator itr;
				//fills map with room names and course info
				for(int i = 0; i< courses.size(); i++){
					allRooms[courses[i].getRoom()].push_back(courses[i]);
				}
				//loops through allRooms
				for(itr = allRooms.begin(); itr != allRooms.end(); ++itr){
					//vector that will store all sorted rooms
					std::vector<Classes> sortedRoom;
				
					sortedRoom.push_back(allRooms[itr->first][0]);
					//loops through allRooms[itr->first]
					for(int i = 1; i < allRooms[itr->first].size(); i++){
						bool runs = false;
						std::vector<Classes>::iterator itr2 = sortedRoom.begin();
						//loops through sortedRoom
						for(int j = 0; j<sortedRoom.size(); j++){
							Classes sortClass2 = sortRoom(allRooms[itr->first][i],sortedRoom[j]);
							//if sortClass2 is the same as allRooms[itr->first][i], then allRooms[itr->first][i] comes before sortedRoom[j]
							if(sortClass2.getID() == allRooms[itr->first][i].getID() && sortClass2.getDept() == allRooms[itr->first][i].getDept() && 
							sortClass2.getCourseCode() == allRooms[itr->first][i].getCourseCode() && sortClass2.getCourseTitle() == allRooms[itr->first][i].getCourseTitle() &&
							sortClass2.getDays() == allRooms[itr->first][i].getDays() && sortClass2.getStartTime() == allRooms[itr->first][i].getStartTime() &&sortClass2.getEndTime() == allRooms[itr->first][i].getEndTime()){ 
								runs = true;
								sortedRoom.insert(itr2,1,allRooms[itr->first][i]);				
								break;
							}
							++itr2;
						}
						//if itr2 goes through all of sortedRoom
						if(runs == false){
							sortedRoom.push_back(allRooms[itr->first][i]);
						}				
					}			
					allRooms[itr->first] = sortedRoom;
					
				}
				printRoom(allRooms,outfile);
			}
		}
		
		if(argStr == "dept"){
			std::string argStr2 = argv[4];
			
			std::vector<Classes> specificDept = oneDept(courses, argStr2);
			//vector that will store all sorted rooms
			std::vector<Classes> sortedDept;
			
			sortedDept.push_back(specificDept[0]);
			for(int i = 1; i < specificDept.size(); i++){
				bool runs = false;
				std::vector<Classes>::iterator itr = sortedDept.begin();
				//loops through sortedDept
				for(int j = 0; j<sortedDept.size(); j++){
					Classes sortDept2 = sortDept(specificDept[i],sortedDept[j]);
					//if sortDept2 is the same as specificDept[i], then specificDept[i] comes before sortedDept[j]
					if(sortDept2.getID() == specificDept[i].getID() && sortDept2.getDept() == specificDept[i].getDept() && 
					sortDept2.getCourseCode() == specificDept[i].getCourseCode() && sortDept2.getCourseTitle() == specificDept[i].getCourseTitle() &&
					sortDept2.getDays() == specificDept[i].getDays() && sortDept2.getStartTime() == specificDept[i].getStartTime() && sortDept2.getEndTime() == specificDept[i].getEndTime()){ 
						runs = true;
						sortedDept.insert(itr,1,specificDept[i]);				
						break;
					}
					++itr;
				}
				//if itr goes through all of sortedDept
				if(runs == false){
					sortedDept.push_back(specificDept[i]);
				}					
			}
			printDept(argStr2,sortedDept,outfile);
		
		}
		
		if(argStr == "custom"){
			//map that has room with number of times its used
			std::map<std::string,int> allRooms;
			std::map<std::string,int>::iterator itr;
			for(int i = 0; i< courses.size(); i++){
				allRooms[courses[i].getRoom()]++;		
			}
			
			
			
			printMostUsedRoom(allRooms,outfile);
			
			
		}
	}
}