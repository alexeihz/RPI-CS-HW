#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ostream>



std::vector<std::string> dilation(std::vector<std::string> spaces,char* argv4){
	
	//create and fill another vector of strings
	std::vector<std::string> spaces2;
	for(int i = 0; i<spaces.size(); i++){
		spaces2.push_back(spaces[i]);		
	}
	
	//checks each point in image
	for(int i = 0; i<spaces.size(); i++){
		for(int j = 0; j<spaces[i].size(); j++){
			//if the pixel is not the foreground character
			if(spaces[i][j] != *argv4){
				//checks pixels up, down, left, and right of the current pixel and if any one of those pixels have the foreground character, add the foreground character on to the current pixel
				bool add = false;
				if(i-1 >= 0 && add == false){		
					if(spaces[i-1][j]==*argv4){
						add = true;
					}				
				}
				if(i+1 < spaces.size() && add == false){		
					if(spaces[i+1][j]==*argv4){
						add = true;
					}	
				}
				if(j-1 >= 0 && add == false){		
					if(spaces[i][j-1]==*argv4){
						add = true;
					}
				}
				if(j+1 < spaces[i].size() && add == false){		
					if(spaces[i][j+1]==*argv4){
						add = true;
					}
				}
				
				if(add == true){
					spaces2[i][j] = *argv4;
				}
			}
		}		
	}
	return spaces2;
}

std::vector<std::string> erosion(std::vector<std::string> spaces,char* argv4, char* argv5){
	
	std::vector<std::string> spaces2;
	
	for(int i = 0; i<spaces.size(); i++){
		spaces2.push_back(spaces[i]);		
	}
	
	for(int i = 0; i<spaces.size(); i++){
		for(int j = 0; j<spaces[i].size(); j++){
			//if the pixel is the foreground character
			if(spaces[i][j] == *argv4){
				//checks pixels up, down, left, and right of the current pixel and if any one of those pixels have the background character, removes the foreground character from the current pixel
				bool subtract = false;
				if(i-1 >= 0 && subtract == false){		
					if(spaces[i-1][j]== *argv5){
						subtract = true;
					}				
				}
				if(i+1 < spaces.size() && subtract == false){		
					if(spaces[i+1][j]== *argv5){
						subtract = true;
					}	
				}
				if(j-1 >= 0 && subtract == false){		
					if(spaces[i][j-1]== *argv5){
						subtract = true;
					}
				}
				if(j+1 < spaces[i].size() && subtract == false){		
					if(spaces[i][j+1]== *argv5){
						subtract = true;
					}
				}
				
				if(subtract == true){
					spaces2[i][j] = *argv5;
				}
			}
		}		
	}

	return spaces2;
}


void replace(std::vector<std::string>& spaces,char* argv4, char* argv5){
	for(int i = 0; i<spaces.size(); i++){
		for(int j = 0; j<spaces[i].size(); j++){
			//if pixel has the foreground character, change it to the different foreground character
			if(spaces[i][j] == *argv4){
				spaces[i][j] = *argv5;			
			}
		}		
	}
}

void print(std::vector<std::string>& spaces, std::ofstream& outfile){
	for(int i = 0; i<spaces.size(); i++){
		outfile << spaces[i] << std::endl;
	}
}

int main(int argc, char* argv[]){
	//checks to make sure infile exists
	std::ifstream infile(argv[1]);
	if (!infile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	
	//creates outfile to write to or writes over previously existing outfile
	std::ofstream outfile(argv[2]);
	if (!outfile.good()) {
		std::cerr << "Can't open " << argv[2] << " to write.\n";
		exit(1);
	}
	
	//parse file
	std::vector<std::string> spaces;
	std::string space;
	while (infile >> space){
		spaces.push_back(space);
	}
	
	std::string argStr = argv[3];
	if(argStr == "replace"){
		replace(spaces,argv[4],argv[5]);
		print(spaces, outfile);
	}
	
	else if(argStr == "dilation"){
		std::vector<std::string> spaces2 = dilation(spaces,argv[4]);
		
		print(spaces2, outfile);
	}
	
	else if(argStr == "erosion"){
		std::vector<std::string> spaces2 = erosion(spaces,argv[4],argv[5]);
		print(spaces2, outfile);
	}
	
	
}	
	
	
	
	