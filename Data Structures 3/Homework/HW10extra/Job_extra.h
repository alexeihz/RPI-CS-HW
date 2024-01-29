#ifndef __JOBEXTRA_
#define __JOBEXTRA_
#include <string>
#include <ctime>    //Needed for std::time_t
#include <iostream>    //Needed for std::ostream
#include "ElegantQueue.h"


//Forward declarations to promise that these classes will exist
class ElegantQueue;

class Job{
public:
    Job(int pri, std::time_t time);
    Job(const Job& j);
    int getID() const { return job_id; }
    int getPriority() const { return priority; }
    std::time_t getTime() const { return timestamp; }
    void removeFromUrgent();
    void removeFromTime();

    //Both queue classes will need access.
    friend class ElegantQueue;
private:
    int job_id;
    int priority;
    std::time_t timestamp; 
    ElegantQueue* priority_ptr; //Pointer to my UrgentQueue object
    ElegantQueue* time_ptr; //Pointer to my TimeQueue object
    eq_hook urgent_hook; //location in the UrgentQueue heap
    eq_hook time_hook; //location in the TimeQueue heap
};

//Promise to declare stream output operator for a job
std::ostream& operator<<(std::ostream& out, const Job* j);

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);
#endif
