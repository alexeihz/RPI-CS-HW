HOMEWORK 6: INVERSE SLITHERLINK RECURSION


NAME:  Alexei Hazell



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Alac tutoring

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >
25

ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of labeled cells in the puzzle (n)? 
The number of edges in the closed loop fence path (e)?
Etc. 



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.  



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

Aight so my code obviously doesn't work properly so I am going to try to explain how it should work and what my thought process was. 
My idea was to try and go through every possible iteration of the board at the same time. So I would place both a 1 and 0 done whenever I see a -1. I would then check to see if there were the correct number of lines touching each square. After making these checks, I would then have to ensure that all the lines were connected and that no more or no less than 2 lines met at a point. Theses would give me correctly filled out boards and I would return 1 to get out of my recusive function. All the boards that had failed I would return 0. Then I would add all the correct solutions to the solution vector.