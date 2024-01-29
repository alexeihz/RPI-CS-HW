#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Football.h"
using namespace std;

Football::Football() {}
Football::Football(std::vector<std::string> & away, std::vector<std::string> & home){
	this -> away_info = away;
	this -> home_info = home;
}

std::vector <std::string> Football::getHomeInfo() const{
	return home_info;
}
std::vector <std::string> Football::getAwayInfo() const{
	return away_info;
}

//takes the 2 home and away vectors and moves the total home scores, total away scores, the differential, and the home and away team names to one vector
std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > one_vec(std::vector<std::string> & away, std::vector<std::string> & home){
	//initialize variables
	std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > vec;
	//std::vector<int> home_scores;
	//std::vector<int> away_scores;
	std::vector<int> home_total;
	std::vector<int> away_total;
	std::vector<std::string> away_teams;
	std::vector<std::string> home_teams;
	//adds the home team name and the away team name to thier respective vectors
	for(unsigned i= 0; i<home.size();i++){
		if(i==0 || i%7==0){
			home_teams.push_back(home[i]);
			away_teams.push_back(away[i]);
		}
		//adds the home team total scores and the away team total scores to thier respective vectors
	else if(i==6 || (i+1)%7==0){
			home_total.push_back(atoi(home[i].c_str()));
			away_total.push_back(atoi(away[i].c_str()));
		}
		// else{
			// home_scores.push_back(atoi(home[i].c_str()));
			// away_scores.push_back(atoi(away[i].c_str()));
		// }
	}
	
	for(unsigned i = 0; i<away_total.size();i++){
		//initialize variables
		std::vector<int> totals;
		std::pair<std::vector<int>,std::pair<std::string,std::string> > pair1;
		std::pair<std::string,std::string> pair2;
		//moves away and home totals and differentials to one vector
		totals.push_back(away_total[i]);
		totals.push_back(home_total[i]);
		totals.push_back(away_total[i] - home_total[i]);
		//makes a pair with home and away team names
		pair2 = std::make_pair(away_teams[i], home_teams[i]);
		//makes a pair with totals vector and pair of home and away team names
		pair1 = std::make_pair(totals,pair2);
		vec.push_back(pair1);
	}
	return vec;
}

