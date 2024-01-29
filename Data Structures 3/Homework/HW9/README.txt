HOMEWORK 9: IMDB SEARCH


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com
stackoverflow.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  50 hours


HASH FUNCTION DESCRIPTION

My hash function is takes in an std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > >.
Then, using the hash funciton from class, it hashes all of the data in the first member of the pair.





HASH TABLE IMPLEMENTATION

My hash table is a std::vector<std::pair<std::vector<std::vector<std::string> >, std::vector<std::vector<std::vector<std::string> > > > >.
The first member of the pair is the partially completed movie while the second member is a vector of completed movies that match the partially completed one.
I can go through the hash table and find the partially completed movie to thus find all the movies that could complete it.




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

It actually works but it takes too long to run on submitty

