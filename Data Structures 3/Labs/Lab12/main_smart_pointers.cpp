#include <iostream>
#include <cassert>
#include <string>
#include <set>

// simple homemade smart pointers
#include "ds_smart_pointers.h"


// ====================================================
// BALLOON: a toy class with dynamically allocated memory
// ====================================================

#define MAX_NUM_ROPES 10

class Balloon {
public:
  // CONSTRUCTOR & DESTRUCTOR
  Balloon(const std::string& name_) : name(name_) {
    std::cout << "Balloon constructor " << name << std::endl;
    num_ropes = 0;
    ropes = new Balloon*[MAX_NUM_ROPES];
	ropes2 = new dsSharedPtr<Balloon>[MAX_NUM_ROPES];
  }
  ~Balloon() {
    std::cout << "Balloon destructor " << name << std::endl;
    // don't try to destroy attached balloons, just delete array
    delete [] ropes;
	delete [] ropes2;
  }

  // ACCESSORS
  const std::string& getName() const { return name; }
  int numRopes() const { return num_ropes; }
  const Balloon* getRope(int i) const { return ropes[i]; }

  // print the balloons we are attached to
  void print() { 
    std::cout << "Balloon " << name << " is connected to: ";
    for (int i = 0; i < num_ropes; i++) {
      std::cout << ropes[i]->name << " ";
    }
    if (num_ropes == 0) std::cout << "nothing";
    std::cout << std::endl;
  }
  
  void print2() { 
    std::cout << "Balloon " << name << " is connected to: ";
    for (int i = 0; i < num_ropes; i++) {
      std::cout << ropes2[i]->name << " ";
    }
    if (num_ropes == 0) std::cout << "nothing";
    std::cout << std::endl;
  }
  
  // add a rope connecting this balloon to another
  void addRope(Balloon* b) { 
    assert (num_ropes < MAX_NUM_ROPES);
    ropes[num_ropes] = b;
    num_ropes++;
  }
  
  void addRope(dsSharedPtr<Balloon>& b) { 
    assert (num_ropes < MAX_NUM_ROPES);
    ropes2[num_ropes] = b;
    num_ropes++;
  }
  
  // detach a rope connecting this balloon to another
  void removeRope(Balloon* b) { 
    for (int i = 0; i < MAX_NUM_ROPES; i++) {
      if (ropes[i] == b) { ropes[i] = ropes[num_ropes-1]; num_ropes--; break; }
    }
  }

private:
  std::string name;
  int num_ropes;
  // a dynamically allocated C-style array of ropes connecting to other Balloons
  Balloon** ropes; 
  dsSharedPtr<Balloon>* ropes2; 
};



void deleteAll(const Balloon* b, std::set<const Balloon*>& s){	
	if(s.find(b) == s.end()){
		s.insert(b);
		int i = 0;
		while(i < b -> numRopes()){
			deleteAll(b->getRope(i),s);
			++i;			
		}
	}
	else{
		return;		
	}	
}

void deleteAll(Balloon *b){
	std::set<const Balloon*> s;
	deleteAll(b,s);
	std::set<const Balloon*>::iterator it = s.begin();
	while(it != s.end()){
		delete *it;
		++it;		
	}
}

// ====================================================
// ====================================================

