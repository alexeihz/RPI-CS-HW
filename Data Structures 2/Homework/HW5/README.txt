HOMEWORK 5: LINKED GRID


NAME: Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Leon Montealegre, cplusplus.com, stackoverflow.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



COMPLEXITY ANALYSIS:
Give the big 'O' notation for each function (or function group) below
assuming the grid is w nodes wide and h nodes high.  Write one or two
sentences justifying each answer.


Grid constructor - O(1) Sets the grid's width and height to 0
Grid copy constructor - O(1) Sets the copy grid's width and height to old grid's width and height
Grid assignment operator - O(h + w) There are 2 for loops run for the width and height but they aren't nested
Grid destructor - O(wh) There is a nested for loop for the width and height in Grid clear which the destructor calls

Grid getWidth - O(1) It is a returning the width
Grid getHeight - O(1) It is a returning the height
Grid getSize - O(1) It is a returning the size

Grid get - O(h + w) There are 2 for loops run for the width and height but they aren't nested
Grid set - O(h + w) There are 2 for loops run for the width and height but they aren't nested

Grid print - O(wh) There is a nested for loop for the width and height

Grid reset - O(hw^2 + wh^2) The nested for loop causes the O notation to be O(hw) but I also have to multiply that by the O notation of set() which is O(w + h)
Grid clear - O(wh) There is a nested for loop for the width and height

Grid join - O(h) There is only one loop and it is for the height
Grid stack - O(w) The while loop in stack_rows only goes for the width of the grid
Grid chop - O(2w + h) There are 2 while loops that can go for the width of the grid and a while loop that can go for the height of the grid
Grid lift - O(2h + w) There are 2 while loops that can go for the height of the grid and a while loop that can go for the width of the grid

Grid begin_upper_left - O(1) Returns iterator to the upper_left of the grid
Grid begin_upper_right - O(1) Returns the iterator to the upper right of the grid 
Grid begin_lower_left - O(1) Returns the iterator to the lower left of the grid 
Grid begin_lower_right - O(1) Returns the iterator to the lower right of the grid 
Grid end - O(1) Returns NULL

GridIterator operator* - O(1) Returns the ptr's value

GridIterator left - O(1) Sets the ptr to the left of the iterator to the ptr and returns the iterator
GridIterator right - O(1) Sets the ptr to the right of the iterator to the ptr and returns the iterator
GridIterator up - O(1) Sets the ptr above the iterator to the ptr and returns the iterator
GridIterator down - O(1) Sets the ptr below the iterator to the ptr and returns the iterator

Grid begin_snake - O(1) Returns the beginning of the snake iterator 
Grid end_snake - O(1) Returns NULL
Grid begin_spiral - O(1) Returns the beginning of the spiral iterator 
Grid end_spiral - O(1) Returns NULL

GridIterator operator++ for snake - O(1) This operator only changes the ptr 
GridIterator operator-- for snake
GridIterator operator++ for spiral - O(1) This operator only changes the ptr 
GridIterator operator-- for spiral



OPTIONAL EXTRA CREDIT:
Describe your implementation choices here.  



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20 hours



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


