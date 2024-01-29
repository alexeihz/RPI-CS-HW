//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN 
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) { 
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end()); 
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }  

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front(); 
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));
  
  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
void MoreTests() {

  //
  //
  // ADD YOUR OWN TEST CASES HERE
  // ADD COMMENTS TO EXPLAIN THE PURPOSE OF THE TEST CASES
  // TEST CASES SHOULD FINISH AND NOT CRASH. OUTPUT IS HELPFUL AS WELL.
  //
  //
  
  //push_front on an empty list instead of push_back
  UnrolledLL<char> a;
  std::list<char> b;
  std::string str = "!ereht_olleh";
  for (int i = 0; i < 12; ++i) {
    a.push_front(str[i]);
    b.push_front(str[i]);
  }  

  // iterate through the string and print it out
  std::cout << "the string is " << std::endl;
  for (UnrolledLL<char>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 12);
  assert (a.front() == 'h');
  assert (a.back() == '!');
  a.pop_front(); 
  b.pop_front();
  assert (a.size() == 11);
  assert (a.front() == 'e');
  a.pop_back();
  b.pop_back();
  assert (a.size() == 10);
  assert (a.back() == 'e');
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // completely erases the list using pop_fronts and pop_backs
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  a.pop_back();
  a.pop_back();
  a.pop_back();
  a.pop_back();
  
  b.pop_back();
  b.pop_back();
  b.pop_back();
  b.pop_back();
  b.pop_back();
  
  a.print(std::cout);
  assert (a.size() == 0);
  
  a.push_back('r');
  a.push_back('r');
  a.push_back('r');
  a.push_back('r');
  a.push_back('r');
  a.push_back('t');
  
  a.push_front('r');
  a.push_front('r');
  a.push_front('r');
  a.push_front('r');
  a.push_front('k');
  a.push_front('s');
  
  
  b.push_back('r');
  b.push_back('r');
  b.push_back('r');
  b.push_back('r');
  b.push_back('r');
  b.push_back('t');
  
  b.push_front('r');
  b.push_front('r');
  b.push_front('r');
  b.push_front('r');
  b.push_front('k');
  b.push_front('s');
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 12);
  assert (a.front() == 's');
  assert (SAME(a,b));

  // erase the 's'
  std::cout <<"erase the 's'" << std::endl;
  UnrolledLL<char>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 's') {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<char>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 's') {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 11);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<char>::iterator itr = a.begin(); itr != a.end(); itr++) {
	  if (*itr == 'k') {
      itr = a.insert(itr,'$');
      itr++;
    } 
  }
  for (std::list<char>::iterator itr = b.begin(); itr != b.end(); itr++) {
	  if (*itr == 'k') {
      itr = b.insert(itr,'$');
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 12);
  assert (SAME(a,b));
  
  // erases everthing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    a_iter = a.erase(a_iter);
  }
  
  b_iter = b.begin();
  while (b_iter != b.end()) {
    b_iter = b.erase(b_iter);
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 0);
  assert (SAME(a,b));

  

}
