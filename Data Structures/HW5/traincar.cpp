// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

void PushBack(TrainCar * &thomas, TrainCar * carType){
	
	if(thomas == NULL){
		thomas = carType;
		thomas -> next = NULL;
	}
	else{
		TrainCar* caboose = thomas;
		while (caboose->next !=NULL){
			caboose = caboose -> next;
		}
		caboose -> next = carType;
		carType -> next = NULL;
		if (carType -> prev != NULL) {
			carType -> prev -> next = NULL;
		}
		carType -> prev = caboose;

	}
}

void DeleteAllCars(TrainCar* remove){
	TrainCar* temp = remove;
	while (temp !=NULL){
		temp = temp -> next;
		delete remove;
		remove = temp;
	}
	delete temp;
}

std::vector<TrainCar*> ShipFreight(TrainCar*& tankEngines, TrainCar*& freightCars, float minSpeed, int maxCars) {
	std::vector<TrainCar*> trains;
	TrainCar* james = NULL;
	TrainCar* engineer = tankEngines;
	TrainCar* shuntingTrucks = freightCars;
	while(engineer != NULL && shuntingTrucks != NULL) {
		int numEngines = 0;
		int numFreightCars = 0;
		TrainCar* nextEngineer = engineer->next;
		
		if (nextEngineer != NULL)
			nextEngineer->prev = NULL;
		PushBack(james, engineer);
		engineer = nextEngineer;
		numEngines++;
		
		while(CalculateSpeed(james) >= minSpeed && (numEngines + numFreightCars) < maxCars && shuntingTrucks!=NULL) {
			TrainCar* nextShuntingTrucks = shuntingTrucks -> next;
			if (nextShuntingTrucks != NULL){
				nextShuntingTrucks->prev = NULL;
			}
			PushBack(james, shuntingTrucks);
			
			// If speed < minSpeed, either remove last freight or add new engine
			if(CalculateSpeed(james) < minSpeed) {
				// If at least 4 spots are open for new freights, then add a new engine
				if (maxCars - (numEngines + numFreightCars) >= 4+1 && engineer != NULL) {
					TrainCar* nextEngineer = engineer->next;
					if (nextEngineer != NULL)
						nextEngineer->prev = NULL;
					
					// Add engine to front
					engineer -> next = james;
					james -> prev = engineer;
					james = engineer;
					
					
					numEngines++;
					numFreightCars++;
					engineer = nextEngineer;
					shuntingTrucks = nextShuntingTrucks;
				} else {
					TrainCar* lastFreight = james;
					while (lastFreight->next != NULL){
						lastFreight = lastFreight->next;
					}
					lastFreight->prev->next = NULL;
					lastFreight->prev = NULL;
					lastFreight->next = nextShuntingTrucks;
					if (nextShuntingTrucks != NULL) {
						nextShuntingTrucks->prev = lastFreight;
					}
					shuntingTrucks = lastFreight;
					break;
				}
			} else {
				numFreightCars++;
				shuntingTrucks = nextShuntingTrucks;
			}
			//shuntingTrucks -> prev = NULL;
		}
		
		trains.push_back(james);
		james = NULL;

		//engineer = engineer -> next;
		//engineer -> prev = NULL;
	}
	tankEngines = engineer;
	freightCars = shuntingTrucks; 
	return trains;
}



float CalculateSpeed(TrainCar*& train){
	int weight  = 0;
	int numE = 0;
	TrainCar* percy = train;
	while(percy != NULL){
		if(percy -> isEngine()){
			numE++;
			weight = weight + 150;
		}
		else if(percy -> isFreightCar()){
			weight = weight + percy -> getWeight();
		}
		else{
			weight = weight + 50;
		}
		percy = percy -> next;
	}
	float speed1 = numE * 3000 *0.1 * 550 * 3600;
	float speed2 = weight * 0.2 * 20 * 5280;
	float speed =speed1/speed2;
	//std::cout << speed << std::endl;
	return speed;
}

