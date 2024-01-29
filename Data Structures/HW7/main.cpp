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
                std::cerr << "Problem opening " << filename << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename << " for reading locations." << std::endl;
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

            printAllUsersWithinDistance(locations, outfile, start_id, max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile, start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(), adj_lists.find(start_id), offset);
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
	while(loadfile >> str){
		string id1;
		string id2;
		id1 = str;
		loadfile >> id2;
		
		stringstream ss;
		ss << id1;
		long num2;
		ss >> num2;
		//cout<<num2<< endl;
		
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
	for(itr = locations.begin(); itr != locations.end(); ++itr){
		key = itr->first;
		//cout << start_id << endl;
		//cout << key << endl;
		if(key == start_id){
			start_xy =  itr->second;
			count++;
			break;
		}
	}
	if(count == 0){
		outfile << "User ID " << start_id << " does not have a recorded location." << endl;
	}
	else{
		int count2 =0;
		for(itr = locations.begin(); itr != locations.end(); ++itr){
			long key2 = itr-> first;
			vector<float> start_xy2= itr -> second;
			distance = distanceEarth(start_xy[0],start_xy[1],start_xy2[0],start_xy2[1]);
			//cout<<distance << endl;
			distance = floor(distance);
			if(distance < max_distance && distance > 0){
				if(count2==0){
					outfile << "User IDs within " << max_distance << " km of user " << key<< ":"<<endl;
				}
				count2++;
				distances[distance].push_back(key2);
			}
		}
		if(count2==0){
			outfile << "There are no users within " << max_distance << " km of user " << start_id<<endl;
		}
		else{
			long key3;
			vector<long> iD;
			
			for(itr2 = distances.begin(); itr2 != distances.end(); ++itr2){
				key3 = itr2->first;
				iD = itr2 -> second;
				//cout << iD.size() << endl;
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
	for(itr = adj_lists.begin(); itr != adj_lists.end(); ++itr){
		//int key = itr->first;
		
		vector<string> value = itr->second;
		temp.push_back(value.size());
		//cout << value.size() << endl;
	}
	while(count != adj_lists.size()){
		int num = std::count(temp.begin(),temp.end(),i);
		temp2.push_back(num);
		count = count + num;
		i++;
		
	}
	for(unsigned int j = 0; j<temp2.size(); ++j){
		if(temp2[j] > 0){
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
	//map < string,int > :: const_iterator p;
	for(itr = adj_lists.begin(); itr != adj_lists.end(); ++itr){
		long key = itr->first;
		//cout << itr->first << endl;
		vector<string> value = itr->second;
		
		outfile << " " << key <<": Degree " << value.size() << endl;
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
 
 
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,const ID_TYPE& start_id, unsigned int degree){
	int count = 0;
	vector<string> friendo;
	vector<long> degrees;
	map < long,vector<string> > ::const_iterator itr;
	map < float,vector<long> > ::const_iterator itr2;
	map< long, vector<string> > ::const_iterator p;
	
	
	for(p=adj_lists.begin(); p!=adj_lists.end(); ++p){
		long key1 = p->first;
		if(key1==start_id){
			friendo = p->second;
			count++;
			break;
		}
	}
	if(count == 0){
		outfile << "There is no user with friends and ID " << start_id << endl;
	}
	else{
		vector<string> homie;
		//cout<<friendo.size() << endl;
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
		if(degrees.size()==0){
			outfile << "User " << start_id << " has " << degrees.size() << " friend(s) with degree " << degree << endl;
		}
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
	map< long, vector<string> > ::const_iterator p;
	
	
	for(p=adj_lists.begin(); p!=adj_lists.end(); ++p){
		long key1 = p->first;
		
		if(key1==start_id){
			friendo = p->second;
			count++;
			break;
		}
	}
	if(count == 0){
		outfile << "There is no user with friends and ID " << start_id << endl;
	}
	else{
		count = 0;
		for(itr = locations.begin(); itr != locations.end(); ++itr){
			key = itr->first;
			//cout << start_id << endl;
			//cout << key << endl;
			if(key == start_id){
				start_xy =  itr->second;
				count++;
				break;
			}
		}
		if(count == 0){
			outfile << "User ID " << start_id << " does not have a recorded location." << endl;
		}
		else{
			int count2 =0;
			for(itr = locations.begin(); itr != locations.end(); ++itr){
				long key2 = itr-> first;
				vector<float> start_xy2= itr -> second;
				distance = distanceEarth(start_xy[0],start_xy[1],start_xy2[0],start_xy2[1]);
				//cout<<key2 << endl;
				//distance = floor(distance);
				bool homie = false;
				//cout<<friendo.size() << endl;
				for(unsigned int i = 0; i < friendo.size(); ++i){
					stringstream ss;
					ss << friendo[i];
					long num2;
					ss >> num2;
					//cout<<num2 << endl;
					if(num2 == key2){
						homie = true;
						break;
					}
				}
				if(distance < max_distance && distance > 0 && homie){
					if(count2==0){
						outfile << "Friends within " << max_distance << " km of user " << key<< ":"<<endl;
					}
					count2++;
					distances[distance].push_back(key2);
				}
			}
			if(count2==0){
				outfile << "There are no friends within " << max_distance << " km of user " << start_id<<endl;
			}
			else{
				float key3;
				vector<long> iD;
				
				for(itr2 = distances.begin(); itr2 != distances.end(); ++itr2){
					key3 = itr2->first;
					iD = itr2 -> second;
					//cout << iD.size() << endl;
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
	if(count==0){
		outfile << "There is no user with the requested ID" << endl;
	}
	else{
		keypos = startKey + offset;
		keyneg = startKey - offset;
		//cout << keypos << endl;
		//cout << keyneg << endl;
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
		if(vec.size()==0){
			outfile << "There are no users with an ID within +/-" << offset << " of " << startKey << endl;
		}
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



