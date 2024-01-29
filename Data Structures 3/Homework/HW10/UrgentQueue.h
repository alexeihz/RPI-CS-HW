#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>

typedef int uq_hook; //Used to point to a location in the heap, fill in the "???"


//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue{

//////////FILL THIS IN///////////
private:
  std::vector<Job*> m_heap;

public:
	UrgentQueue();

	UrgentQueue( std::vector<Job*> const& values );

	const Job* top() const {return m_heap[0]; } //returns first element in the heap

	void push( Job* entry );
	
	Job* pop();

	int size() { return m_heap.size(); } //returns heap size
	bool empty() { return m_heap.empty(); } //checks if heap is empty
  
	void printHeap( std::ostream & ostr );
	
	void remove_from_index(uq_hook hook);
	
	void loop (std::vector<Job*> const& values);
};

#endif