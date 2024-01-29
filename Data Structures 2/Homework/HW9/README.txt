HOMEWORK 10: IMAGE COMPARISON HASHING


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< stackoverflow.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 hours >




i = # of images
w = width x h = height (average size image)
s x s = seed size
r x r = typical subregion match. 
t = hash table size 
c = fraction of hash table to compare


ANALYSIS OF SIMPLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

Time:   O((i*w*h*s)^2)
You need to compare i*(i-1) image pairs, and for each pair, you need
to iterate w*h points in two images to find the same point, then for
each point pair, you need to check s*s seed points.

Memory: O(i*w*h)
You need to store i images, and each image requires to store w*h pixels.


ANALYSIS OF HASH TABLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.




SUMMARY OF RESULTS: 
Test your implementation on a variety of images and command line
arguments and summarize and discuss the results (both running time and
quality of results).




EXTRA CREDIT -- MULTIPLE ROTATION AND/OR 90/180/270 ROTATION AND
HORIZONTAL/VERTICAL FLIP:
Discuss your implementation and results of testing.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!