void total_points(std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > & vec, std::ofstream & outfile){
	outfile << "ALL GAMES, SORTED BY POINT DIFFERENTIAL:" << std::endl;
	//makes a vector to sort the previous vector
	std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > vec_sort1;
	vec_sort1.push_back(vec[0]);
	bool swap = true;
	for(unsigned i = 1; i<vec.size(); i++){
		// the vec_sort1 is constantly changing so the size must be set to a variable to keep it from changing
		int size = vec_sort1.size(); 
		for(int j = 0; j<size; j++){
			//checks if the differential of the new information is less than the differential of the present information and if it is inserts the new info in front of the present one
			if(std::abs(vec[i].first[2]) < std::abs(vec_sort1[j].first[2])){
				vec_sort1.insert(vec_sort1.begin()+j,vec[i]);
				break;
			}
			//if the differentials are equal, then it checks which set of data has the larger added total scores and places the larger one in front of the present one and the smaller one behind the present one
			else if(std::abs(vec[i].first[2]) == std::abs(vec_sort1[j].first[2])){
				if(vec[i].first[0] + vec[i].first[1] < vec_sort1[j].first[0] + vec_sort1[j].first[1]){
					vec_sort1.insert(vec_sort1.begin()+j+1,vec[i]);
					break;
				}
				if(vec[i].first[0] + vec[i].first[1] > vec_sort1[j].first[0] + vec_sort1[j].first[1]){
					vec_sort1.insert(vec_sort1.begin()+j,vec[i]);
					break;
				}
				//if the added total scores are equal, then it checks which away team name comes first in the alphabet and sorts them accordingly
				else if(vec[i].first[0] + vec[i].first[1] == vec_sort1[j].first[0] + vec_sort1[j].first[1]){
					if(vec[i].second.first < vec_sort1[j].second.first){
						vec_sort1.insert(vec_sort1.begin()+j,vec[i]);
						break;
					}
					if(vec[i].second.first > vec_sort1[j].second.first){
						vec_sort1.insert(vec_sort1.begin()+j+1,vec[i]);
						break;
					}
					//if the away team names are the same, then it checks which home team name comes first in the alphabet and sorts them accordingly
					else if(vec[i].second.first == vec_sort1[j].second.first){
						if(vec[i].second.second < vec_sort1[j].second.second){
							vec_sort1.insert(vec_sort1.begin()+j,vec[i]);
							break;
						}
						else if(vec[i].second.second > vec_sort1[j].second.second){
							vec_sort1.insert(vec_sort1.begin()+j+1,vec[i]);
							break;
						}
					}
				}
			}
			else if((unsigned)j == vec_sort1.size()-1){
				vec_sort1.push_back(vec[i]);
			}
		}
	}
	
	//loops back through vec_sort1 to make sure that everything is properly sorted and loops until it is
	while(swap){
		swap=false;
		for(unsigned j = 0; j<vec_sort1.size()-1; j++){
			std::pair<std::vector<int>,std::pair<std::string,std::string> > temp;
			if(std::abs(vec_sort1[j].first[2]) == std::abs(vec_sort1[j+1].first[2])){
				if(vec_sort1[j].first[0] + vec_sort1[j].first[1] < vec_sort1[j+1].first[0] + vec_sort1[j+1].first[1]){
					temp = vec_sort1[j+1];
					vec_sort1.erase(vec_sort1.begin()+j+1);
					vec_sort1.insert(vec_sort1.begin()+j,temp);
					swap=true;
					break;
				}
				
				if(vec_sort1[j].first[0] + vec_sort1[j].first[1] == vec_sort1[j+1].first[0] + vec_sort1[j+1].first[1]){
					if(vec_sort1[j].second.first < vec_sort1[j+1].second.first){
						temp = vec_sort1[j+1];
						vec_sort1.erase(vec_sort1.begin()+j+1);
						vec_sort1.insert(vec_sort1.begin()+j,temp);
						swap=true;
						break;
					}
					else if(vec_sort1[j].second.first == vec_sort1[j+1].second.first){
						if(vec_sort1[j].second.second < vec_sort1[j+1].second.second){
							temp = vec_sort1[j+1];
							vec_sort1.erase(vec_sort1.begin()+j+1);
							vec_sort1.insert(vec_sort1.begin()+j,temp);
							swap=true;
							break;
						}
					}
				}
			}
		}
	}
	//the length of a home team and away team name
	unsigned home_len = vec_sort1[0].second.first.length();
	unsigned away_len = vec_sort1[0].second.second.length();
	
	//finds the longest away team and home team name
	for(unsigned j = 0; j<vec_sort1.size();j++){
		if(vec_sort1[j].second.first.length() >= home_len){
			home_len = vec_sort1[j].second.first.length();
		}
		if(vec_sort1[j].second.second.length() >= away_len){
			away_len = vec_sort1[j].second.second.length();
		}
	}
	//finds the longest of the longest away team and home team name
	unsigned maxlen =std::max(home_len,away_len);
	
	for(unsigned i = 0; i<vec_sort1.size(); i++){
		//does text justification using empty spaces
		std::string  away_str = vec_sort1[i].second.first;
		std::string home_str = vec_sort1[i].second.second;
		int total_points = vec_sort1[i].first[0] + vec_sort1[i].first[1];
		std::string digits1 = "  ";
		std::string digits2 = " ";
		std::string digits3 = " ";
		for(unsigned j=vec_sort1[i].second.first.length(); j<maxlen; j++){
			away_str = away_str + " ";
		}
		for(unsigned j=vec_sort1[i].second.second.length(); j<maxlen; j++){
			home_str = home_str + " ";
		}
		if(vec_sort1[i].first[0] <10){
			digits1 = digits1 + " ";
		}
		if(vec_sort1[i].first[1] <10){
			digits2 = digits2 + " ";
		}
		if(vec_sort1[i].first[2] <10 && vec_sort1[i].first[2] > -10){
			digits3 = digits3 + " ";
		}
		//if the differential is negative, the away team lost to the home team
		if(vec_sort1[i].first[2] < 0){
			outfile << std::left << away_str << "  lost to   " << std::left << home_str << digits1 << vec_sort1[i].first[0] << " -" << digits2 << vec_sort1[i].first[1] << "  differential = " << digits3 << std::abs(vec_sort1[i].first[2]) << "  " << "total points =   " << std::right << total_points << std::endl ;
		}
		//if the differential is positive, the away team defeated the home team
		if(vec_sort1[i].first[2] > 0){
			outfile << std::left << away_str << "  defeated  " << std::left << home_str << digits1 << vec_sort1[i].first[0] << " -" << digits2 << vec_sort1[i].first[1] << "  differential = " << digits3 << std::abs(vec_sort1[i].first[2]) << "  " << "total points =   " << std::right << total_points << std::endl ;
		}
	}
}

