//Animal.h
#include <string>

Class Animal{
public:
	Animal(const std::string& name);
	// ACCESSORS
	const std::string& getName() const;
	int getWeight() const;
	bool onLand() const;
	bool inWater() const;
	bool eatMeat() const;
	bool eatPlants() const;
	bool omnivore() const;
	bool amphibious() const;
	
	// MODIFIERS
	void setWeight(int weight);
	void setOnLand(bool onLand);
	void setInWater(bool inWater);
	void setEatMeat(bool eatMeat);
	void setEatPlants(bool eatPlants);
	
	
private:
	std::stirng name;
	int weight;
	bool inWater, onLand, eatMeat, eatPlants;
}