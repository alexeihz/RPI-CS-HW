HOMEWORK 6: BATTLESHIP RECURSION


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



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  78



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of ships (s)? 
The total number of occupied cells (o) or open water (w)? 
The number of constraints (c)? 
The number of unknown sums (u) or unspecified ship types (t)? 
Etc. 

In theory, my order notation for the dimensions of the board would be O(w*h). For the number of ships, the order notation should be O(1). The total number of occupied cells/open water I don't deal with in my code. The order notation for the number of constraints would be O(1) because I would just look for the constarint and just put the ship there. The order notation of the number of unknown sums would be O(1) because I would deal with those as a last case and change the question mark to the number of the spaces taken up. My unknown ships would be O(w*h). 


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

My code doesn't exactly work properly as you can no doubt see so I'm just gonna try and explain what my thought process was as briefly as possible. I wanted to hash the ships to a string of numbers representing the (x,y), the length, and the orientation and add all of them to a vector. Then, I would combine all the hashed ships into one string and add that to another vector of hashed boards. I would then use the string of numbers, or the "ids" to compare the boards and determine if that solution already existed.


