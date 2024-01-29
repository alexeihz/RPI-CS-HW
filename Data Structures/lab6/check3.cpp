#include <iostream>
#include <list>
#include <vector>
#include <cassert>

void update(std::list<std::string>& data, std::vector<std::string> add, std::vector<std::string> remove){
	std::list<std::string>::iterator i;
	for(unsigned int j=0; j<add.size(); j++){
		for( i=data.begin(); i!=data.end(); i++){
			if((*i)==add[j]){
				break;
			}
			data.insert(i,add[j]);
		}
	}
	
	std::list<std::string>::iterator k;
	for(unsigned int j=0; j<remove.size(); j++){
		for( k=data.begin(); k!=data.end(); k++){
			//std::cout << *k << std::endl;
			//std::cout << remove[j] << std::endl;
			if((*k).find(remove[j])!= std::string::npos){
				std::cout << remove[j] << std::endl;
				k = data.erase(k);
				
			}
		}
	}
}

void print(const std::string &label, const std::list<std::string> &data) {
  std::cout << label;
  for (std::list<std::string>::const_iterator itr = data.begin();
       itr != data.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl;
}


int main() {


  // Examples demonstrating STL string find:
  // catfish contains the substring fish
  assert (std::string("catfish").find(std::string("fish")) != std::string::npos);
  // fish contains the substring fish
  assert (std::string("fish").find(std::string("fish")) != std::string::npos);
  // fish does not contain the substring catfish
  assert (std::string("fish").find(std::string("catfish")) == std::string::npos);


  // A simple example:
  std::list<std::string> data;
  data.push_back("antelope");
  data.push_back("catfish");
  data.push_back("giraffe");
  data.push_back("jellyfish");
  data.push_back("llama");
  data.push_back("whale_shark");
  data.push_back("zebra");

  std::vector<std::string> add;
  add.push_back("tiger");
  add.push_back("llama");
  add.push_back("elephant");
  
  std::vector<std::string> remove;
  remove.push_back("fish");
  remove.push_back("bear");
  remove.push_back("whale");
  
  print ("before:",data);
  update(data,add,remove);
  print ("after: ",data);
  
  // at the end, data should contain: antelope elephant giraffe llama tiger zebra
  assert (data.size() == 6);

}
