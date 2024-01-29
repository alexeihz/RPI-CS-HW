// file header "bowler.h"
#include <string>
#include <vector>

#ifndef BOWLER_H
#define BOWLER_H

class Bowler{
public:
	Bowler();
	Bowler(const std::string& first, const std::string& last, const std::vector<int>& scores);
	
	// ACCESSORS
	std::string getFirstName() const;
	std::string getLastName() const;
	int getTotalScore() const;
	std::vector<int> getScores() const;
	// MODIFIERS
	
	
private: // REPRESENTATION (member variables)
	std::string first_name, last_name;
	std::vector<int> scores;
};

bool sortName(const Bowler& a, const Bowler& b);
bool sortScores(const Bowler& a, const Bowler& b);
void printFrame(const std::vector<Bowler>& a,std::ostream& outfile);
void printWinner(const std::vector<Bowler>& a,std::ostream& outfile);
#endif