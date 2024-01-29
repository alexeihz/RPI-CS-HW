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


int fact(int n);

int nCr(int n, int r){
	return fact(n)/(fact(r) * fact(n-r));
}


int fact(int n){
	int res = 1;
	for(int i = 2; i<= n; i++){
		res = res * i;		
	}
	return res;
}

std::vector<std::vector<int> > combinations(){
	int count = 1;
	std::vector<std::vector<int> > combos;
	std::vector<int> combo;
	for(int i = 1; i<7; i++){
		combo.push_back(i);
	}
	combos.push_back(combo);
	std::vector<int> temp;
	while(combos.size() < 64){
		for(unsigned i = 0; i < 6; ++i){
			temp = combo;
			temp[i] = 0;
			if(count > 1){
				std::vector<int> temp2;
				for(unsigned j = i+1; j < 6; ++j){
					temp2 = temp;
					temp2[j]= 0;
					if(count > 2){
						std::vector<int> temp3;
						for(unsigned k = j+1; k < 6; ++k){
							temp3 = temp2;
							temp3[k]= 0;
							if(count > 3){
								std::vector<int> temp4;
								for(unsigned m = k+1; m < 6; ++m){
									temp4 = temp3;
									temp4[m]= 0;
									if(count > 4){
										std::vector<int> temp5;
										for(unsigned n = m+1; n < 6; ++n){
											temp5 = temp4;
											temp5[n]= 0;
											if(std::find(combos.begin(), combos.end(), temp5)==combos.end()){
												combos.push_back(temp5);
											}
										}
										continue;
									}
									
									if(std::find(combos.begin(), combos.end(), temp4)==combos.end()){
										combos.push_back(temp4);
									}
									
								}
								continue;
							}
							
							if(std::find(combos.begin(), combos.end(), temp3)==combos.end()){
								combos.push_back(temp3);
							}
							
						}
						continue;
					}
					
					if(std::find(combos.begin(), combos.end(), temp2)==combos.end()){
						combos.push_back(temp2);
					}
				}
				continue;
			}
			if(std::find(combos.begin(), combos.end(), temp)==combos.end()){
				combos.push_back(temp);
			}
		}
		count++;
		
		if (count == 6){
			std::vector<int> temp6;
			temp6 = combo;
			for(unsigned i = 0; i< 6; i++){
				temp6[i] = 0;
			}
			if(std::find(combos.begin(), combos.end(), temp6)==combos.end()){
				combos.push_back(temp6);
			}
			count++;
			break;
		}
	}
	return combos;
}

