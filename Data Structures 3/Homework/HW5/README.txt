HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com, stackoverflow.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30 hours



TESTING & DEBUGGING STRATEGY:
Please be concise!  

I used dr. memory a lot a long with std::cout testing.


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

Everything in the iterator class is constant

size: O(1)
empty: O(1)
clear: O(n) where n is the number of nodes in the list
front: O(1)
back: O(1)
push_front: O(n) where n is the number of elements in the node
pop_front: O(n) where n is the number of elements in the node 
push_back: O(1)
pop_back:  O(n) where n is the number of elements in the node
operator==: O(n) where n is number of nodes in the list
operator!=: O(n) where n is number of nodes in the list
erase: O(n) where n is the number of elements in the node
insert: O(n) where n is the number of elements in the node
copy_list: O(n * m) where n is the number of nods in the list and m is the number of elements in the node
destroy_list: O(n) where n is the number of nodes in the list
print: O(n*m) where n is the number of nodes in the list and m is the number of elements in the node 

The UnrolledLL can hold multiple elements in each node while the dslist cannot.
The UnrolledLL has a less expensive erase option than the STL list.

This data structure would be inefficient when there are incomplete nodes with the total number of elements is less than the maximum number of elements that can be held in a node.
This causes more memory than necessary to be allocated.

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


