HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?

O(m*w)


What is the order notation for performance (running time) of each of
the commands?

load - O(nlog m)
	The load command reads in every word of the file and if that word is not found in the map structure, then insert it in.
	If it is found in the map structure increase the integer value
print - O(wlog m)
	The print command loops for w and adds the integer to a count.
	Then in prints out the read word along with the count and the possible words that come after it with the number of times they appear after the word
generate - O(plog m)
	The generate command loops for p and, depending on a input value, randomly picks an element to follow the previous word or selects the most common word that comes after the previous one.



EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


