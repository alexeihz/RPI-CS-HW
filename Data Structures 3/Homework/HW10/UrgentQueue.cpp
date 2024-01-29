#include <ctime>
#include <vector>
#include "Job.h"
#include "UrgentQueue.h"

UrgentQueue::UrgentQueue() {}
UrgentQueue::UrgentQueue( std::vector<Job*> const& values ){
	for(unsigned int j = 0; j < values.size(); j++){
		m_heap.insert(m_heap.begin(), values[j]);
		
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
		loop(m_heap);
	}
}

//loops through heap to assign correct hook values
void UrgentQueue::loop(std::vector<Job*> const& values){
	for(unsigned int i = 0; i< values.size(); i++){
		values[i] -> urgent_hook = i;
	}	
}

//adds element to the heap and percolates up
void UrgentQueue::push( Job* entry ){
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
	loop(m_heap);
}
	
//returns and removes first element in heap and percolates down	
Job* UrgentQueue::pop(){
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
	loop(m_heap);
	return temp;	
}

//prints heap
void UrgentQueue::printHeap( std::ostream & ostr ){
		ostr << "UQ " << m_heap.size() << " jobs:" << std::endl;
		for ( unsigned int i=0; i<m_heap.size(); ++i ){
			ostr << "\t" << m_heap[i];
		}
	}
	
//erases correct element in the heap and percolates down
void UrgentQueue::remove_from_index(uq_hook hook){
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
	loop(m_heap);
}
	
