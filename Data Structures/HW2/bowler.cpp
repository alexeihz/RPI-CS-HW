//file bowler.cpp
#include <algorithm>
#include <iostream>
#include "bowler.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

Bowler::Bowler() {}
Bowler::Bowler(const std::string& first, const std::string& last, const std::vector<int>& scores) {
	// u can do this
	this->first_name = first;
	this->last_name = last;
	this->scores = scores;
}

std::string Bowler::getFirstName() const {
	return first_name;
}
std::string Bowler::getLastName() const {
	return last_name;
}
int Bowler::getTotalScore() const {
	int score=0;
	int frameCount=0;
	int frame10 = 1;
	for(int i=0; i<scores.size();i++){
		if(frame10!=10 && (scores[i] == 10 && frameCount==1) || (frameCount==1 && scores[i-1] + scores[i] == 10)){
			score += scores[i] + scores[i+1];
			frameCount=0;
			frame10++;
			continue;
		}
		else if(frame10!=10 && scores[i]==10 && frameCount==0){
			score += scores[i] + scores[i+1] + scores[i+2];
			frameCount=0;
			frame10++;
			continue;
		}
		
		frameCount++;
		frame10++;
		if(frameCount==2){
			frameCount=0;
		}
		score = score + scores[i];
	}
	return score;
}
std::vector<int> Bowler::getScores() const {
	return scores;
}

bool sortName(const Bowler& a, const Bowler& b) {
	if(a.getLastName() != b.getLastName()){
		return a.getLastName() < b.getLastName();
	}
	return a.getFirstName() < b.getFirstName();
}

bool sortScores(const Bowler& a, const Bowler& b) {
	return a.getTotalScore() > b.getTotalScore();
}

void printWinner(const std::vector<Bowler>& a,std::ostream& outfile){
	int max = a[0].getFirstName().length() + a[0].getLastName().length();
	int tmp;
	for(int i=1; i<a.size(); i++){
		tmp = a[i].getFirstName().length() + a[i].getLastName().length() + 1;
		max = std::max(max,tmp);
	}
	for(int i=0;i<a.size();i++){
		std::string str = a[i].getFirstName() +" " + a[i].getLastName();
		while(str.length()<max){
			str+=" ";
		}
		
		if(a[i].getTotalScore()<10){
			str += "  ";
		}
		if(a[i].getTotalScore()>=10 && a[i].getTotalScore()<100 ){
			str += " ";
		}
		str +="  ";
		outfile << str << a[i].getTotalScore() << std::endl;
	}
}

void printFrame(const std::vector<Bowler>& a,std::ostream& outfile){
	
	int max = a[0].getFirstName().length() + a[0].getLastName().length()+1;
	int tmp;
	for(int i=1; i<a.size(); i++){
		tmp = a[i].getFirstName().length() + a[i].getLastName().length() + 1;
		max = std::max(max,tmp);
	}
	outfile << "------------------------------------------------------------------------------" << std::endl;
	for (int i=0;i<a.size();i++){
		std::string str = a[i].getFirstName() +" " + a[i].getLastName();
		while(str.length()<max){
			str+=" ";
		}
		str = "| " + str + " |" ;
		int frameCount=0;
		int frame10=1;
		int subFrame1 = 0;
		int subFrame2 = 2;
		for(int j=0;j<a[i].getScores().size();j++){
			std::ostringstream oss;
			oss << a[i].getScores()[j];
			if (a[i].getScores()[j] == 0){
				str += " -";
			}
			if(frame10!=10 && frameCount==1 && (a[i].getScores()[j] == 10 ||  a[i].getScores()[j-1] + a[i].getScores()[j] == 10)){
				str += " / |";
				frame10++;
				frameCount=0;
				continue;
			}
			if(frame10!=10 && a[i].getScores()[j] == 10 && frameCount==0){
				str += "   X |";
				frame10++;
				frameCount=0;
				continue;
			}
			if(frame10==10 && a[i].getScores()[j] == 10){
				str += " X";
				if(subFrame1==0){
					subFrame2 = 3;
				}
				subFrame1++;
				if(subFrame1 == subFrame2){
					str+=" |";
					break;
				}
				continue;
			}
			else if (frame10==10 && (a[i].getScores()[j] == 10 ||  a[i].getScores()[j-1] + a[i].getScores()[j] == 10)){
				str += " /";
				if(subFrame1==1){
					subFrame2=3;
				}
				subFrame1++;
				if(subFrame1 == subFrame2){
					str+=" |";
					break;
				}
				continue;
			}
			
			if(a[i].getScores()[j]!= 0 && a[i].getScores()[j]!=10){
				str += " " + oss.str();
				if(frame10==10 && subFrame1==2){
					str+= " |";
					break;
				}
			}
			frameCount++;
			if(frameCount==2){
				if(frame10==10){
					if(a[i].getScores()[j]==10){
						continue;
					}
					else{
						str+=" ";
					}
					str+="  |";
					frame10=1;
				}
				else{
					str+=" |";
					frameCount=0;
					frame10++;
				}
			}
		}
		
		outfile << str<< std::endl;
	//add scores to the bottom of each section
		frameCount=0;
		frame10=1;
		subFrame1 = 0;
		subFrame2 = 0;
		int addScore = 0;
		std::string str2 = "| ";
		for(int k=0; k<max;k++){
			str2 += " ";
		}
		str2+= " |";
		for(int j=0;j<a[i].getScores().size();j++){
			
			
			if(frame10!=10 && (a[i].getScores()[j] == 10 && frameCount==1) || (frameCount==1 && a[i].getScores()[j-1] + a[i].getScores()[j] == 10)){
				addScore += a[i].getScores()[j] + a[i].getScores()[j +1];
				std::ostringstream oss;
					oss << addScore;
					if(addScore < 10){
						str2+="   ";
					}
					if(addScore < 100 && addScore>=10){
						str2+="  ";
					}
					if(addScore < 1000 && addScore>=100){
						str2+=" ";
					}
					str2 += oss.str();
					str2+=" |";
					frameCount=0;
					frame10++;
					continue;
			}
			else if(frame10!=10 && a[i].getScores()[j]==10 && frameCount==0){
				addScore += a[i].getScores()[j] + a[i].getScores()[j +1] + a[i].getScores()[j +2];
				std::ostringstream oss;
					oss << addScore;
					if(addScore < 10){
						str2+="   ";
					}
					if(addScore < 100 && addScore>=10){
						str2+="  ";
					}
					if(addScore < 1000 && addScore>=100){
						str2+=" ";
					}
					str2 += oss.str();
					str2+=" |";
					frameCount=0;
					frame10++;
				continue;
			}
			frameCount++;
			addScore += a[i].getScores()[j];
			if(frameCount==2){
				if(frame10==10){
					std::ostringstream oss;
					oss << addScore;
					if(addScore < 10){
						str2+="     ";
					}
					if(addScore < 100 && addScore>=10){
						str2+="    ";
					}
					if(addScore < 1000 && addScore>=100){
						str2+="   ";
					}
					str2 += oss.str();
					str2+=" |";
					frameCount=0;
				}
				
				else{
					std::ostringstream oss;
					oss << addScore;
					if(addScore < 10){
						str2+="   ";
					}
					if(addScore < 100 && addScore>=10){
						str2+="  ";
					}
					if(addScore < 1000 && addScore>=100){
						str2+=" ";
					}
					str2 += oss.str();
					str2+=" |";
					frameCount=0;
					frame10++;
				}
				
			}
			
		}
		outfile << str2 << std::endl;
		outfile << "------------------------------------------------------------------------------" << std::endl;
	}
}