int main() {

  std::cout << "start of main" << std::endl;
  
  // ====================================================
  // SINGLE OWNER SMART POINTERS
  // ====================================================

  // first, without smart pointers!
  Balloon* alice(new Balloon("Hello Kitty"));
  
  // now, with our homemade single owner smart pointer
  dsAutoPtr<Balloon> bob(new Balloon("Spiderman"));

  // both alice & bob work like regular pointers...
  alice->print();
  bob->print();



  //
  // CHECKPOINT 2A: INSERT NECESSARY EXPLICIT DEALLOCATION
  //
  
  
	delete alice;
	alice = NULL;

  
  // ====================================================
  // SIMPLE SHARED POINTERS
  // ====================================================

  // first, without smart pointers
  Balloon* cathy(new Balloon("Buzz Lightyear"));  
  Balloon* daniel(cathy);
  Balloon* elaine(new Balloon("Pokemon"));
  Balloon* fred(elaine);
  daniel = fred;
  fred = NULL;
  elaine = cathy;
  cathy = NULL;
  


  //
  // CHECKPOINT 2B: INSERT NECESSARY EXPLICIT DEALLOCATION
  //
  delete daniel;
  delete elaine;


  daniel = NULL;
  elaine = NULL;
  

  // now, with our homemade shared pointer
  dsSharedPtr<Balloon> cathy2(new Balloon("Buzz Lightyear2"));
  dsSharedPtr<Balloon> daniel2(cathy2);
  dsSharedPtr<Balloon> elaine2(new Balloon("Pokemon2"));
  dsSharedPtr<Balloon> fred2(elaine2);
  daniel2 = fred2;
  fred2 = NULL;
  elaine2 = cathy2;
  cathy2 = NULL;
   // NOTE:  no explicit destruction required!
  daniel2 = NULL;
  elaine2 = NULL;


  // ====================================================
  // SHARED POINTERS WITH INTERCONNECTED STRUCTURES
  // ====================================================

  Balloon* georgette(new Balloon("Mr Potato Head"));
  Balloon* henry(new Balloon("Snoopy"));

  georgette->addRope(henry);
  henry = new Balloon("Tigger");
  georgette->addRope(henry);
  georgette->print();
  henry->print();
  
  Balloon* isabelle(new Balloon("Shrek"));
  henry->addRope(isabelle);
  isabelle = new Balloon("Barney the Purple Dinosaur");
  georgette->addRope(isabelle);

  henry->print();
  georgette->print();
  isabelle->print();
  
  
  delete henry->getRope(0);
  delete henry;
  delete georgette->getRope(0);
  delete georgette;
  delete isabelle;
  henry = NULL;
  isabelle = NULL;
  georgette = NULL;


  //
  // CHECKPOINT 2C: REWRITE THE ABOVE EXAMPLE TO USE SHARED POINTERS
  //


  dsSharedPtr<Balloon> georgette2(new Balloon("Mr Potato Head"));
  dsSharedPtr<Balloon> henry2(new Balloon("Snoopy"));
  
  georgette2->addRope(henry2);
  henry2 = new Balloon("Tigger");
  georgette2->addRope(henry2);
  georgette2->print2();
  henry2->print2();
  
  dsSharedPtr<Balloon> isabelle2(new Balloon("Shrek"));
  henry2->addRope(isabelle2);
  isabelle2 = new Balloon("Barney the Purple Dinosaur");
  georgette2->addRope(isabelle2);

  henry2->print2();
  georgette2->print2();
  isabelle2->print2();
  
  
  

  // ====================================================
  // CYCLIC STRUCTURES
  // ====================================================


  // FOR CHECKPOINT 3


  
  Balloon* jacob(new Balloon("Dora the Explorer"));
  Balloon* katherine(new Balloon("Kung Fu Panda"));
  Balloon* larry(new Balloon("Scooby Doo"));
  Balloon* miranda(new Balloon("SpongeBob SquarePants"));
  Balloon* nicole(new Balloon("Papa Smurf"));

  jacob->addRope(katherine);
  katherine->addRope(larry);
  larry->addRope(jacob);
  miranda->addRope(jacob);
  nicole->addRope(miranda);
  larry->addRope(nicole);

  katherine = NULL;
  larry = NULL;
  miranda = NULL;
  nicole = NULL;

  // jacob points to a cyclic structure!

  // to cleanup this structure:
  deleteAll(jacob);
  
  jacob = NULL;
  



  std::cout << "end of main" << std::endl;
  return 0;

  //
  // NOTE: when smart pointers go out of scope, the destructors for
  //       those objects will be called automatically
  //
}

// ====================================================