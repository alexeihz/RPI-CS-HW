//file bowlerMain.cpp
#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "bowler.h"
#include <cstdlib>
#include <algorithm>
#include <cctype>
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
	std::string argStr = argv[3];
	if(argStr == "standard"){
		std::vector<Bowler> bowlers;
		
		std::string line;
		while (std::getline(infile, line)) {
			// Load string stream
			std::istringstream ss(line);
			
			// Load name and scores
			std::string first, last;
			ss >> first;
			ss >> last;
			std::vector<int> scores;
			int num;
			while (ss >> num) {
				//std::cout << num << std::endl;
				scores.push_back(num);
			}
			Bowler b(first, last, scores);
			bowlers.push_back(b);
		}
		
		std::sort(bowlers.begin(), bowlers.end(), sortName);
		//std::cout << bowlers[3].getScores()[18] << std::endl; 
		printFrame(bowlers,outfile);
		
		
		outfile << endl;
		
		std::sort(bowlers.begin(), bowlers.end(), sortScores);
		
		printWinner(bowlers,outfile);
	}
}