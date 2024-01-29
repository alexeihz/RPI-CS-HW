// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//

#include "traincar.h"
#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>
#include <vector>

void PushBack(TrainCar* &train, TrainCar * carType);
void DeleteAllCars(TrainCar * first);
std::vector<TrainCar*> ShipFreight(TrainCar*& engines, TrainCar*& freightCars, float minSpeed, int maxCars);
void TotalWeightAndCountCars(TrainCar* train, int& tWeight, int& numEngines, int& numFreights, int& numPassengers, int& numDining, int& numSleep);
float CalculateSpeed(TrainCar*& train);
float AverageDistanceToDiningCar(TrainCar* train);
int ClosestEngineToSleeperCar(TrainCar* train);
void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3);