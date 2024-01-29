#ifndef unrolled_h_
#define unrolled_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include <iostream>
const int NUM_ELEMENTS_PER_NODE = 6;
// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : next_(NULL), prev_(NULL), num_elements(0) {}
  Node(const T& v) : next_(NULL), prev_(NULL){
	elements[0] = v;
	num_elements = 1;
  }

  // REPRESENTATION
  T elements[NUM_ELEMENTS_PER_NODE];
  Node<T>* next_;
  Node<T>* prev_;
  int num_elements;
  
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p = NULL) : ptr_(p), offset(0) {}
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->elements[offset];  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
	if(offset == ptr_->num_elements-1){
		ptr_ = ptr_->next_;
		offset = 0;
		return *this;
	}
	else{
		offset++;
		return *this;
	}
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
	if(offset == ptr_->num_elements-1){
		list_iterator<T> temp(*this);
		ptr_ = ptr_->next_;
		offset = 0;
		return temp;
	}
	else{
		offset++;
		return *this;
	}
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
	if(offset == 0){
		ptr_ = ptr_->prev_;
		offset = ptr_->num_elements-1;
		return *this;
	}
	else{
		offset--;
		return *this;
	}
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
	if(offset == 0){
		list_iterator<T> temp(*this);
		ptr_ = ptr_->prev_;
		offset == ptr_->num_elements-1;
		return temp;
	}
	else{
		offset--;
		return *this;
	}
  }
  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_ && offset == r.offset; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_ || offset != r.offset; }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  int offset;
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL{
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->elements[0];  }
  T& front() { return head_->elements[0]; }
  const T& back() const { return tail_->elements[tail_->num_elements-1]; }
  T& back() { return tail_->elements[tail_->num_elements-1]; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { 	return iterator(NULL);}
  iterator tail_itr(){ return iterator(tail_);}
  
  void print(std::ostream& outfile);

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {
	// special case: initially empty list
	if (!tail_) {
		Node<T>* newp = new Node<T>(v);
		head_ = tail_ = newp;
	}
	else{
		//if the number of elements equals the max number of elements the node can hold
		if(head_ -> num_elements == NUM_ELEMENTS_PER_NODE){	
			Node<T>* newp = new Node<T>(v);
			Node<T>* tmp = head_;
			head_ = newp;
			head_ -> next_ = tmp;
			tmp -> prev_ = head_;
		}
		else{
			//normal push_front
			int size = head_ -> num_elements+1;
			T temp[size];
			temp[0] = head_ -> elements[0];
			head_ -> elements[0] = v;
			for(int i = 1; i<size; i++){
				temp[i] = head_->elements[i];
			}
			for(int i = 0; i< size; i++){
				head_ -> elements[i+1] = temp[i];
			}
			head_ -> num_elements++;
		}
	}
	++size_;
}

template <class T>
void UnrolledLL<T>::pop_front() {
	//list is initially empty
	if (head_ == NULL) {
		return;
	}
	//list only has one Node in it and that Node has only one element in it
	else if (head_->next_ == NULL && head_->num_elements == 1) {
		this -> begin() = erase(this -> begin());
	}
	//list has at least 2 Nodes in it and the head_ Node has only 1 element in it
	else if(head_->num_elements == 1){
		this -> begin() = erase(this -> begin());
	}
	//normal pop_front
	else {		
		int size = head_ -> num_elements-1;
		T temp[NUM_ELEMENTS_PER_NODE];
		for(int i =0; i < size; i++){
			temp[i] = head_->elements[i+1];
		}
		for(int i = 0; i< size; i++){
			head_ -> elements[i] = temp[i];			
		}
		head_ -> num_elements--;
		--size_;
	}
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
	// special case: initially empty list
	if (tail_ == NULL) {
		Node<T>* newp = new Node<T>(v);
		head_ = tail_ = newp;
	}
	else{
		//if the number of elements equals the max number of elements the node can hold
		if(tail_ -> num_elements == NUM_ELEMENTS_PER_NODE){
			Node<T>* newp = new Node<T>(v);
			Node<T>* tmp = tail_;
			tail_ = newp;
			tmp -> next_ = tail_;
			tail_ -> prev_ = tmp;
			
		}
		else{
			//normal push_back
		  int size = tail_ -> num_elements+1;
		  tail_ -> elements[size-1] = v;
		  tail_ -> num_elements++;
		}
	}
	++size_;
}

template <class T>
void UnrolledLL<T>::pop_back() {
	//list is initially empty
	if (head_ == NULL) {
		return;
	}
	//list only has one Node in it and that Node has only one element in it
	else if (head_->next_ == NULL && head_->num_elements == 1) {
		this -> tail_itr() = erase(this -> tail_itr());
	}
	//list has at least 2 Nodes in it and the tail_ Node has only 1 element in it
	else if(tail_->num_elements == 1){
		this -> tail_itr() = erase(this -> tail_itr());
	}
	//normal pop_back
	else {
		int size = head_ -> num_elements-1;
		T temp[NUM_ELEMENTS_PER_NODE];
		for(int i =0; i < size; i++){
			temp[i] = tail_->elements[i];
		}
		for(int i = 0; i< size; i++){
			tail_ -> elements[i] = temp[i];
		}
		tail_ -> num_elements--;
		--size_;
	}
}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  iterator result(itr.ptr_->next_);
  // One element left in the list.
  if (itr.ptr_ == head_ && head_ == tail_ && head_ -> num_elements == 1) {
    head_ = tail_ = NULL;
  }
  // Removing the head in a list with at least two nodes
  else if (itr.ptr_ == head_ && head_ -> num_elements == 1) {
    head_ = head_->next_;
    head_->prev_ = NULL;
  }
  // Removing the tail in a list with at least two nodes
  else if (itr.ptr_ == tail_ && tail_ -> num_elements == 1) {
    tail_ = tail_->prev_;
    tail_->next_ = NULL;
  }
  //removing a node with only 1 element left in it
  else if(itr.ptr_ -> num_elements == 1){
	itr.ptr_->prev_->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = itr.ptr_->prev_;
  }
  // Normal remove
  else {
	int size = itr.ptr_ -> num_elements-1;
	T temp[NUM_ELEMENTS_PER_NODE];
	int j =0;
	for(int i =0; i < size+1; i++){
		if(i != itr.offset){
			temp[j] = itr.ptr_->elements[i];
			j++;
		}
	}
	for(int i = 0; i< size; i++){
		itr.ptr_ -> elements[i] = temp[i];
	}
	itr.ptr_ -> num_elements--;
	itr.ptr_ -> elements[itr.ptr_->num_elements] = 0; 
	return itr.ptr_;
  }
  delete itr.ptr_;
  return result;
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  ++size_ ;
  //if the number of elements equals the max number of elements the node can hold
  if(itr.ptr_ -> num_elements == NUM_ELEMENTS_PER_NODE){
	int size1 = itr.offset +1;
	int size2 = itr.ptr_ -> num_elements - itr.offset;
	Node<T>* tmp = itr.ptr_ -> next_;
	
	T temp2[NUM_ELEMENTS_PER_NODE];
	Node<T>* newp = new Node<T>(0);
	int j = 0;
	for(int i = itr.offset; i < size2 + itr.offset; i++){
		temp2[j] = itr.ptr_->elements[i];
		j++;
		
	}
	for(int i = 0; i< size2; i++){
		newp -> elements[i] = temp2[i];
	}
	newp -> num_elements = size2;

	T temp[NUM_ELEMENTS_PER_NODE];
	j = 0;
	for(int i =0; i < size1; i++){
		if(i != itr.offset){
			temp[i] = itr.ptr_->elements[j];
			j++;
		}
		else{
			temp[i] = v;
		}
	}	
	for(int i = 0; i< size1; i++){
		itr.ptr_ -> elements[i] = temp[i];
	}
	itr.ptr_ -> num_elements = size1;
	
	itr.ptr_ -> next_ = newp;
	newp -> prev_ = itr.ptr_;
	newp -> next_ = tmp;
	
	return itr;
  }
  
  else{
	//normal insert
	int size = itr.ptr_ -> num_elements+1;
	T temp[NUM_ELEMENTS_PER_NODE];
	int j = 0;
	for(int i =0; i < size; i++){
		if(i != itr.offset){
			temp[i] = itr.ptr_->elements[j];
			j++;
		}
		else{
			temp[i] = v;
		}
	}
	for(int i = 0; i< size; i++){
		itr.ptr_ -> elements[i] = temp[i];
	}
	itr.ptr_ -> num_elements++;
	return itr;
  }
}


