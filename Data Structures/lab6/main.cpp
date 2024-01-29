#include <iostream>
#include <vector>
#include <list>

void reverse_vector(std::vector<int>& vec){
	int count = vec.size() -1;
	int temp = 0;
	for(int i=0; i<vec.size()/2; i++){
		temp = vec[i];
		//std::cout << vec[i];
		vec[i] = vec[count];
		//std::cout << vec[i];
		vec[count] = temp;
		
		count--;
	}
}

void print(std::vector<int>& vec){
	for(int i =0; i<vec.size(); i++){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void reverse_list(std::list<int>& listy){
	int count = listy.size()/2;
	int temp = 0;
	std::list<int>::iterator i;
	std::list<int>::reverse_iterator ri;
	for( i=listy.begin(), ri = listy.rbegin(); ri!=listy.rend(); i++, ++ri){
		temp = *i;
		//std::cout << vec[i];
		*i = *ri;
		//std::cout << vec[i];
		*ri = temp;
		
		count--;
		if (count==0){
			break;
		}
	}
}

void print(std::list<int>& listy){
	std::list<int>::iterator itr;
	for(itr = listy.begin(); itr != listy.end(); ++itr){
		std::cout << *itr << " ";
	}
	std::cout<<std::endl;
}

int main(){
	std::vector<int> vec;
	
	for(int i =0; i<0; i++){
		vec.push_back(i);
	}
	print(vec);
	reverse_vector(vec);
	print(vec);
	
	std::cout << std::endl;
	
	std::list<int> listy;
	for(int i = 0; i<0; i++){
		listy.push_back(i);
	}
	print(listy);
	reverse_list(listy);
	print(listy);
	
	return 0;
}