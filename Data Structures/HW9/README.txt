HOMEWORK 7: MINIBLAST


NAME:  Alexei Hazell


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  24


HASH FUNCTION DESCRIPTION

The hash function is the same one used in lab. It takes an input of a string and converts that string based on its characters into an integer value.




HASH TABLE IMPLEMENTATION

My hash table was a vector of pairs of strings and vectors of ints. First, I fill my hash table with place holders. Then, I hash every set of letters of kmer length in the dna. I took the hash and preformed a modulus on it with size. I took that value and set it as my location in the hashtable, changing the first element of the pair to the string of kmer length of dna pushing back the location of the string in the dna. After that, I hashed the query that I was given and preformed a modulus with size on it as well. Then, I went to that location in the hash table. If something was there, I tested it to find out if there was a match with the proper amount of mistakes or less. If there was a place holder value at that location, then there was no match.




ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?

O(L)
There are place holder values in the hash table, causing it to take up more memory.


What is the order notation for performance (running time) of each of the commands?

O(1)
It directly finds the location in the hashtable.

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