template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = NULL;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>(old.head_->elements[0]);
  for(int i = 0; i< old.head_->num_elements; i++){
	head_ -> elements[i] = old.head_->elements[i]; 
  }
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_->next_ = new Node<T>(old_p->elements[0]);
	for(int i = 0; i< old_p->num_elements; i++){
		tail_->next_ -> elements[i] = old_p->elements[i]; 
	}
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}


template <class T>
void UnrolledLL<T>::destroy_list() {
	Node<T> * vari = head_;
	while(head_ != NULL){
		vari = vari -> next_;
		delete head_;
		head_=vari;
		size_--;
	}
	head_ = NULL;
	tail_ = NULL;
}

template <class T>
void UnrolledLL<T>::print(std::ostream& outfile){
	outfile << "UnrolledLL, size: "<< size_ << std::endl;
	typename UnrolledLL<T>::iterator itr = this -> begin();
	while (itr != this -> end()){
		outfile << " node:[" << itr.ptr_ -> num_elements << "]";
		for(int i = 0; i < itr.ptr_ -> num_elements; i++){
			if(itr.ptr_->elements[i] != 0){
				outfile << " " << itr.ptr_ -> elements[i];
			}
		}
		outfile << std::endl;
		int size = itr.ptr_ -> num_elements;
		for(int i = 0; i< size; i++){
			itr++;
		}
	}
}
#endif