void TotalWeightAndCountCars(TrainCar* train, int& tWeight, int& numEngines, int& numFreights, int& numPassengers, int& numDining, int& numSleep){
	TrainCar* gordon = train;
	tWeight = 0;
	numEngines = 0;
	numDining = 0;
	numFreights = 0;
	numPassengers = 0;
	numSleep = 0;
	while(gordon!=NULL){
		if((*gordon).isEngine()){
			++numEngines;
			tWeight = tWeight +150;
		}
		else if((*gordon).isFreightCar()){
			tWeight = (*gordon).getWeight() + tWeight;
			++numFreights;
		}
		else if((*gordon).isPassengerCar()){
			tWeight = tWeight + 50;
			++numPassengers;	
		}
		else if((*gordon).isDiningCar()){
			tWeight = tWeight + 50;
			++numDining;
		}
		else if((*gordon).isSleepingCar()){
			tWeight = tWeight + 50;
			++numSleep;
		}
		gordon = gordon->next;
	}
}

float AverageDistanceToDiningCar(TrainCar* train){
	std::vector<TrainCar*> vecTrain;
	std::vector<int> dinners;
	int count = 0;
	int sum = 0;
	int numPassenger = 0;
	TrainCar* henry = train;
	while(henry != NULL) {
		vecTrain.push_back(henry);
		if(henry -> isDiningCar()){
			dinners.push_back(count);
		}
		count++;
		henry = henry -> next;
	}
	for(unsigned int i =0; i <vecTrain.size(); i++){
		int min = 99999;
		if(vecTrain[i] -> isPassengerCar()){
			numPassenger++;
			for(unsigned int j = 0; j<dinners.size(); j++){
				if(abs(i-j)<min){
					min = abs(i-j);
				}
			}
			sum += min;
		}
	}
	
	return float(sum/numPassenger);
}

void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3){
	train2 = train1;
	TrainCar* toby = train1;
	TrainCar* emily = NULL;
	int carsCount = 0;
	int engineCount = 0;
	
	if(toby->next != NULL)
	{
		train3 = toby;
		(*emily).next = NULL;
		(*train3).prev = NULL;
	}
	
	//TrainCar* temp = cars;
	int totalCars = 0;
	while (toby != NULL)
	{
		totalCars++;
		toby = toby->next;
	}
	for(int i =0; i<totalCars/2; i++){
		if((*toby).isEngine()){
			engineCount++;
		}
		toby = (*toby).next;
	}
	
	if(engineCount == 1){
		for(int i =0; i<totalCars; i++){
			toby = (*toby).next;
			if(i == totalCars/2){
				train2 = toby;
				train3 = toby->next;
				train3-> prev = NULL;
				train2 -> next = NULL;
				break;
			}
		}
	}
	
	else if(engineCount == 2){
		TrainCar* engine2;
		for(int i =0; i<totalCars/2; i++){
			if((*toby).isEngine()){
				engineCount++;
				if(engineCount == 2){
					engine2 = toby;
					toby= toby->next;
					toby -> prev = toby;
				}
			}
			toby = (*toby).next;
		}
		for(int i =0; i<totalCars; i++){
			toby = (*toby).next;
			if(i == totalCars/2){
				train2 = toby;
				train3 = toby -> next;
				train3 -> prev = engine2;
				train3 -> prev = NULL;
				train2 -> next = NULL;
				break;
			}
		}
	}
	
	else if(engineCount == 0){
		TrainCar* engine2;
		for(int i =totalCars/2; i<totalCars; i++){
			if((*toby).isEngine()){
				engineCount++;
				if(engineCount == 1){
					engine2 = toby;
					toby= toby->next;
					toby -> prev = toby;
				}
			}
			toby = (*toby).next;
		}
			train2 = toby;
			train3 = toby -> next;
			train2 -> prev = engine2;
			train2 -> next = NULL;
			train3 -> prev = NULL;
		
		
	}
	train1 = NULL;
	
}

int ClosestEngineToSleeperCar(TrainCar* train){
	std::vector<TrainCar*> vecTrain;
	std::vector<int> slepts;
	std::vector<int> closest;
	int count = 0;
	int sum = 0;
	int numE = 0;
	TrainCar* edward = train;
	while(edward != NULL) {
		vecTrain.push_back(edward);
		if(edward -> isSleepingCar()){
			slepts.push_back(count);
		}
		count++;
		edward = edward -> next;
	}
	for(unsigned int i =0; i <vecTrain.size(); i++){
		int min = 99999;
		if(vecTrain[i] -> isEngine()){
			numE++;
			for(unsigned int j = 0; j<slepts.size(); j++){
				if(abs(i-j)<min){
					min = abs(i-j);
				}
			}
			closest.push_back(min);
		}
	}
	std::sort(closest.begin(),closest.end());
	int minimum = closest[0];
	return minimum;
}
