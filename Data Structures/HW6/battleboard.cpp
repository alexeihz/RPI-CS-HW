#include <sstream>
#include "battleboard.h"
#include "ship.h"
#include <iostream>
#include <string>
using namespace std;

BattleBoard::BattleBoard(int x, int y, vector<int> rowCount, vector<int> colsCount, vector<Ship> ships, vector<int> unknown){
	for(int i = 0; i < x; ++i){
		vector<string> vec;
		for(int j = 0; j < y; ++j){
			vec.push_back(" ");
		}
		gameboard.push_back(vec);
	}
}

int BattleBoard::getRows(){
	return gameboard[0].size();
}
int BattleBoard::getCols(){
	return gameboard.size();
}

bool BattleBoard::addShip(Ship ship, vector<int> rowCount, vector<int> colsCount, vector<string> &hash){
	if(ship.isHorizontal() == true){
		int x =rowCount.size();
		int y =colsCount.size();
		for(int i = 0; i< x; ++i){
			for(int j = 0; j < y; ++j){
				if(ship.getLength() <= rowCount[j] && ship.getLength() <= x-j && gameboard[i][j]==" "){
					if(((y-i==1 && x-j==1) || gameboard[i+1][j+1] == " ") && ((x-j == 1) || gameboard[i][j+1] == " ") &&  ((y-i == 1) || gameboard[i+1][j]==" ") && ((x==0 && y==0) || gameboard[i-1][j-1]==" ") && (x==0 || gameboard[i-1][j]==" ") && (y ==0 || gameboard[i][j-1]==" ")){
						for(int k = i; k < y; ++k){
							if(ship.getLength() > colsCount[k]){
								return false;
							}
						}
						string str;
						stringstream ss;
						ss << i << j << ship.getLength() << "1";
						ss >> str;
						hash.push_back(str);
						if(ship.getLength()==1){
							gameboard[i][j] = "o";
						}
						else if(ship.getLength()>=2){
							gameboard[i][j] = "<";
							rowCount[i]--;
							
							for(int h =1; h<ship.getLength()-1; ++h){
								gameboard[i+h][j] = "X";
								rowCount[i]--;
							}
							
							gameboard[i+ship.getLength()-1][j] = ">";
							rowCount[i]--;
						}
						return true;
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
		}
	}
	
	else{
		int y =colsCount.size();
		int x =rowCount.size();
		for(int i = 0; i< x; ++i){;
			
			for(int j = 0; j < y; ++j){
				if(ship.getLength() <= colsCount[j] && ship.getLength() <= y-j){
					if(((y-i==1 && x-j==1) || gameboard[i+1][j+1] == " ") && ((x-j == 1) || gameboard[i][j+1] == " ") && ((y-i == 1) || gameboard[i+1][j]==" ") && ((x==0 && y==0) || gameboard[i-1][j-1]==" ") && (x==0 || gameboard[i-1][j]==" ") && (y ==0 || gameboard[i][j-1]==" ")){
						for(int k = i; k < x; ++k){
							if(ship.getLength() > rowCount[k]){
								return false;
							}
						}
						string str;
						stringstream ss;
						ss << i << j << ship.getLength() << "2";
						ss >> str;
						hash.push_back(str);
						if(ship.getLength()==1){
							gameboard[i][j] = "o";
						}
						else if(ship.getLength()>=2){
							gameboard[i][j] = "^";
							colsCount[i]--;
							
							for(int h =1; h<ship.getLength()-1; ++h){
								gameboard[i+h][j] = "X";
								colsCount[i]--;
							}
							
							gameboard[i+ship.getLength()-1][j] = "V";
							colsCount[i]--;
						}
						return true;
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
		}
	}
}



void BattleBoard::printBattleBoard(int x, int y, vector<int> rowCount, vector<int> colsCount){
	string str = "+";
	for(int i =0; i < y; ++i){
		str += "-";
	}
	str += "+";
	cout << str << endl;
	for(int i = 0; i < x; ++i){
		cout << "|";
		for(int j = 0; j < y; ++j){
			cout << gameboard[i][j];
		}
		cout << "|" << rowCount[i] << endl;
	}
	cout << str << endl;
	string str2 = " ";
	
	
	for(int i =0; i < y; ++i){
		if(colsCount[i]==-1){
			str2+="?";
		}
		else{
			stringstream ss;
			string str3;
			ss << colsCount[i];
			ss >> str3;
			str2 += str3;
		}
	}
	cout << str2 << endl;
}

void BattleBoard::solution(vector<string> hash, vector<Ship> ships){
	cout<< "Solution:" << endl;
	
	for(unsigned int i = 0; i<hash.size(); ++i){
		if(hash[i][2] == 1){
			cout << "submarine";
			cout << hash[i][0] << " " << hash[i][1] << " ";
			
		}
		if(hash[i][2] == 2){
			cout << "destroyer";
			cout << hash[i][0] << " " << hash[i][1] << " ";
			if(hash[i][3] == 1){
				cout << "horizontal";
			}
			else{
				cout << "vertical";
			}
			
		}
		if(hash[i][2] == 3){
			cout << "cruiser";
			cout << hash[i][0] << " " << hash[i][1] << " ";
			if(hash[i][3] == 1){
				cout << "horizontal";
			}
			else{
				cout << "vertical";
			}
			
		}
		if(hash[i][2] == 4){
			cout << "battleship";
			cout << hash[i][0] << " " << hash[i][1] << " ";
			if(hash[i][3] == 1){
				cout << "horizontal";
			}
			else{
				cout << "vertical";
			}
			
		}
		if(hash[i][2] == 5){
			cout << "carrier";
			cout << hash[i][0] << " " << hash[i][1] << " ";
			if(hash[i][3] == 1){
				cout << "horizontal";
			}
			else{
				cout << "vertical";
			}
			
		}
		if(hash[i][2] == 6){
			cout << "cargo";
			cout << hash[i][0] << " " << hash[i][1] << " ";
			if(hash[i][3] == 1){
				cout << "horizontal";
			}
			else{
				cout << "vertical";
			}
			
		}
		if(hash[i][2] == 7){
			cout << "tanker";
			cout << hash[i][0] << " " << hash[i][1] << " ";
			if(hash[i][3] == 1){
				cout << "horizontal";
			}
			else{
				cout << "vertical";
			}
			
		}
	}
	
}