void partial_hash(const std::vector<std::vector<std::string> >&one_movie_data, std::set<std::vector<std::vector<std::string> > >& partials, const std::vector<std::vector<int> >& combos){
	/*
	unsigned int possible_combos = 0;
	for(unsigned i = 0; i <= one_movie_data.size(); ++i){
		//std::cout << nCr(one_movie_data.size(),i) << std::endl;
		possible_combos += nCr(one_movie_data.size(),i);
	}
	//std::cout << possible_combos << std::endl;
	//std::cout << one_movie_data.size() << std::endl;
	
	std::vector<std::vector<std::string> > one_movie;
	std::vector<std::string> temp;
	//std::cout << combos.size() << std::endl;
	partials.push_back(one_movie_data);
	for(unsigned i = 0; i<combos.size(); i++){
		for(unsigned j = 0; j < combos[i].size(); j++){
			//std::cout << combos[i][j] << std::endl;
			if(combos[i][j] == 0){
				temp.push_back("oof");
			}
			else{
				temp = one_movie_data[j];
			}
			one_movie.push_back(temp);
		}
		partials.push_back(one_movie);
	}
	*/
	
	
	
	
	int count = 1;
	std::vector<std::vector<std::string> > temp;
	std::vector<std::string> empty;
	empty.push_back("oof");
	partials.insert(one_movie_data);
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
											//if(std::find(partials.begin(), partials.end(), temp5)==partials.end()){
												partials.insert(temp5);
											//}
										}
										continue;
									}
									
									//if(std::find(partials.begin(), partials.end(), temp4)==partials.end()){
										partials.insert(temp4);
									//}
									
								}
								continue;
							}
							
							//if(std::find(partials.begin(), partials.end(), temp3)==partials.end()){
								partials.insert(temp3);
							//}
							
						}
						continue;
					}
					
					//if(std::find(partials.begin(), partials.end(), temp2)==partials.end()){
						partials.insert(temp2);
					//}
				}
				continue;
			}
			//if(std::find(partials.begin(), partials.end(), temp)==partials.end()){
				partials.insert(temp);
			//}
		}
		count++;
		
		if (count == 6){
			std::vector<std::vector<std::string> > temp6;
			temp6 = one_movie_data;
			for(unsigned i = 0; i< one_movie_data.size(); i++){
				temp6[i] = empty;
			}
			//if(std::find(partials.begin(), partials.end(), temp6)==partials.end()){
				partials.insert(temp6);
			//}
			count++;
			break;
		}
		
		/*
		if(count == 1){
			for(unsigned int i = 0; i < one_movie_data.size(); i++){
				temp = one_movie_data;
				//std::cout << temp[i][0] << std::endl;
				temp[i] = empty;
				//std::cout << temp[i][0] << std::endl;
				if(std::find(partials.begin(), partials.end(), temp)==partials.end()){
					partials.push_back(temp);
				}
			}
			count++;
			continue;
		}
		
		else if(count == 2){
			for(unsigned i = 0; i < one_movie_data.size(); ++i){
				temp = one_movie_data;
				temp[i] = empty;
				std::vector<std::vector<std::string> > temp2;
				for(unsigned j = i+1; j < one_movie_data.size(); ++j){
					temp2 = temp;
					//std::cout << temp2[j][0] << std::endl;
					temp2[j] = empty;
					//std::cout << temp2[j][0] << std::endl;
					if(std::find(partials.begin(), partials.end(), temp2)==partials.end()){
						partials.push_back(temp2);
					}
				}
			}
			count++;
			continue;
		}
		
		else if(count == 3){
			for(unsigned i = 0; i < one_movie_data.size(); ++i){
				temp = one_movie_data;
				temp[i] = empty;
				std::vector<std::vector<std::string> > temp2;
				for(unsigned j = i + 1; j < one_movie_data.size(); ++j){
					temp2 = temp;
					temp2[j] = empty;
					std::vector<std::vector<std::string> > temp3;
					for(unsigned k = j + 1; k < one_movie_data.size(); ++k){
						temp3 = temp2;
						temp3[k] = empty;
						if(std::find(partials.begin(), partials.end(), temp3)==partials.end()){
							partials.push_back(temp3);
						}
					}
				}
			}
			
			count++;
			continue;
		}
		else if(count == 4){
			for(unsigned i = 0; i < one_movie_data.size(); ++i){
				temp = one_movie_data;
				temp[i]= empty;
				std::vector<std::vector<std::string> > temp2;
				for(unsigned j = i +1; j < one_movie_data.size(); ++j){
					temp2 = temp;
					temp2[j]= empty;
					std::vector<std::vector<std::string> > temp3;
					for(unsigned k = j+1; k < one_movie_data.size(); ++k){
						temp3 = temp2;
						temp3[k] = empty;
						std::vector<std::vector<std::string> > temp4;
						for(unsigned m = k+1; m < one_movie_data.size(); ++m){
							temp4 = temp3;
							temp4[m]= empty;
							if(std::find(partials.begin(), partials.end(), temp4)==partials.end()){
								partials.push_back(temp4);
							}
						}
					}
				}
			}		
			
			count++;
			continue;
		}
		else if(count == 5){
			for(unsigned i = 0; i < one_movie_data.size(); ++i){
				temp = one_movie_data;
				temp[i] = empty;
				std::vector<std::vector<std::string> > temp2;
				for(unsigned j = i+1; j < one_movie_data.size(); ++j){
					temp2 = temp;
					temp2[j]= empty;
					std::vector<std::vector<std::string> > temp3;
					for(unsigned k = j+1; k < one_movie_data.size(); ++k){
						temp3 = temp2;
						temp3[k]= empty;
						std::vector<std::vector<std::string> > temp4;
						for(unsigned m = k+1; m < one_movie_data.size(); ++m){
							temp4 = temp3;
							temp4[m]= empty;
							std::vector<std::vector<std::string> > temp5;
							for(unsigned n = m+1; n < one_movie_data.size(); ++n){
								temp5 = temp4;
								temp5[n]= empty;
								if(std::find(partials.begin(), partials.end(), temp5)==partials.end()){
									partials.push_back(temp5);
								}
							}
							
						}
					}
				}
			}
			count++;
			continue;
		}
		else if (count == 6){
			std::vector<std::vector<std::string> > temp6;
			temp6 = one_movie_data;
			for(int i = 0; i< one_movie_data.size(); i++){
				temp6[i] = empty;
			}
			if(std::find(partials.begin(), partials.end(), temp6)==partials.end()){
				partials.push_back(temp6);
			}
			
			// for(unsigned int i = 0; i < partials.size(); i++){
				// for(unsigned int j = 0; j < partials[i].size(); j++){
					// std::cout << partials[i][j][0] << std::endl;
				// }
				// std::cout << std::endl;
			// }
			
			count++;
			continue;
		}
	*/
	}
	//return partials;
	
}





