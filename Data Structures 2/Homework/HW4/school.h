#ifndef SCHOOL_H_
#define SCHOOL_H_

#include <list>
#include <string>

class School{
	public:
		//School(std::string school_name, int open_slots) : name(school_name), slots(open_slots) {
		//}
		School(std::string school_name, int open_slots);
		
		std::string GetName() const;
		void AddStudent(std::string student_name);
		int NumAcceptedStudents();
		int MaxAcceptedStudents();
		void StudentDeclinesTentativeAcceptance(std::string student_name);
		void StudentTentativelyAcceptsOffer(std::string student_name);
		std::string MakeNextOffer();
		void PrintSchoolEnrollment(std::ofstream &ostr);
		void PrepareToMakeOffers();
		// std::list<std::string> GetPossibleStudents() const;
		void insertStudent(std::list<std::string>::iterator itr, std::string student_name);
		
		std::list<std::string>::const_iterator begin() const { return possible_students.begin(); }
		std::list<std::string>::const_iterator end() const { return possible_students.end(); }
		
		std::list<std::string>::iterator begin() { return possible_students.begin(); }
		std::list<std::string>::iterator end() { return possible_students.end(); }
		
	private:
		std::list<std::string> students_accepted;
		std::string name;
		std::list<std::string>::iterator itr_offers;
		int slots;
		std::list<std::string> possible_students;
};


#endif
