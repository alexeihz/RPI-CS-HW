#include <ctime>
#include <vector>
#include "Job.h"
#include "TimeQueue.h"

TimeQueue::TimeQueue() {}
TimeQueue::TimeQueue( std::vector<Job*> const& values ){
	for(unsigned int j = 0; j < values.size(); j++){
		m_heap.insert(m_heap.begin(), values[j]);

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
		loop(m_heap);
	}
}

//loops through heap to assign correct hook values
void TimeQueue::loop(std::vector<Job*> const& values){
	for(unsigned int i = 0; i< values.size(); i++){
		values[i] -> time_hook = i;
	}
}
	
//adds element to the heap and percolates up
void TimeQueue::push( Job* entry ){
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
	loop(m_heap);
}
	
//returns and removes first element in heap and percolates down		
Job* TimeQueue::pop(){
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
	loop(m_heap);
	return temp;	
}

//prints heap
void TimeQueue::printHeap( std::ostream & ostr ){
		ostr << "TQ " << m_heap.size() << " jobs:" << std::endl;
		for ( unsigned int i=0; i<m_heap.size(); ++i ){
			ostr << "\t" << m_heap[i];
		}
	}

//erases correct element in the heap and percolates down
void TimeQueue::remove_from_index(tq_hook hook){
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
	loop(m_heap);
}