typedef ds_hashset<std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > >, hash_string_obj> ds_hashset_type;
//typedef ds_hashset<std::vector<std::vector<std::string> > , hash_string_obj> ds_hashset_type2;


int main(int argc, char** argv){
	std::string str;
	int table_size = 100;
	float occupancy = 0.5;
	std::vector<std::vector<int> > combos = combinations();
	std::string actor_filename;
	std::string movie_filename;
	std::map <std::string, std::string> actor_data;
	std::vector<std::vector<std::vector<std::string> > > movie_data;
	ds_hashset_type hash_table(table_size);
	//ds_hashset_type query_hash;
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
			
			int count = 0;
			int length = 0;
			while (infile >> line){
				std::vector<std::string> temp2;
				if(count < 3){
					//std::cout << line << std::endl;
					temp2.push_back(line);
					temp1.push_back(temp2);
					count++;
					
				}
				else if(count >= 3 && count < 6){
					std::stringstream oof(line);
					oof >> length;
					for(int i = 0; i< length; i++){
						infile >> line;
					//	std::cout << line << std::endl;
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
			
			// std::pair< ds_hashset_type::iterator, bool > insert_result;
			//std::cout << movie_data.size() << std::endl;
			//for(unsigned int i = 0; i < movie_data.size(); ++i){
				//insert_result = hash_table.insert(movie_data[i]);
				// ds_hashset_type::iterator p;
				// p = hash_table.find(movie_data[i]);
				// std::cout << *p << std::endl;
			//}
			//hash_table.print(std::cout);
			
			
			std::vector<std::vector<std::string> > temp;
			
			std::set<std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > > > everything;
			//everything = std::make_pair(temp,temp2);
			
			for(unsigned i = 0; i < movie_data.size(); i++){
				std::set<std::vector<std::vector<std::string> > > partials;
				std::set<std::vector<std::vector<std::string> > >::iterator itr;
				std::set<std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > > >::iterator itr2;
				partial_hash(movie_data[i],partials,combos);
				for(itr = partials.begin(); itr!= partials.end(); ++itr){
					
					if(everything.size() == 0){
						std::vector<std::vector<std::vector<std::string> > >temp2;
						temp2.push_back(*(partials.begin()));
						everything.insert(std::make_pair(*(itr),temp2));
						continue;
					}
					for(itr2= everything.begin(); itr2!=everything.end(); ++itr2){
						if((*itr2).first == *itr){
							//if(std::find(everything[k].second.begin(), everything[k].second.end(),*itr) == everything[k].second.end()){
								(*itr2).second.push_back(*(partials.begin()));
							//}
							break;
						}
						// else if(k+1 == everything.size()){
							// std::vector<std::vector<std::vector<std::string> > >temp2;
							// temp2.push_back(*(partials.begin()));
							// everything.push_back(std::make_pair(*itr,temp2));
						// }
					}
					if(itr2 == everything.end()){
						std::vector<std::vector<std::vector<std::string> > >temp2;
						temp2.push_back(*(partials.begin()));
						everything.insert(std::make_pair(*itr,temp2));
					}
				}
			}
			
			//std::cout << everything[63].second[1][0][0] << std::endl;
			std::pair< ds_hashset_type::iterator, bool > insert_result;
			for(unsigned i = 0; i < everything.size(); i++){
				insert_result = hash_table.insert(everything[i],occupancy);
				
			}
			
			//std::cout << partials.size() << std::endl;
			//std::pair<std::vector<std::string>,std::vector<std::vector<std::string> > > table;
			
			continue;
			
		}
		
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
						//std::cout << "dsfdsaf" << std::endl;
						line = "oof";
					}
					//std::cout << line << std::endl;
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
			
			// for(int i = 0; i< single_movie_data.size(); i++){
				// std::cout << single_movie_data[i][0] << std::endl;				
			// }
			// std::vector<std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > > > one;
			std::vector<std::vector<std::vector<std::string> > > empty_holder;
			// one.push_back(std::make_pair(single_movie_data,empty_holder));
			
			// std::pair< ds_hashset_type::iterator, bool > insert_result;
			// insert_result = query_hash.insert(one[0]);
			ds_hashset_type::iterator p = hash_table.find(std::make_pair(single_movie_data,empty_holder));
			if(p != hash_table.end()){
				hash_table.print(actor_data,std::make_pair(single_movie_data,empty_holder));
			}
			else{
				//hash_table.print(actor_data,std::make_pair(single_movie_data,empty_holder));
				std::cout << "No results for query." << std::endl;
				
			}
			
		}	
	}
	
	
	
}