void win_percentage(std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > & vec, std::ofstream & outfile){
	outfile << "ALL TEAMS, SORTED BY WIN PERCENTAGE:" << std::endl;
	//initialize variables
	std::vector<std::pair<std::string,std::pair<int,int> > > teams_scores;
	std::pair <int,int> pair1; //<win,lose>
	pair1 = std::make_pair(0,0);
	//adds a pair of the away team name and pair1 to teams_scores
	teams_scores.push_back(std::make_pair(vec[0].second.first,pair1));
	//adds a pair of the home team name and pair1 to teams_scores
	teams_scores.push_back(std::make_pair(vec[0].second.second,pair1));

	for(unsigned i = 0; i<vec.size(); i++){
		//teams_scores is constantly changing. Seting the size to a variable keeps it stagnet
		int size = teams_scores.size(); 
		bool away = false;
		bool home = false;
		for(int j=0; j<size; j++){
			//if the names teams_scores already has the team in the vector then it adds either a win or a loss
			if(teams_scores[j].first == vec[i].second.first){
				if(vec[i].first[0] > vec[i].first[1]){
					teams_scores[j].second.first++;
					away=true;
				}
				if(vec[i].first[0] < vec[i].first[1]){
					teams_scores[j].second.second++;
					away=true;
				}
			}
			if(teams_scores[j].first == vec[i].second.second){
				if(vec[i].first[1] > vec[i].first[0]){
					teams_scores[j].second.first++;
					home=true;
				}
				if(vec[i].first[1] < vec[i].first[0]){
					teams_scores[j].second.second++;
					home=true;
				}
			}
			//if the vector is at its last element, then 2 elements with the names and wins/losses of the away and home teams are made and pushed back to the vector
			else if (j==size-1 && teams_scores[j].first != vec[i].second.first){
				if(away==false){
					if(vec[i].first[0] > vec[i].first[1]){
						pair1 = std::make_pair(1,0);
					}
					if(vec[i].first[0] < vec[i].first[1]){
						pair1 = std::make_pair(0,1);
					}
					teams_scores.push_back(std::make_pair(vec[i].second.first,pair1));
				}
				if(home==false){
					if(vec[i].first[1] > vec[i].first[0]){
						pair1 = std::make_pair(1,0);
					}
					if(vec[i].first[1] < vec[i].first[0]){
						pair1 = std::make_pair(0,1);
					}
					teams_scores.push_back(std::make_pair(vec[i].second.second,pair1));
				}
			}
		}
	}
	
	std::vector<std::pair<std::string,std::pair<int,int> > > sorted_vec;//made to sort teams_scores by higher win_percentage, then by more total games played, then by alphabetically
	sorted_vec.push_back(teams_scores[0]);
	
	for(unsigned i = 1; i<teams_scores.size(); i++){
		int size2 = sorted_vec.size();//constantly changing size
		float percent_win1 = teams_scores[i].second.first/float (teams_scores[i].second.first+teams_scores[i].second.second);
		for(int j = 0; j<size2; j++){
			float percent_win2 = sorted_vec[j].second.first/float (sorted_vec[j].second.first+sorted_vec[j].second.second);
			if(percent_win2 < percent_win1){
				sorted_vec.insert(sorted_vec.begin()+j,teams_scores[i]);
				break;
			}
			else if(percent_win2 == percent_win1){
				if(teams_scores[i].second.first+teams_scores[i].second.second > sorted_vec[j].second.first+sorted_vec[j].second.second){
					sorted_vec.insert(sorted_vec.begin()+j,teams_scores[i]);
					break;
				}
				else if(teams_scores[i].second.first+teams_scores[i].second.second < sorted_vec[j].second.first+sorted_vec[j].second.second){
					sorted_vec.insert(sorted_vec.begin()+j +1 ,teams_scores[i]);
					break;
				}
				else if(teams_scores[i].second.first+teams_scores[i].second.second == sorted_vec[j].second.first+sorted_vec[j].second.second){
					if(teams_scores[i].first < sorted_vec[j].first){
						sorted_vec.insert(sorted_vec.begin()+j,teams_scores[i]);
						break;
					}
					else if(teams_scores[i].first > sorted_vec[j].first){
						sorted_vec.insert(sorted_vec.begin()+j+1,teams_scores[i]);
						break;
					}
					
				}
			}
			else if(percent_win2 > percent_win1 && j==size2-1){
				sorted_vec.push_back(teams_scores[i]);
			}
		}
	}
	unsigned len = sorted_vec[0].first.length();
	//finds longest team name
	for(unsigned j = 0; j<sorted_vec.size();j++){
		if(sorted_vec[j].first.length() >= len){
			len = sorted_vec[j].first.length();
		}
	}
	
	for(unsigned i = 0; i<sorted_vec.size(); i++){
		std::string team_str = "  ";
		std::string digits_lose = " ";
		std::string digits_win = " ";
		std::string digits_per = " ";
		//text justification with spaces
		for(unsigned j=sorted_vec[i].first.length(); j<len; j++){
			team_str = team_str + " ";
		}
		if(sorted_vec[i].second.first>9){
			digits_win += " ";
		}
		if(sorted_vec[i].second.second>9){
			digits_lose += " ";
		}
		float win_percent = sorted_vec[i].second.first/float (sorted_vec[i].second.first+sorted_vec[i].second.second);
		if(win_percent > 9){
			digits_per += " ";
		}
		outfile << std::left << sorted_vec[i].first << team_str << digits_win << sorted_vec[i].second.first << " win(s) - "  << digits_lose << sorted_vec[i].second.second << " loss(es) " << digits_per << std::setprecision(2)<< fixed <<win_percent << std::endl;
	}
}

