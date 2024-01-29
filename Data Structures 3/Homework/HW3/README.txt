HOMEWORK 3: RESIZABLE TABLE


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 20 hours



ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.


Just to make sure 
n = the number of rows of the 'this' table
m = the number of columns of the 'this' table


get: O(1)

set: O(1)

numRows: O(1)

numColumns: O(1)

push_back_row: O((n+1)*m) + O(n*m) +O(m) + O(n*m) = 3*O(n*m) + O(m) = O(n*m) + O(m)

push_back_column: O((m+1)*n) + O(n*m) + O(n) + O(n*m) = 3*O(n*m) + O(n) = O(n*m) + O(n)

pop_back_row: O((n-1)*m) + O((n-1)*m) + O(n*m) = 3*O(n*m) = O(n*m)

pop_back_column: O((m-1)*n) + O((m-1)*n) + O(n*m) = 3*O(n*m) = O(n*m)

print: O(n*m)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?

I used Dr. Memory to debug my program. I tested the corner cases using a std::cout and print strategy

EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

I implemented push_back for multiple rows and multiple columns

a = the number of rows in the other table
b = the number of columns in the other table


push_back_rows: O((n+1)*m) + O(n*m) + O(m*a) + O(n*m) = 3*O(n*m) + O(m*a) = O(n*m) + O(m*a)

push_back_columns: O((m+1)*n) + O(n*m) + O(n*b) + O(n*m) = 3*O(n*m) + O(n*b) = O(n*m) + O(n*b)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

