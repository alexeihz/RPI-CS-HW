HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Alexei Hazell

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  7 hours



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity along with a short
justification for each of the functions below:

n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

loadConnections(): O(d)
	The while loop only has a single while loop that run until 	the file runs out of lines to read. The number of lines read 	will be equal to the total number off users with degree >= 1

loadLocations(): O(l)
	The while loop only has a single while loop that run until 	the file runs out of lines to read. The number of lines read 	will be equal to the total number off users with a location

printAllUsersWithinDistance():O(l) + O(l) + O(m * p)
	Loop 1: Goes through total number of users with a location. 		(Runtime O(l))
	Loop 2: Goes through total number of users with a location. 		(Runtime O(l))
	Loop 3: Goes through the total number of connections, while 		going through the amount the vector of users that are 			to be printed (Runtime O(m * p))

printDegreesHistogram(): O(n) + O(n) + O(p)
	Loop 1: Goes through entire map. (Runtime O(n))
	Loop 2: Goes through entire map. (Runtime O(n))
	Loop 3: Goes through the amount the vector of users that are 		to be printed (Runtime O(p))


printDegreesOfAll(): O(n)
	The function loops through all the users.(Runtime O(n))

printFriendsWithDegree(): O(n) + O(n * m)
	First, the total number of users is checked for the proper 	ID(Runtime O(n)). Next, the total number of users is checked 	again with the number of connections within that loop 	(Runtime O(n*m)).

printFriendsWithinDistance():O(n) + O(l) + O(l * m) + O(m * p)
	Loop 1: Goes through entire map. (Runtime O(n))
	Loop 2: Goes through total number of users with a location. 		(Runtime O(l))
	Loop 3: Goes through total number of users with a location 			while going through the total number of connections 			inside that loop (Runtime O(l * m))
	Loop 4: Goes through the total number of connections, while 		going through the amount the vector of users that are 			to be printed (Runtime O(m * p))

printUsersWithinIDRange(): O(n) + O(n) + O(p)
	Loop 1: Goes through entire map. (Runtime O(n))
	Loop 2: Goes through entire map. (Runtime O(n))
	Loop 3: Goes through the amount the vector of users that are 		to be printed (Runtime O(p))

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


This is my own code from a previous time taking the class. I checked with professor Holzbauer to make sure that doing this was okay.



