#include <vector>
#include <string>
#include "ship.h"
using namespace std;

#ifndef BATTLEBOARD_H
#define BATTLEBOARD_H

class BattleBoard{
	public:
		BattleBoard(int x, int y, vector<int> rowCount, vector<int> colsCount, vector<Ship> ships, vector<int> unknown);
		int getRows();
		int getCols();
		bool addShip(Ship ship, vector<int> rowCount, vector<int> colsCount, vector<string> &shipHash);
		//bool addShipRecursion(vector<Ship> ships,vector<int> rowCount, vector<int> colsCount, vector<string> &shipHash);
		void printBattleBoard(int x, int y, vector<int> rowCount, vector<int> colsCount);
		void solution(vector<string> hash, vector<Ship> ships);
	private:
		vector<vector<string> >gameboard;	
};
#endif