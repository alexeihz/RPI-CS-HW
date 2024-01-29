#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath> 
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <sstream>
#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif
using namespace std;

//TODO: You must fill in all ?????? with the correct types.
typedef long ID_TYPE; //Type for user IDs
typedef pair<float,float> COORD_TYPE; //Type for a coordinate (latitude and longitude)
typedef map <long, vector<string> > ADJ_TYPE; //Adjacency Lists type
typedef map <long, vector<float> > GEO_TYPE; //Positional "dictionary"

//Function forward declarations. DO NOT CHANGE these. 
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0] 
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!" 
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!" 
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id, 
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile, 
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}



// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile){
	string str;
	//reads file and stores data in 'adj_lists'
	while(loadfile >> str){
		string id1;
		string id2;
		id1 = str;
		loadfile >> id2;
		
		stringstream ss;
		ss << id1;
		long num2;
		ss >> num2;
		
		adj_lists[num2].push_back(id2);
	}
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile){
	long key;
	//reads file and stores data in 'locations'
	while(loadfile >> key){
		float location1;
		float location2;
		vector<float> veclocation;
		loadfile >> location1;
		loadfile >> location2;
		veclocation.push_back(location1);
		veclocation.push_back(location2);
		locations[key] = veclocation;
	}
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile, const ID_TYPE& start_id, double max_distance){
	map<long,vector<long> > distances;
	int count = 0;
	float distance;
	long key;
	vector<float> start_xy;
	map < long,vector<float> > ::const_iterator itr;
	map < long,vector<long> > ::const_iterator itr2;
	//iterates through 'locations' to find a value equal to 'start_id' 
	for(itr = locations.begin(); itr != locations.end(); ++itr){
		key = itr->first;
		if(key == start_id){
			start_xy =  itr->second;
			count++;
			break;
		}
	}
	//if a value equal to 'start_id' isn't found then outputs message below
	if(count == 0){
		outfile << "User ID " << start_id << " does not have a recorded location." << endl;
	}
	//if a value equal to 'start_id' is found then iterate through 'locations' again to find other users within 'max_distance'
	//adds any users to map 'distances'
	else{
		int count2 =0;
		for(itr = locations.begin(); itr != locations.end(); ++itr){
			long key2 = itr-> first;
			vector<float> start_xy2= itr -> second;
			distance = distanceEarth(start_xy[0],start_xy[1],start_xy2[0],start_xy2[1]);
			distance = floor(distance);
			if(distance < max_distance && distance > 0){
				//only prints at the top of the list of users within 'max_distance'
				if(count2==0){
					outfile << "User IDs within " << max_distance << " km of user " << key<< ":"<<endl;
				}
				count2++;
				distances[distance].push_back(key2);
			}
		}
		//if users withen 'max_distance' aren't found then outputs message below
		if(count2==0){
			outfile << "There are no users within " << max_distance << " km of user " << start_id<<endl;
		}
		//if users are found iterate through map 'distances'
		//prints out list of the distances away from start_id and how many users are this far away at each distance
		else{
			long key3;
			vector<long> iD;
			
			for(itr2 = distances.begin(); itr2 != distances.end(); ++itr2){
				key3 = itr2->first;
				iD = itr2 -> second;
				outfile << " " << key3 << " km: ";
			
				for(unsigned int i = 0; i<iD.size(); ++i){
					if(i+1 == iD.size()){
						outfile << iD[i] << endl;
					}	
					else{
						outfile << iD[i] << " ";
					}
				}	
			}
			
		}
	}
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
	outfile << "Histogram for " << adj_lists.size() << " users:" << endl;
	int i = 1;
	unsigned int count = 0;
	map < long,vector<string> > ::const_iterator itr;
	vector<int> temp;
	vector<int> temp2;
	//iterates through 'adj_lists'
	for(itr = adj_lists.begin(); itr != adj_lists.end(); ++itr){
		vector<string> value = itr->second;
		//adds size of value to 'temp'
		temp.push_back(value.size());
	}
	//Ends when 'count' equals the size of 'adj_lists'
	while(count != adj_lists.size()){
		//counts the amount of numbers in 'temp' that are equal to 'i'
		int num = std::count(temp.begin(),temp.end(),i);
		temp2.push_back(num);
		count = count + num;
		i++;
	}
	//loops through 'temp2' and prints out proper degree if degree is >=1
	for(unsigned int j = 0; j<temp2.size(); ++j){
		if(temp2[j] >=1){
			outfile << " Degree " << j + 1 <<": " << temp2[j] << endl;
		}
	}
}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
	outfile << "Degrees for " << adj_lists.size() << " users:" << endl;
	map < long,vector<string> > ::const_iterator itr;
	//iterates through 'adj_lists' and prints the degree if the degree is >=1
	for(itr = adj_lists.begin(); itr != adj_lists.end(); ++itr){
		long key = itr->first;
		vector<string> value = itr->second;
		if(value.size() >= 1){
			outfile << " " << key <<": Degree " << value.size() << endl;
		}
	}
}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile, const ID_TYPE& start_id, unsigned int degree){
	int count = 0;
	vector<string> friendo;
	vector<long> degrees;
	map < long,vector<string> > ::const_iterator itr;
	map < float,vector<long> > ::const_iterator itr2;
	map< long, vector<string> > ::const_iterator p;
	
	//iterates through 'adj_lists' to find 'start_id' 
	for(p=adj_lists.begin(); p!=adj_lists.end(); ++p){
		long key1 = p->first;
		if(key1==start_id){
			friendo = p->second;
			count++;
			break;
		}
	}
	//if 'start_id' isn't found then outputs message below
	if(count == 0){
		outfile << "There is no user with friends and ID " << start_id << endl;
	}
	//if 'start_id' is found then iterate through 'adj_lists' again to find other friends with the right 'degree'
	//adds any friends to vector 'degrees'
	else{
		vector<string> homie;
		for(itr = adj_lists.begin(); itr != adj_lists.end(); ++itr){
			long key = itr->first;
			for(unsigned int i = 0; i < friendo.size(); ++i){
				stringstream ss;
				ss << friendo[i];
				long num2;
				ss >> num2;
				if(key == num2){
					homie = itr -> second;
					if(homie.size() == degree){
						degrees.push_back(key);
					}
				}
			}
		}
		//if 'start_id' has no friends with the degree then output message below
		if(degrees.size()==0){
			outfile << "User " << start_id << " has " << degrees.size() << " friend(s) with degree " << degree << endl;
		}
		//outputs friends with 'degree'
		else{
			outfile << "User " << start_id << " has " << degrees.size() << " friend(s) with degree " << degree <<": ";
			for(unsigned int j =0; j<degrees.size(); ++j){
				if(j+1 == degrees.size()){
					outfile << degrees[j] << endl;
				}	
				else{
					outfile << degrees[j] << " ";
				}
			}
		}
	}
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, std::ofstream& outfile, const ID_TYPE& start_id, double max_distance){
	map<float,vector<long> > distances;
	vector<string> friendo;
	int count = 0;
	float distance;
	long key;
	vector<float> start_xy;
	map < long,vector<float> > ::const_iterator itr;
	map < float,vector<long> > ::const_iterator itr2;
	map	< long, vector<string> > ::const_iterator p;
	
	//iterates through 'adj_lists' to find 'start_id
	for(p=adj_lists.begin(); p!=adj_lists.end(); ++p){
		long key1 = p->first;
		
		if(key1==start_id){
			friendo = p->second;
			count++;
			break;
		}
	}
	//if 'start_id' isn't found then outputs message below
	if(count == 0){
		outfile << "There is no user with friends and ID " << start_id << endl;
	}
	//iterates through 'locations' to find 'start_id
	else{
		count = 0;
		for(itr = locations.begin(); itr != locations.end(); ++itr){
			key = itr->first;
			if(key == start_id){
				start_xy =  itr->second;
				count++;
				break;
			}
		}
		//if 'start_id' isn't found then outputs message below
		if(count == 0){
			outfile << "User ID " << start_id << " does not have a recorded location." << endl;
		}
		else{
			//if 'start_id' is found then iterate through 'locations' again to find other friends
			//adds any friends to map 'distances'
			int count2 =0;
			for(itr = locations.begin(); itr != locations.end(); ++itr){
				long key2 = itr-> first;
				vector<float> start_xy2= itr -> second;
				distance = distanceEarth(start_xy[0],start_xy[1],start_xy2[0],start_xy2[1]);
				bool homie = false;
				for(unsigned int i = 0; i < friendo.size(); ++i){
					stringstream ss;
					ss << friendo[i];
					long num2;
					ss >> num2;
					if(num2 == key2){
						homie = true;
						break;
					}
				}
				if(distance < max_distance && distance > 0 && homie){
					//only prints at the top of the list of friends within 'max_distance'
					if(count2==0){
						outfile << "Friends within " << max_distance << " km of user " << key<< ":"<<endl;
					}
					count2++;
					distances[distance].push_back(key2);
				}
			}
			//if there are no friends within 'max_distance', outputs message below
			if(count2==0){
				outfile << "There are no friends within " << max_distance << " km of user " << start_id<<endl;
			}
			//outputs friends within 'max_distance' of user
			else{
				float key3;
				vector<long> iD;
				
				for(itr2 = distances.begin(); itr2 != distances.end(); ++itr2){
					key3 = itr2->first;
					iD = itr2 -> second;
					outfile << " " << key3 << " km: ";
				
					for(unsigned int i = 0; i<iD.size(); ++i){
						if(i+1 == iD.size()){
							outfile << iD[i] << endl;
						}	
						else{
							outfile << iD[i] << " ";
						}
					}	
				}
				
			}
		}
	}
}

