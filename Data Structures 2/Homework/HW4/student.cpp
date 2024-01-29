#include "student.h"

#include <algorithm>
#include <cassert>
#include <list>
#include <iomanip>
#include <fstream>
#include <iostream>

//constructor
Student::Student(std::string student_name){
	name = student_name;
}

std::string Student::GetName() const{
	return name;
}

void Student::AddSchool(std::string school_name){
	if (std::find(prefered_colleges.begin(), prefered_colleges.end(), school_name) != prefered_colleges.end())
		std::cerr << "WARNING: could not add " << school_name << " into student preference list, this school is already in the list" << std::endl;
	else
		prefered_colleges.push_back(school_name);
}
//removes school from prefered_colleges list
void Student::RemoveSchool(std::string school_name){
	std::list<std::string>::iterator itr;
	
	for(itr = prefered_colleges.begin(); itr != prefered_colleges.end(); ++itr){
		if((*itr) == school_name){
			prefered_colleges.erase(itr);
			break;
		}
	}
}

bool Student::HasOffer(){
	return has_offer;
}

std::string Student::GetBestOffer(){
	return college_picked;
}

void Student::PrintStudentDecision(std::ofstream &ostr) const{
	if (college_picked == "") {
		ostr << name << " has not received an acceptable offer" << std::endl;
	} else {
		ostr << name << " will be attending " << college_picked << std::endl;
	}
}

bool Student::IsOfferTentativelyAccepted(std::string school_name){
	// school  not in list => deny
	if (std::find(prefered_colleges.begin(), prefered_colleges.end(), school_name) == prefered_colleges.end())
		return false;
		
	//if the student has no offer, the college is accepted
	if(has_offer == false){
		has_offer = true;
		college_picked = school_name;
		return true;
	}
	else{
		std::list<std::string>::iterator itr = prefered_colleges.begin();
		while(itr != prefered_colleges.end()){
			// if new school was found first then replace current
			if(*itr == school_name){
				college_picked = school_name;
				return true;
			}
			// if current was found first then continue using it
			if(*itr == college_picked){
				return false;
			}
			
			++itr;
		}
		return false;
	}
	
}

void Student::PrepareToReceiveOffers(){
	has_offer = false;
	college_picked = "";
}


