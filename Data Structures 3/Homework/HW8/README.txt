HOMEWORK 8: ROPES


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com
ALAC tutors 
TAs

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  50 hours

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor: 
	1. O(p) because I go from the root to every leaf in the tree
	2. O(p) because I go from the root to every leaf in the tree

Construct from Node*: 
	1. O(p) because I have to go from the root to the furthest right leaf to get the size
	2. O(p) because I have to go from the root to the furthest right leaf to get the size
	
Index: 
	1. O(p) becuase I have to find the a leaf
	2. O(p) becuase I have to find the a leaf

Report: 
	1. O(p^2) because I have to find a leaf multiple times
	2. O(p^2) because I have to find a leaf multiple times

iterator operator++: 
	1. O(p) because I have to go to every node
	2. O(p) because I have to go to every node

Split:
	1. O(5p)
	2. O(5p)

Concat: 
	1. O(3p) because I have to copy the entire tree, find all the leaves, and get the size.
	2. O(3p) because I have to copy the entire tree, find all the leaves, and get the size.

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

lots of printing


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

I did not have a ValidRope() assertion in my main file and so I did not know what the assertion wanted me to fix.
Please be kind to me. I stuggled and put a lot of time in office hours