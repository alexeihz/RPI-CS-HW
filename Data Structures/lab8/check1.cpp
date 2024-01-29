#include <cstdlib>
#include <iostream>

int paths(int x, int y){
	
  if(x == 0 || y == 0){
    return 1;
  }
  return paths(x-1, y) + paths(x, y-1);
}

int main(){
  std::cout << paths(0, 0) << std::endl;
  std::cout << paths(2, 1) << std::endl;
  std::cout << paths(2, 2) << std::endl;
}