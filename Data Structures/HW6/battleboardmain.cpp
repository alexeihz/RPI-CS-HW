#include "battleboard.h"
#include "ship.h"
#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cctype>
using namespace std;

void addShipRecursion(BattleBoard game, vector<Ship> ships,vector<int> rowCount, vector<int> colsCount, vector<string> &hash){
	if(game.addShip(ships[0],rowCount,colsCount,hash)==true){
		if(ships.size()>0){
			ships.erase(ships.begin(), ships.begin()+1);
			addShipRecursion(game,ships,rowCount,colsCount,hash);
		}
	}
	else{
		ships[0].setHorizontal();
		if(game.addShip(ships[0], rowCount,colsCount, hash)){
			if(ships.size()>0){
				ships.erase(ships.begin(), ships.begin()+1);
				addShipRecursion(game,ships,rowCount,colsCount,hash);
			}
		}
	}
}

int main(int argc, char* argv[]){
	//parse file
	ifstream infile(argv[1]);
	if(argc <=2){
		
		if (!infile.good()) {
			std::cerr << "Can't open " << argv[1] << " to read.\n";
			exit(1);
		}
		
		string str;
		string yStr, xStr;
		string num;
		int y, x;
		vector<int> vecCols, vecRows;
		vector<string> constraints;
		vector<int> unknown;
		vector<Ship> ships;
		vector<string> hashShip;
		vector<string> hashBoard;
		
		
		while(infile >> str){
			if(str =="board"){
				infile >> xStr;
				stringstream ss;
				ss << xStr;
				int num2;
				ss >> num2;
				x = num2;
				
				stringstream ss2;
				infile >> yStr;
				ss2 << yStr;
				int num3;
				ss2 >> num3;
				y = num3;
				
			}
			if(str == "rows"){
				for(int i = 0; i < x; ++i){
					infile >> num;
					
					if(num == "?"){
						int num2 = -1;
						vecRows.push_back(num2);
					}
					else{
						stringstream ss;
						ss << num;
						int num2;
						ss >> num2;
						vecRows.push_back(num2);
					}
				}
			}
			else if(str == "cols"){
				for(int i = 0; i < y; ++i){
					infile >> num;
					if(num == "?"){
						int num2 = -1;
						vecCols.push_back(num2);
					}
					else{
						stringstream ss;
						ss << num;
						int num2;
						ss >> num2;
						vecCols.push_back(num2);
					}
				}
			}
			else if(str == "submarine"){
				ships.push_back(Ship("submarine",1));
			}
			else if(str == "destroyer"){
				ships.push_back(Ship("destroyer",2));
			}
			else if(str == "cruiser"){
				ships.push_back(Ship("cruiser",3));
			}
			else if(str == "battleship"){
				ships.push_back(Ship("battleship",4));
			}
			else if(str == "carrier"){
				ships.push_back(Ship("carrier",5));
			}
			else if(str == "cargo"){
				ships.push_back(Ship("cargo",6));
			}
			else if(str == "tanker"){
				ships.push_back(Ship("tanker",7));
			}
			else if(str == "unknown"){
				ships.push_back(Ship("unknown",-1));
			}
			else if (str == "constraint") {
				infile >> yStr; 
				infile >> xStr;
				infile >> num;
				constraints.push_back(xStr);
				constraints.push_back(yStr);
				constraints.push_back(num);
			}
		}
		BattleBoard game(x,y,vecRows,vecCols,ships,unknown);
		addShipRecursion(game,ships,vecRows,vecCols,hashShip);
		
		game.printBattleBoard(x,y,vecRows,vecCols);
		string hashString = "";
		for(unsigned int p = 0; p < hashShip.size(); ++p){
			hashString += hashShip[p];
		}
		hashBoard.push_back(hashString);
		game.solution(hashBoard,ships);
		
	}	
	
	else if(argc==2){
		std::string argStr = argv[2];
		if(argStr == "find_all_solutions"){
			if (!infile.good()) {
				std::cerr << "Can't open " << argv[1] << " to read.\n";
				exit(1);
			}
		
			string str;
			string yStr, xStr;
			string num;
			int y, x;
			vector<int> vecCols, vecRows;
			vector<string> constraints;
			vector<int> unknown;
			vector<Ship> ships;
			vector<string> hashShip;
			vector<string> hashBoard;
			
			while(infile >> str){
				if(str =="board"){
					infile >> xStr;
					stringstream ss;
					ss << xStr;
					int num2;
					ss >> num2;
					x = num2;
					
					stringstream ss2;
					infile >> yStr;
					ss2 << yStr;
					int num3;
					ss2 >> num3;
					y = num3;
					
				}
				if(str == "rows"){
					for(int i = 0; i < x; ++i){
						infile >> num;
						
						if(num == "?"){
							int num2 = -1;
							vecRows.push_back(num2);
						}
						else{
							stringstream ss;
							ss << num;
							int num2;
							ss >> num2;
							vecRows.push_back(num2);
						}
					}
				}
				else if(str == "cols"){
					for(int i = 0; i < y; ++i){
						infile >> num;
						if(num == "?"){
							int num2 = -1;
							vecCols.push_back(num2);
						}
						else{
							stringstream ss;
							ss << num;
							int num2;
							ss >> num2;
							vecCols.push_back(num2);
						}
					}
				}
				else if(str == "submarine"){
					ships.push_back(Ship("submarine",1));
				}
				else if(str == "destroyer"){
					ships.push_back(Ship("destroyer",2));
				}
				else if(str == "cruiser"){
					ships.push_back(Ship("cruiser",3));
				}
				else if(str == "battleship"){
					ships.push_back(Ship("battleship",4));
				}
				else if(str == "carrier"){
					ships.push_back(Ship("carrier",5));
				}
				else if(str == "cargo"){
					ships.push_back(Ship("cargo",6));
				}
				else if(str == "tanker"){
					ships.push_back(Ship("tanker",7));
				}
				else if(str == "unknown"){
					ships.push_back(Ship("unknown",-1));
				}
				else if (str == "constraint") {
					infile >> yStr; 
					infile >> xStr;
					infile >> num;
					constraints.push_back(xStr);
					constraints.push_back(yStr);
					constraints.push_back(num);
				}
			}
			BattleBoard game(x,y,vecRows,vecCols,ships,unknown);
			addShipRecursion(game,ships,vecRows,vecCols,hashShip);
			
			game.printBattleBoard(x,y,vecRows,vecCols);
				string hashString = "";
				for(unsigned int p = 0; p < hashShip.size(); ++p){
					hashString += hashShip[p];
				}
				hashBoard.push_back(hashString);
				game.solution(hashBoard,ships);
		}
		else{
			std::cerr << "Not find_all_solutions \n";
			exit(1);
		}
	}
	return 0;
}