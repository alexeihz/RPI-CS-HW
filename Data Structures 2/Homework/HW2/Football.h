//Football.h

#include <string>
#include <vector>

#ifndef FOOTBALL_H
#define FOOTBALL_H

class Football{
public:
	Football();
	Football(std::vector<std::string> & away, std::vector<std::string> & home);
	
	// ACCESSORS
	std::vector <std::string> getAwayInfo() const;
	std::vector <std::string> getHomeInfo() const;
	
	// MODIFIERS
	
	
private: // REPRESENTATION (member variables)
	std::vector <std::string> away_info, home_info;
};

void total_points(std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > & vec, std::ofstream & outfile);
void win_percentage(std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > & vec, std::ofstream & outfile);
void creative (std::vector<std::string> date, std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > & vec, std::ofstream & outfile);
std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > one_vec(std::vector<std::string> & away, std::vector<std::string> & home);
#endif