/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, ADJ_TYPE::const_iterator end, ADJ_TYPE::const_iterator start_it, unsigned int offset){
	map < long,vector<string> > ::const_iterator itr;
	int count =0;
	long startKey;
	long keypos;
	long keyneg;
	for(itr = begin; itr != end; ++itr){
		if(itr == start_it){
			startKey = itr -> first;
			count++;
		}
	}
	//if there is no user with requested ID, outputs message below
	if(count==0){
		outfile << "There is no user with the requested ID" << endl;
	}
	//if there is a usere with the requested ID, add keys that are +/- 'offest' of 'startKey' to 'vec'
	else{
		keypos = startKey + offset;
		keyneg = startKey - offset;
		vector<long> vec;
		for(itr = begin; itr != end; ++itr){
			long key = itr -> first;
			if(key != startKey &&  key >= startKey && key <= keypos){
				vec.push_back(key);
			}
			else if(key != startKey && key <= startKey && key >= keyneg){
				vec.push_back(key);
			}
		}
		//if there aren't any users with an ID within +/- 'offest' of 'startKey', outputs message below
		if(vec.size()==0){
			outfile << "There are no users with an ID within +/-" << offset << " of " << startKey << endl;
		}
		//prints users with an ID within +/- 'offset' of 'startKey'
		else{
			outfile << "Users with an ID within +/-" << offset << " of " << startKey << ": "; 
			for(unsigned int j =0; j < vec.size(); ++j){
				if(j+1 == vec.size()){
					outfile << vec[j] << endl;
				}	
				else{
					outfile << vec[j] << " ";
				}
			}
		}
	}
}