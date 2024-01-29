#include <ctime>
#include <vector>
#include "Job_extra.h"
#include "ElegantQueue.h"

ElegantQueue::ElegantQueue() {}




//loops through heap to assign correct hook values
void ElegantQueue::urgent_loop(std::vector<Job*> const& values){
	for(unsigned int i = 0; i< values.size(); i++){
		values[i] -> urgent_hook = i;
	}	
}

//adds element to the heap and percolates up
void ElegantQueue::urgent_push( Job* entry ){
	m_heap.push_back(entry);
	entry -> priority_ptr = this;

	int i = m_heap.size() - 1;
	while(( (i - 1) / 2) >= 0){
		if(m_heap[i]->priority > m_heap[(i - 1)/2]->priority){
			Job* x = m_heap[i];
			m_heap[i] = m_heap[(i-1) / 2];
			m_heap[(i-1) / 2] = x;
			i = (i - 1) / 2;
		}

		else{
			break;
		}
	}
	urgent_loop(m_heap);
}
	
//returns and removes first element in heap and percolates down	
Job* ElegantQueue::urgent_pop(){
	Job* temp = m_heap[0];
	m_heap[0] = m_heap[m_heap.size()-1];
	m_heap.erase(m_heap.begin()+(m_heap.size()-1));
	unsigned int i = 0;
	while(2 * i + 1 < m_heap.size()){
		Job* child;
		int child_idx;
		if(2 * i + 2 < m_heap.size() && m_heap[2 * i + 2]->priority > m_heap[2 * i + 1]->priority){
			child = m_heap[2 * i + 2];
			child_idx = 2 * i + 2;
		}

		else{
			child = m_heap[2 * i + 1];
			child_idx = 2 * i + 1;
		}

		if(child->priority > m_heap[i]->priority){
			m_heap[child_idx] = m_heap[i];
			m_heap[i] = child;
			i = child_idx;
			
		}

		else{
			break;
		}
	}
	urgent_loop(m_heap);
	return temp;	
}

//prints heap
void ElegantQueue::urgent_printHeap( std::ostream & ostr ){
		ostr << "UQ " << m_heap.size() << " jobs:" << std::endl;
		for ( unsigned int i=0; i<m_heap.size(); ++i ){
			ostr << "\t" << m_heap[i];
		}
	}
	
//erases correct element in the heap and percolates down
void ElegantQueue::urgent_remove_from_index(eq_hook hook){
	m_heap.erase(m_heap.begin() + hook);
	unsigned int i = 0;
	while(2 * i + 1 < m_heap.size()){
		Job* child;
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
	urgent_loop(m_heap);
}
	





//loops through heap to assign correct hook values
void ElegantQueue::time_loop(std::vector<Job*> const& values){
	for(unsigned int i = 0; i< values.size(); i++){
		values[i] -> time_hook = i;
	}
}
	
//adds element to the heap and percolates up
void ElegantQueue::time_push( Job* entry ){
	m_heap.push_back(entry);
	entry -> time_ptr = this;
	
	int i = m_heap.size() - 1;
	while(( (i - 1) / 2) >= 0){
		if(m_heap[i]->timestamp < m_heap[(i - 1)/2]->timestamp){
			Job* x = m_heap[i];
			m_heap[i] = m_heap[(i-1) / 2];
			m_heap[(i-1) / 2] = x;
			i = (i - 1) / 2;			
		}

		else{
			break;
		}
	}
	time_loop(m_heap);
}
	
//returns and removes first element in heap and percolates down		
Job* ElegantQueue::time_pop(){
	Job* temp = m_heap[0];
	
	m_heap[0] = m_heap[m_heap.size()-1];
	m_heap.erase(m_heap.begin()+(m_heap.size()-1));
	

	unsigned int i = 0;
	while(2 * i + 1 < m_heap.size()){
		Job* child;
		int child_idx;
		if(2 * i + 2 < m_heap.size() && m_heap[2 * i + 2]->timestamp < m_heap[2 * i + 1]->timestamp){
			child = m_heap[2 * i + 2];
			child_idx = 2 * i + 2;
		}

		else{
			child = m_heap[2 * i + 1];
			child_idx = 2 * i + 1;
		}

		if(child->timestamp < m_heap[i]->timestamp){
			m_heap[child_idx] = m_heap[i];
			m_heap[child_idx] -> time_hook = child_idx;
			m_heap[i] = child;
			i = child_idx;
		}

		else{
			break;
		}
	}
	time_loop(m_heap);
	return temp;	
}

//prints heap
void ElegantQueue::time_printHeap( std::ostream & ostr ){
		ostr << "TQ " << m_heap.size() << " jobs:" << std::endl;
		for ( unsigned int i=0; i<m_heap.size(); ++i ){
			ostr << "\t" << m_heap[i];
		}
	}

//erases correct element in the heap and percolates down
void ElegantQueue::time_remove_from_index(eq_hook hook){
	m_heap.erase(m_heap.begin() + hook);
	unsigned int i = 0;
	while(2 * i + 1 < m_heap.size()){
		Job* child;
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
			m_heap[child_idx] -> urgent_hook = child_idx;
			m_heap[i] = child;
			i = child_idx;
		}

		else{
			break;
		}
	}
	time_loop(m_heap);
}