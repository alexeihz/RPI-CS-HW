#include <ctime>
#include <vector>
#include "UrgentQueue.h"

UrgentQueue::UrgentQueue() {}
UrgentQueue::UrgentQueue( std::vector<Job*> const& values ){
		for(unsigned int j = 0; j < values.size(); j++){
			m_heap.insert(m_heap.begin(), values[j]);
			loop(m_heap);
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
		}
	}
	
void UrgentQueue::loop(std::vector<Job*> const& values){
	for(unsigned int i = 0; i< values.size(); i++){
		values[i] -> urgent_hook = i;
	}	
}
	
void UrgentQueue::push( Job* entry ){
		m_heap.push_back(entry);
		entry -> priority_ptr = this;
		loop(m_heap);
		//std::cout << "???\n";
		int i = m_heap.size() - 1;
		while(( (i - 1) / 2) >= 0){
		  //std::cout << i << "\n";
			if(m_heap[i] < m_heap[(i - 1)/2]){
				Job* x = m_heap[i];
				m_heap[i] = m_heap[(i-1) / 2];
				m_heap[(i-1) / 2] = x;

				i = (i - 1) / 2;
			}

			else{
				break;
			}
		}
	}
	
Job* UrgentQueue::pop(){
		//assert( !m_heap.empty() );
		Job* max;
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
		Job* temp = m_heap[0] + max_idx;
		m_heap.erase(m_heap.begin() + max_idx);
		loop(m_heap);
		
		return temp;
	}
	
void UrgentQueue::printHeap( std::ostream & ostr ){
		ostr << "UQ " << m_heap.size() << " jobs:" << std::endl;
		for ( unsigned int i=0; i<m_heap.size(); ++i ){
			ostr << "\t" << m_heap[i] << std::endl;
		}
	}
	
void UrgentQueue::remove_from_index(uq_hook hook){
		//std::cout << hook << std::endl;
		m_heap.erase(m_heap.begin() + hook);
		loop(m_heap);
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
	}
	
