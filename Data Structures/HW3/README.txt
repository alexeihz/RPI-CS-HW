HOMEWORK 3: MATRIX CLASS


NAME:  < Alexei Hazell>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< cplusplus.com
stackoverflow.com
Garret Premo >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 48 >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get: O(1)

set: 0(1)

num_rows: 0(1)

get_column: 0(m*n)

operator<<: 0(m*n)

quarter: 0(m*n)

operator==: 0(m*n)

operator!=: 0(m*n)

swap_rows: 0(m*n)

rref (provided in matrix_main.cpp): 0(m^2 * n)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used Dr. Memory to help me see what my memory leaks were and where my memory leaks were occuring. I used std::cout to help me see what variables were doing where. I tested corner cases by making cases that would try to break my code. For example, matrices with size 0.


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.

I implemented resize() for extra credit.
resize(): 0(m*n)



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

