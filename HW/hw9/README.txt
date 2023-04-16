HOMEWORK 9: MINIBLAST


NAME:  < Danny Zou >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Collaborators:
Nobody

Resources:
Took the hash function and simple implementation of hash table from Lab 11
https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables-with-linear-probing#:~:text=Linear%20probing%20is%20a%20collision,already%20occupied%20by%20another%20key.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6 >


HASH FUNCTION DESCRIPTION
Took the hash function from Lab 11. Which is a general purpose, very good 
hash function for strings.

HASH TABLE IMPLEMENTATION
My hash table is basically just a vector of pairs. With the first value of 
the pair being the kmer key as a string and the second value being a list of all the
positions on the genome the kmer key is found at. 

ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:

If we are only talking about my algorithm for getting the query results and not the initialization of the hashmap
with empty values, then I think first of all, inserting all the kmers of the genome sequence is going to take O(L-k)
time complexity. After inserting, we will need to find the specific kmer key in the hashmap which will only take O(1) time
complexity. After that, we will have to slowly build the query string based on the key size, which I think will
take O(q-k) time complexity. Adding on the number of different locations where the key is found, we need to consider how many
different times we have to go through the query length which makes the time complexity for this section O(p(q-k)). 


L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

Overall, I think the time complexity is going to be O((L-k) + p*(q-k))

How much memory will the hash table data structure require (order notation for memory use)?
The genome sequence will be taking up O(L) memory, and the keys will be taking O(L-k) memory.
Bring along the different positions each key can have, that becomes O((L-k)*p) memory.
I think overall, my program takes O(L*((L-k)*p)) memory.

What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

genome - O(L)
table_size - O(1)
occupancy - O(1)
kmer - O(L-k)
query - O(p*(q-k))


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
None


