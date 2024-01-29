#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <utility>
#include <map>

typedef std::vector<std::vector<std::pair<char,std::pair<bool,bool> > > > grid_type;
typedef std::vector<grid_type> multi_grid_type;



void down(int x, int y, std::string word, bool start_direction, grid_type grid, std::vector<std::string>& dict, std::map<int,int>& across_map, std::map<int,int>& down_map,multi_grid_type& multiple_grids);

void across(int x, int y, std::string word, bool start_direction, grid_type grid, std::vector<std::string>& dict, std::map<int,int>& across_map, std::map<int,int>& down_map,multi_grid_type& multiple_grids){
	word = word + grid[x][y].first;
	int j = y;
	for(int i = 0; i < dict.size(); i++){
		if(word == dict[i].substr(0,word.length())){
			if(std::find(dict.begin(), dict.end(),word) != dict.end()){
				if(across_map.find(word.length()) != across_map.end()){
					if(j+word.length() >= grid[i].size() && x+1<grid.size()){
						across(x+1,0,"",false,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+word.length() >= grid[x].size() && x+1>=grid.size() && start_direction == false){
						down(0,0,"",false,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+word.length() >= grid[x].size() && x+1>=grid.size() && start_direction == true){
						across_map[word.length()]--;
						if(across_map[word.length()] == 0){
							across_map.erase(word.length());
						}
						for(int k = y; k < j; k++){
							grid[x][k].second.first = true;
						}
						
						if(across_map.empty() && down_map.empty()){
							multiple_grids.push_back(grid);
						}
					}
					else if(j+word.length() < grid[x].size()){
						across(x,j+word.length(),"",false,grid,dict,across_map,down_map, multiple_grids);
					}
					
					across_map[word.length()]--;
					if(across_map[word.length()] == 0){
						across_map.erase(word.length());
					}
					for(int k = y; k < j; k++){
						grid[x][k].second.first = true;
					}
					if(j+1 < grid[x].size()){
						grid[x][j+1].first = '#';
					}
					if(j+2 < grid[x].size()){
						across(x,j+2,"",false,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+2 >= grid[x].size() && x+1 >= grid.size() && start_direction == false){
						down(0,0,"",false,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+2 >= grid[x].size() && x+1 >= grid.size() && start_direction == true){
						if(across_map.empty() && down_map.empty()){
							multiple_grids.push_back(grid);
						}
					}
				}
				if(j+1 < grid[x].size()){
					j++;
					word = word + grid[x][j].first;
					i = 0;
				}
				else if(j+1 >= grid[x].size() && x+1 < grid.size()){
					across(x+1,0,"",false,grid,dict, across_map,down_map, multiple_grids);
					
				}
				else if(j+1 >= grid[x].size() && x+1 >= grid.size() && start_direction == false){
					down(0,0,"",false,grid,dict,across_map,down_map, multiple_grids);
				}
				else if(j+1 >= grid[x].size() && x+1 >= grid.size() && start_direction == true){
					if(across_map.empty() && down_map.empty()){
						multiple_grids.push_back(grid);
					}
				}
			}
			else if(j+1 < grid[x].size()){
				j++;
				word = word + grid[x][j].first;
				i = 0;
			}
			else if(j+1 >= grid[x].size() && x+1 < grid.size()){
				across(x+1,0,"",false,grid,dict, across_map,down_map, multiple_grids);
			}
			else if(j+1 >= grid[x].size() && x+1 >= grid.size() && start_direction == false){
				down(0,0,"",false,grid,dict,across_map,down_map, multiple_grids);
			}
			else if(j+1 >= grid[x].size() && x+1 >= grid.size() && start_direction == true){
				if(across_map.empty() && down_map.empty()){
					multiple_grids.push_back(grid);
				}
			}
		}
		else if(j+1 < grid[x].size()){
			j++;
			word = word + grid[x][j].first;
			i = 0;
		}
		else if(j+1 >= grid[x].size() && x+1 < grid.size()){
			across(x+1,0,"",false,grid,dict, across_map,down_map, multiple_grids);
		}
		else if(j+1 >= grid[x].size() && x+1 >= grid.size() && start_direction == false){
			down(0,0,"",false,grid,dict,across_map,down_map, multiple_grids);
		}
		else if(j+1 >= grid[x].size() && x+1 >= grid.size() && start_direction == true){
			if(across_map.empty() && down_map.empty()){
				multiple_grids.push_back(grid);
			}
		}
	}
}

void down(int x, int y, std::string word, bool start_direction, grid_type grid, std::vector<std::string>& dict, std::map<int,int>& across_map, std::map<int,int>& down_map, multi_grid_type& multiple_grids){
	int j = x;
	for(int i = 0; i < dict.size(); i++){
		if(word == dict[i].substr(0,word.length())){
			if(std::find(dict.begin(), dict.end(),word) != dict.end()){
				if(down_map.find(word.length()) != down_map.end()){
					if(j+word.length() >= grid.size() && y+1<grid[x].size()){
						down(0,y+1,"",true,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+word.length() >= grid.size() && y+1>=grid[x].size() && start_direction == true){
						across(0,0,"",true,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+word.length() >= grid.size() && y+1>=grid[x].size() && start_direction == false){
						down_map[word.length()]--;
						if(down_map[word.length()] == 0){
							down_map.erase(word.length());
						}
						for(int k = x; k < j; k++){
							grid[k][y].second.second = true;
						}
						
						if(across_map.empty() && down_map.empty()){
							multiple_grids.push_back(grid);
						}
					}
					else if(j+word.length() < grid.size()){
						across(j+word.length(),y,"",true,grid,dict,across_map,down_map, multiple_grids);
					}
					
					down_map[word.length()]--;
					if(down_map[word.length()] == 0){
						down_map.erase(word.length());
					}
					for(int k = x; k < j; k++){
						grid[k][y].second.second = true;
					}
					if(j+1 < grid.size()){
						grid[j+1][y].first = '#';
					}
					if(j+2 < grid.size()){
						down(x,y+1,"",true,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+2 >= grid.size() && y+1 >= grid[x].size() && start_direction == true){
						across(0,0,"",true,grid,dict,across_map,down_map, multiple_grids);
					}
					else if(j+2 >= grid.size() && y+1 >= grid[x].size() && start_direction == false){
						if(across_map.empty() && down_map.empty()){
							multiple_grids.push_back(grid);
						}
					}
				}
				if(j+1 < grid.size()){
					j++;
					word = word + grid[j][y].first;
					i = 0;
				}
				else if(j+1 >= grid.size() && y+1 < grid[x].size()){
					down(0,y+1,"",true,grid,dict, across_map,down_map, multiple_grids);
					
				}
				else if(j+1 >= grid.size() && y+1 >= grid[x].size() && start_direction == true){
					across(0,0,"",true,grid,dict,across_map,down_map, multiple_grids);
				}
				else if(j+1 >= grid.size() && y+1 >= grid[x].size() && start_direction == false){
					if(across_map.empty() && down_map.empty()){
						multiple_grids.push_back(grid);
					}
				}
			}
			else if(j+1 < grid.size()){
				j++;
				word = word + grid[j][y].first;
				i = 0;
			}
			else if(j+1 >= grid.size() && y+1 < grid[x].size()){
				down(0,y+1,"",true,grid,dict, across_map,down_map, multiple_grids);
				
			}
			else if(j+1 >= grid.size() && y+1 >= grid[x].size() && start_direction == true){
				across(0,0,"",true,grid,dict,across_map,down_map, multiple_grids);
			}
			else if(j+1 >= grid.size() && y+1 >= grid[x].size() && start_direction == false){
				if(across_map.empty() && down_map.empty()){
					multiple_grids.push_back(grid);
				}
			}
		}
		else if(j+1 < grid.size()){
			j++;
			word = word + grid[j][y].first;
			i = 0;
		}
		else if(j+1 >= grid.size() && y+1 < grid[x].size()){
			down(0,y+1,"",true,grid,dict, across_map,down_map, multiple_grids);
			
		}
		else if(j+1 >= grid.size() && y+1 >= grid[x].size() && start_direction == true){
			across(0,0,"",true,grid,dict,across_map,down_map, multiple_grids);
		}
		else if(j+1 >= grid.size() && y+1 >= grid[x].size() && start_direction == false){
			if(across_map.empty() && down_map.empty()){
				multiple_grids.push_back(grid);
			}
		}
	}
}

void check(multi_grid_type& multiple_grids){
	for(int i = 0; i< multiple_grids.size(); ++i){
		for(int j = 0; j< multiple_grids[i].size(); ++j){
			for(int k = 0; k<multiple_grids[i][j].size(); ++k){
				if(multiple_grids[i][j][k].second.first == false && multiple_grids[i][j][k].second.second == false){
					multiple_grids[i][j][k].first = '#';
				}
			}
		}
	}
}

void print(multi_grid_type& multiple_grids, int num){
	for(int i = 0; i< num; ++i){
		for(int j = 0; j< multiple_grids[i].size(); ++j){
			for(int k = 0; k<multiple_grids[i][j].size(); ++k){
				std::cout << multiple_grids[i][j][k].first;
			}
			std::cout << std::endl;
		}
	}
}


//direction: down = true, across = false
void solutions(grid_type grid, std::vector<std::string>& dict, std::map<int,int>& across_map, std::map<int,int>& down_map, multi_grid_type& multiple_grids){
	across(0,0,"",false,grid,dict,across_map,down_map, multiple_grids);
	down(0,0,"",true,grid,dict,across_map,down_map, multiple_grids);
}	
	

int main(int argc, char* argv[]){
	std::ifstream dict_file(argv[1]);
	if (!dict_file.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	
	std::ifstream grid_file(argv[2]);
	if (!grid_file.good()) {
		std::cerr << "Can't open " << argv[2] << " to read.\n";
		exit(1);
	}
	
	std::vector<std::string> dict;
	std::vector<std::pair<char,std::pair<bool,bool> > >row;
	grid_type grid;
	std::string line;
	
	while (dict_file >> line){
		dict.push_back(line);
	}
	
	bool direction = false;
	std::map<int,int> across_map;
	std::map<int,int> down_map;
	while (grid_file >> line){
		if(line[0] == '!'){
			if(line.substr(1,line.length()-1)=="Across"){
				direction = true;
			}
			if(line.substr(1,line.length()-1)=="Down"){
				direction = false;
			}
		}
		else if(line[0] == '+'){
			std::stringstream s(line.substr(1,line.length()-1));
			int x = 0;
			s >> x;
			if(direction == true){
				across_map[x]++;
			}
			else{
				down_map[x]++;
			}
		}
		else{
			for(int i = 0; i<line.length(); i++){
				row.push_back(std::make_pair(line[i],std::make_pair(false,false)));
			}
			grid.push_back(row);
		}
	}
	
	std::string solution_mode = argv[3];
	std::string output_mode = argv[4];
	multi_grid_type multiple_grids;
	
	solutions(grid, dict, across_map, down_map, multiple_grids);
	check(multiple_grids);
	
	if(output_mode == "print_boards"){
		std::cout << "Number of solution(s): " << multiple_grids.size() << std::endl;
		if(solution_mode == "one_solution"){
			std::cout << "Board:" << std::endl;
			print(multiple_grids,1);
		}
		if(solution_mode == "all_solutions"){
			for(int i = 0; i<multiple_grids.size(); ++i){
				std::cout << "Board:" << std::endl;
				print(multiple_grids,i);
			}
		}
	}
	
	if(output_mode == "count_only"){
		std::cout << "Number of solution(s): " << multiple_grids.size() << std::endl;
	}
}