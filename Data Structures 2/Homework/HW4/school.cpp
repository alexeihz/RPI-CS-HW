#include "school.h"

#include <algorithm>
#include <cassert>
#include <list>
#include <iomanip>
#include <fstream>
#include <iostream>

//constructor
School::School(std::string school_name, int open_slots){
	name = school_name;
	slots = open_slots;
}
//inserts student into possible students list
void School::insertStudent(std::list<std::string>::iterator itr, std::string student_name){
	if (std::find(possible_students.begin(), possible_students.end(), student_name) != possible_students.end())
		std::cerr << "WARNING: could not add " << student_name << " into school preference list, this student is already in the list" << std::endl;
	else
		possible_students.insert(itr, student_name);
}

std::string School::GetName() const{
	return name;
}

int School::NumAcceptedStudents(){
	return students_accepted.size();
}

void School::AddStudent(std::string student_name){
	if (std::find(possible_students.begin(), possible_students.end(), student_name) != possible_students.end())
		std::cerr << "WARNING: could not add " << student_name << " into school preference list, this student is already in the list" << std::endl;
	else
		possible_students.push_back(student_name);
}

int School::MaxAcceptedStudents(){
	return slots;
}
//removes student from students_accepted list
void School::StudentDeclinesTentativeAcceptance(std::string student_name){
	std::list<std::string>::iterator itr;
	
	for(itr = students_accepted.begin(); itr != students_accepted.end(); ++itr){
		if((*itr) == student_name){
			students_accepted.erase(itr);
			break;
		}
	}
}

void School::StudentTentativelyAcceptsOffer(std::string student_name){
	students_accepted.push_back(student_name);
}

std::string School::MakeNextOffer(){
	if(itr_offers != possible_students.end()){
		std::string str = *itr_offers;
		++itr_offers;
		return str;
	}
	else{
		return "";
	}
}

void School::PrintSchoolEnrollment(std::ofstream &ostr){
	ostr << "student(s) who will be attending " << name << ":" <<std::endl;
	
	students_accepted.sort();
	
	std::list<std::string>::iterator itr = students_accepted.begin();
	while(itr != students_accepted.end()){
		ostr << "  " << (*itr) << std::endl;
		++itr;
	}
	if (NumAcceptedStudents() != MaxAcceptedStudents()) {
		ostr << "  [" << (MaxAcceptedStudents() - NumAcceptedStudents()) << " remaining slot(s) in enrollment]" << std::endl;
	}
}

void School::PrepareToMakeOffers(){
	itr_offers = possible_students.begin();
}
