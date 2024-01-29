#ifndef __ELEGANTQ_H_
#define __ELEGANTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>

typedef int eq_hook; //Used to point to a location in the heap, fill in the "???"


//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class ElegantQueue{

//////////FILL THIS IN///////////
private:
  std::vector<Job*> m_heap;

public:
	ElegantQueue();

	//ElegantQueue( std::vector<Job*> const& values );

	const Job* top() const {return m_heap[0]; } //returns first element in the heap

	void urgent_push( Job* entry );
	void time_push( Job* entry );

	Job* urgent_pop();
	Job* time_pop();

	int size() { return m_heap.size(); } //returns heap size
	bool empty() { return m_heap.empty(); } //checks if heap is empty
  
	void urgent_printHeap( std::ostream & ostr );
	void time_printHeap( std::ostream & ostr );
	
	void urgent_remove_from_index(eq_hook hook);
	void time_remove_from_index(eq_hook hook);
	
	void urgent_loop (std::vector<Job*> const& values);
	void time_loop (std::vector<Job*> const& values);
	
};

#endif