HOMEWORK 10: JOB PRIORITIZATION


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.
Online resources should have specific URLs

cplusplus.com
ALAC tutoring
Alexei Hazell

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20 hours


EXTRA CREDIT
As described in the hw.pdf create a new ElegantQueue that can function as a TimeQueue or
as an UrgentQueue. Describe the changes you had to make to main/Job, and how your ElegantQueue
supports both getting the highest urgency Job and getting the earliest Job.

I essentially put functions from both UrgentQueue and TimeQueue into one function.
I made specific functions so that the ElegantQueue could tell the difference between which type of queue it was representing.
For example, I have an urgent_push function to use when the ElegantQueue is representing a UrgentQueue and a time_push function for when the ElegantQueue is representing a TimeQueue.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

Some of this code is from when I previously took this class.

