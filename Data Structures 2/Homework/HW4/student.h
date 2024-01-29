#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <list>
#include <algorithm>

class Student{
	public:
		Student(std::string student_name);
		std::string GetName() const;
		void RemoveSchool(std::string school_name);
		void AddSchool(std::string school_name);
		bool HasOffer();
		std::string GetBestOffer();
		bool IsOfferTentativelyAccepted(std::string school_name);
		void PrepareToReceiveOffers();
		void PrintStudentDecision(std::ofstream &ostr) const;
		// std::list<std::string> GetPossibleSchools() const;
		
		std::list<std::string>::const_iterator begin() const { return prefered_colleges.begin(); }
		std::list<std::string>::const_iterator end() const { return prefered_colleges.end(); }
		
		std::list<std::string>::iterator begin() { return prefered_colleges.begin(); }
		std::list<std::string>::iterator end() { return prefered_colleges.end(); }
		
	private:
		bool has_offer;
		std::string name;
		std::list<std::string> prefered_colleges;
		std::string college_picked;
};

#endif