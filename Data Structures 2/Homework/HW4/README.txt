HOMEWORK 4: PREFERENCE LISTS


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15



ORDER NOTATION:
Give the order notation for each function below assuming
m schools, s slots per school, r rankings of students by each school,
n students, and p preferences of schools by each student.
Write one or two sentences justifying each answer.


add_school
O(s+m)
insert_student_into_school_preference_list
O(m*n)
print_school_preferences
O(p)
add_student
O(p+n)
remove_school_from_student_preference_list
O(n)
print_student_preferences
O(r)
perform_matching
O(s+n+m+p+r)
print_school_enrollments
O(m)
print_student_decisions
O(n)


OPTIONAL EXTRA CREDIT:
Describe the two different iterative loops that you selected to
rewrite using recursion.  



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

The autograder for test 4 and 5 isn't telling me what is wrong.
In the case of test 4, it says that actually nothing is wrong yet I am still getting 2 points off.

