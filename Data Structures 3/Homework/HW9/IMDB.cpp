#include <iostream>
#include <stdio.h>
#include <map>
#include <fstream>
#include <ostream>
#include <sstream> 
#include "ds_hashset.h"
#include <set>

class hash_string_obj {
public:

	//hash function from lab modified
  unsigned int operator() ( const std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > > & key ) const {
    //  This implementation comes from 
    //  http://www.partow.net/programming/hashfunctions/
    //
    //  This is a general-purpose, very good hash function for strings.
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.first.size(); i++){
		for(unsigned int j = 0; j<key.first[i].size(); j++){
			for(unsigned int k = 0; k < key.first[i][j].length(); k++){
				hash ^= ((hash << 5) + key.first[i][j][k] + (hash >> 2));
			}
		}
	}  
    return hash;
  }   
  
};

//creates all 64 different combinations of partial movie data
void partial_hash(const std::vector<std::vector<std::string> >&one_movie_data, std::vector<std::vector<std::vector<std::string> > >& partials){
	int count = 1;
	std::vector<std::vector<std::string> > temp;
	std::vector<std::string> empty;
	empty.push_back("oof");
	partials.push_back(one_movie_data);
	while(partials.size() < 64){
		for(unsigned i = 0; i < one_movie_data.size(); ++i){
			temp = one_movie_data;
			temp[i] = empty;
			if(count > 1){
				std::vector<std::vector<std::string> > temp2;
				for(unsigned j = i+1; j < one_movie_data.size(); ++j){
					temp2 = temp;
					temp2[j]= empty;
					if(count > 2){
						std::vector<std::vector<std::string> > temp3;
						for(unsigned k = j+1; k < one_movie_data.size(); ++k){
							temp3 = temp2;
							temp3[k]= empty;
							if(count > 3){
								std::vector<std::vector<std::string> > temp4;
								for(unsigned m = k+1; m < one_movie_data.size(); ++m){
									temp4 = temp3;
									temp4[m]= empty;
									if(count > 4){
										std::vector<std::vector<std::string> > temp5;
										for(unsigned n = m+1; n < one_movie_data.size(); ++n){
											temp5 = temp4;
											temp5[n]= empty;
											if(std::find(partials.begin(), partials.end(), temp5)==partials.end()){
												partials.push_back(temp5);
											}
										}
										continue;
									}
									
									if(std::find(partials.begin(), partials.end(), temp4)==partials.end()){
										partials.push_back(temp4);
									}
									
								}
								continue;
							}
							
							if(std::find(partials.begin(), partials.end(), temp3)==partials.end()){
								partials.push_back(temp3);
							}
							
						}
						continue;
					}
					
					if(std::find(partials.begin(), partials.end(), temp2)==partials.end()){
						partials.push_back(temp2);
					}
				}
				continue;
			}
			if(std::find(partials.begin(), partials.end(), temp)==partials.end()){
				partials.push_back(temp);
			}
		}
		count++;
		
		if (count == 6){
			std::vector<std::vector<std::string> > temp6;
			temp6 = one_movie_data;
			for(unsigned i = 0; i< one_movie_data.size(); i++){
				temp6[i] = empty;
			}
			if(std::find(partials.begin(), partials.end(), temp6)==partials.end()){
				partials.push_back(temp6);
			}
			count++;
			break;
		}
	}	
}

typedef ds_hashset<std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > >, hash_string_obj> ds_hashset_type;

int main(int argc, char** argv){
	std::string str;
	int table_size = 100;
	float occupancy = 0.5;
	std::string actor_filename;
	std::string movie_filename;
	std::map <std::string, std::string> actor_data;
	std::vector<std::vector<std::vector<std::string> > > movie_data;
	ds_hashset_type hash_table(table_size);
	//read in info
	while(str != "quit"){
		std::cin >> str;
		if(str == "table_size"){
			std::cin >> table_size;
			hash_table.resize_table(table_size);
			continue;
		}
		
		if(str == "occupancy"){
			std::cin >> occupancy;
			continue;
		}
		
		if(str == "movies"){
			std::cin >> movie_filename;
			std::ifstream infile(movie_filename);
			std::string line;
			std::vector<std::vector<std::string> > temp1;
			//read in movie data from file
			int count = 0;
			int length = 0;
			while (infile >> line){
				std::vector<std::string> temp2;
				if(count < 3){
					temp2.push_back(line);
					temp1.push_back(temp2);
					count++;
					
				}
				else if(count >= 3 && count < 6){
					std::stringstream oof(line);
					oof >> length;
					for(int i = 0; i< length; i++){
						infile >> line;
						temp2.push_back(line);
					}
					temp1.push_back(temp2);
					count++;
				}
				if(count >= 6){
					movie_data.push_back(temp1);
					count = 0;
					temp1.clear();
				}
			}
			//make vector of pairs for hash table
			std::vector<std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > > > everything;
			for(unsigned i = 0; i < movie_data.size(); i++){
				std::vector<std::vector<std::vector<std::string> > > partials;
				partial_hash(movie_data[i],partials);
				for(unsigned j = 0; j < partials.size(); j++){
					if(everything.size() == 0){
						std::vector<std::vector<std::vector<std::string> > >temp2;
						temp2.push_back(partials[0]);
						everything.push_back(std::make_pair(partials[j],temp2));
						continue;
					}
					for(unsigned k = 0; k< everything.size(); k++){
						if(everything[k].first == partials[j]){
							if(std::find(everything[k].second.begin(), everything[k].second.end(),partials[0]) == everything[k].second.end()){
								everything[k].second.push_back(partials[0]);
							}
							break;
						}
						else if(k+1 == everything.size()){
							std::vector<std::vector<std::vector<std::string> > >temp2;
							temp2.push_back(partials[0]);
							everything.push_back(std::make_pair(partials[j],temp2));
						}
					}
				}
			}
			//make hash table
			std::pair< ds_hashset_type::iterator, bool > insert_result;
			for(unsigned i = 0; i < everything.size(); i++){
				insert_result = hash_table.insert(everything[i],occupancy);
				
			}
			continue;
		}
		//reads in actors
		if(str == "actors"){
			std::cin >> actor_filename;
			std::ifstream infile(actor_filename);
			std::string line;
			std::string line2;
			
			while (infile >> line){
				line2 = line;
				infile >> line;
				actor_data[line2] = line;
			}
			continue;
		}
		//reads in the query 
		if(str == "query"){
			std::string line;
			int count = 0;
			int length = 0;
			std::vector<std::vector<std::string> > single_movie_data;
			while(count < 6){
				std::vector<std::string> temp2;
				std::cin >> line;
				if(count < 3){
					if(line == "?"){
						line = "oof";
					}
					temp2.push_back(line);
					single_movie_data.push_back(temp2);
					count++;
					
				}
				else if(count >= 3 && count < 6){
					if(line == "0"){
						line = "oof";
						count++;
						temp2.push_back(line);
						single_movie_data.push_back(temp2);
						continue;
					}
					std::stringstream oof(line);
					oof >> length;
					for(int i = 0; i< length; i++){
						std::cin >> line;
						temp2.push_back(line);
					}
					single_movie_data.push_back(temp2);
					count++;
				}
			}
			//print movies that fufill query
			std::vector<std::vector<std::vector<std::string> > > empty_holder;
			ds_hashset_type::iterator p = hash_table.find(std::make_pair(single_movie_data,empty_holder));
			if(p != hash_table.end()){
				hash_table.print(actor_data,p);
			}
			else{
				std::cout << "No results for query." << std::endl;
				
			}
		}	
	}	
}
