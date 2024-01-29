#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
	priority_queue() {}

	priority_queue( std::vector<T> const& values ){
		for(unsigned int j = 0; j < values.size(); j++){
			m_heap.insert(m_heap.begin(), values[j]);

			unsigned int i = 0;
			while(2 * i + 1 < m_heap.size()){
				int child;
				int child_idx;
				if(2 * i + 2 < m_heap.size() && m_heap[2 * i + 2] < m_heap[2 * i + 1]){
					child = m_heap[2 * i + 2];
					child_idx = 2 * i + 2;
				}

				else{
					child = m_heap[2 * i + 1];
					child_idx = 2 * i + 1;
				}

				if(child < m_heap[i]){
					m_heap[child_idx] = m_heap[i];
					m_heap[i] = child;
					i = child_idx;
				}

				else{
					break;
				}
			}
		}
	}

	const T& top() const {
		assert( !m_heap.empty() );
		return m_heap[0]; 
	}

	void push( const T& entry ){
		m_heap.push_back(entry);
		//std::cout << "???\n";
		int i = m_heap.size() - 1;
		while(( (i - 1) / 2) >= 0){
		  //std::cout << i << "\n";
			if(m_heap[i] < m_heap[(i - 1)/2]){
				T x = m_heap[i];
				m_heap[i] = m_heap[(i-1) / 2];
				m_heap[(i-1) / 2] = x;

				i = (i - 1) / 2;
			}

			else{
				break;
			}
		}
	}

  void pop(){
		assert( !m_heap.empty() );
		int max = 0;
		bool first = true;
		int max_idx;
		for(unsigned int i = 0; i < m_heap.size(); i++){
			if(first){
				max = m_heap[i];
				max_idx = i;
				first = false;
				continue;
			}

			if(m_heap[i] > max){
				max = m_heap[i];
				max_idx = i;
			}
		}

		m_heap[0] = max;
		m_heap.erase(m_heap.begin() + max_idx);

		unsigned int i = 0;
		while(2 * i + 1 < m_heap.size()){
			int child;
			int child_idx;
			if(2 * i + 2 < m_heap.size() && m_heap[2 * i + 2] < m_heap[2 * i + 1]){
				child = m_heap[2 * i + 2];
				child_idx = 2 * i + 2;
			}

			else{
				child = m_heap[2 * i + 1];
				child_idx = 2 * i + 1;
			}

			if(child < m_heap[i]){
				m_heap[child_idx] = m_heap[i];
				m_heap[i] = child;
				i = child_idx;
			}

			else{
				break;
			}
		}

	}

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap()
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap ){
		for(unsigned int i = 0; i < heap.size(); i++){
		  //std::cout << i << "\n";
		  //Check left child
			if(2 * i + 1 < heap.size()){
				if(heap[2 * i + 1] < heap[i])
				return false;
			}
			 //Check right child
			if(2 * i + 2 < heap.size()){
				if(heap[2 * i + 2] < heap[i]){
				  return false;
				}
			}
		}

		return true;
	}

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v ){
	for(unsigned int i = 0; i < v.size(); i++){
		std::cout << i << ": " << v[i] << "\n";
	}
	//Construct a heap
	for(unsigned int j = 0; j < v.size() / 2; j++){
		unsigned int i = 0;
		while(2 * i + 1 < v.size()){
			//std::cout << i << "\n";
			int child;
			int child_idx;
			if(2 * i + 2 < v.size() && v[2 * i + 2] < v[2 * i + 1]){
				child = v[2 * i + 2];
				child_idx = 2 * i + 2;
			}

			else{
				child = v[2 * i + 1];
				child_idx = 2 * i + 1;
			}

			if(child < v[i]){
				v[child_idx] = v[i];
				v[i] = child;
				i = child_idx;
			}

			else{
				i++;
			}
		}
	}
	std::cout << "\nheap:\n";
	for(unsigned int i = 0; i < v.size(); i++){
		std::cout << i << ": " << v[i] << "\n";
	}
	std::cout << "\n\n";

	//Perform the n necessary pop-erations
	for(unsigned int j = 1; j < v.size(); j++){

		T min = v[0];
		T last = v[v.size() - j];
		v[0] = last;
		v[v.size() - j] = min;

		unsigned int i = 0;
		std::cout << "\nBefore: " << j << "\n";
		for(unsigned int i = 0; i < v.size() - j; i++){
			std::cout << i << ": " << v[i] << "\n";
		}
		std::cout << "\n\n";

		while(2 * i + 1 < v.size() - j){
			T child;
			int child_idx;

			if(2 * i + 2 < v.size() - j && v[2 * i + 2] < v[2 * i + 1]){
				child = v[2 * i + 2];
				child_idx = 2 * i + 2;
			}

		  else{
				child = v[2 * i + 1];
				child_idx = 2 * i + 1;
			}

		  if(child < v[i]){
				v[child_idx] = v[i];
				v[i] = child;
				i = child_idx;
			}

		  else{
				break;
			}
		}
    

		std::cout << "\nAfter: \n";
		for(unsigned int i = 0; i < v.size() - j; i++){
			std::cout << i << ": " << v[i] << "\n";
		}
		std::cout << "\n\n";
	}	

	for(unsigned int i = 0; i < v.size() / 2; i++){
		int orig = v[i];
		v[i] = v[v.size() - 1 - i];
		v[v.size() - 1 - i] = orig;

	}
}

#endif