void creative (std::vector<std::string> date, std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > & vec, std::ofstream & outfile){
	outfile << "BIGGEST WINNER ON A DAY, SORTED BY DATE" <<std::endl;
	std::vector<std::pair<std::vector<std::string>,std::vector<std::string> > > wins_per_date;//<dates,winners>
	std::pair<std::vector<std::string>,std::vector<std::string> > vec_pair;
	
	std::vector<std::string> winner;//holds winner of game and score
	stringstream int_str;
	//pushes back first set of data to wins_per_date
	std::vector<std::string> date_vec;//holds dates
	date_vec.push_back(date[0]);
	date_vec.push_back(date[1]);
	date_vec.push_back(date[2]);
	date_vec.push_back(date[3]);
	unsigned date_count = 4;
	
	//pushes winner of game and the score back to the winner vector
	if(vec[0].first[2]<0){
		winner.push_back(vec[0].second.second);
		int_str << vec[0].first[1];
		winner.push_back(int_str.str());
	}
	else if(vec[0].first[2]>0){
		winner.push_back(vec[0].second.first);
		int_str << vec[0].first[0];
		winner.push_back(int_str.str());
	}
	vec_pair = std::make_pair(date_vec,winner);
	wins_per_date.push_back(vec_pair);
	
	for(unsigned i = 1; i <vec.size();i++){
		//clears old vectors
		date_vec.clear();
		winner.clear();
		stringstream int_str2;
		if(date_count<date.size()){
			for(unsigned j = date_count; j<date_count+4; j++){
				date_vec.push_back(date[j]);
			}
			date_count=date_count+4;
		}
		int size = wins_per_date.size();
		for(int k = 0; k<size; k++){
			//if the date from the 2 vectors match, look for a score higher than the present one in the "vec" vector and replace it
			if(wins_per_date[k].first[0] == date_vec[0] && wins_per_date[k].first[1] == date_vec[1] && wins_per_date[k].first[2] == date_vec[2] && wins_per_date[k].first[3] == date_vec[3]){
				int win_score = 0;
				std::string win_team;
				if(vec[i].first[2]<0){
					win_team = vec[i].second.second;
					win_score = vec[i].first[1];
				}
				else if(vec[i].first[2]>0){
					win_team = vec[i].second.first;
					win_score = vec[i].first[0];
				}
				if(atoi(wins_per_date[k].second[1].c_str()) < win_score){
					int_str << win_score;
					wins_per_date[k].second[1] = int_str.str();
					wins_per_date[k].second[0] = win_team;
				}
				break;
			}
			//else if the k is 1 less than the size, push back the winner and the score of the "vec" vector
			else if(k==size-1){
				if(vec[i].first[2]<0){
					winner.push_back(vec[i].second.second);
					int_str2 << vec[i].first[1];
					winner.push_back(int_str2.str());
				}
				else if(vec[i].first[2]>0){
					winner.push_back(vec[i].second.first);
					int_str2 << vec[i].first[0];
					winner.push_back(int_str2.str());
				}
				vec_pair = std::make_pair(date_vec,winner);
				wins_per_date.push_back(vec_pair);
			}
		}
	}
	
	//text justification
	std::string team_str;
	std::string digits;
	std::string day_str;
	std::string month_str;
	std::string date_str;
	std::string year_str;
	
	unsigned len_team = wins_per_date[0].second[0].length();
	unsigned len_day = wins_per_date[0].first[0].length();
	unsigned len_month = wins_per_date[0].first[2].length();
	unsigned len_year = wins_per_date[0].first[3].length();
	//finds longest team name
	for(unsigned j = 0; j<wins_per_date.size();j++){
		if(wins_per_date[j].second[0].length() >= len_team){
			len_team = wins_per_date[j].second[0].length();
		}
		if(wins_per_date[j].first[0].length() >= len_day){
			len_day = wins_per_date[j].first[0].length();
		}
		if(wins_per_date[j].first[1].length() >= len_month){
			len_month = wins_per_date[j].first[1].length();
		}
		if(wins_per_date[j].first[3].length() >= len_year){
			len_year = wins_per_date[j].first[3].length();
		}
		
	}	
	
	for(unsigned i = 0; i<wins_per_date.size(); i++){
		team_str = " ";
		digits = " ";
		day_str  = " ";
		month_str = " ";
		date_str = " ";
		year_str = " ";
		for(unsigned j=wins_per_date[i].second[0].length(); j<len_team; j++){
			team_str = team_str + " ";
		}
		for(unsigned j=wins_per_date[i].first[0].length(); j<len_day; j++){
			day_str = day_str + " ";
		}
		for(unsigned j=wins_per_date[i].first[1].length(); j<len_month; j++){
			month_str = month_str + " ";
		}
		if(atoi(wins_per_date[i].first[2].c_str()) <10){
			date_str += " ";
		}
		for(unsigned j=wins_per_date[i].first[3].length(); j<len_year; j++){
			year_str = year_str + " ";
		}
		if(atoi(wins_per_date[i].second[1].c_str()) <10){
			digits = digits + " ";
		}
		outfile<<"Biggest winner on " << wins_per_date[i].first[0] << day_str << wins_per_date[i].first[1] << month_str << date_str << wins_per_date[i].first[2] << " " <<wins_per_date[i].first[3] << year_str+ ": " << wins_per_date[i].second[0] << team_str<<"-" << digits << wins_per_date[i].second[1] << std::endl;
	}
}

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
	std::vector<std::string> date;
	std::vector<std::string> away_team;
	std::vector<std::string> home_team;
	bool home = false;
	std::string word;
	//parse file
	while (infile >> word) {
		if(word=="Sunday" || word== "Monday" || word=="Tuesday" || word=="Wednesday" || word=="Thursday" || word=="Friday" || word=="Saturday" || word=="Sunday"){
			date.push_back(word);
			for (int i = 0; i<3; i++){
				infile>>word;
				date.push_back(word);
			}
		}
		else if(home==false){
			away_team.push_back(word);
			for (int i = 0; i<6; i++){
				infile>>word;
				away_team.push_back(word);
				
			}
			home=true;
		}
		else if(home==true){
			home_team.push_back(word);
			for (int i = 0; i<6; i++){
				infile>>word;
				home_team.push_back(word);
			}
			home=false;
		}
		
	}
	std::vector<std::pair<std::vector<int>,std::pair<std::string,std::string> > > vec;
	vec = one_vec(away_team,home_team);
	
	if (argc == 4){
		std::string argStr = argv[3];
		if(argStr =="--total_points"){
			total_points(vec,outfile);
		}
		if(argStr =="--win_percentage"){
			win_percentage(vec,outfile);
		}
		if(argStr =="--creative"){
			creative(date,vec,outfile);
		}
	}
	else if(argc==3){
		total_points(vec,outfile);
		outfile << "" << std::endl;
		win_percentage(vec,outfile);
		outfile << "" << std::endl;
		creative(date,vec,outfile);
	}
}