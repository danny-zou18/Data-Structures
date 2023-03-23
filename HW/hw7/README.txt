HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  < Danny Zou >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Collaborators:
Matthew Bui

Resources:
https://cplusplus.com/reference/map/map/
https://www.udacity.com/blog/2020/03/c-maps-explained.html
https://www.geeksforgeeks.org/set-in-cpp-stl/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6 >

ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move

reading the database/populating your initial data structure:

-q (specific move): O(f * log(f) + f * m * log(m))
I first initialize the databases at the start so thats always going to take atleast f^2 time
, then find the character name which is log(f) then the move name which is log(m) then
multiply by the number of moves

-q (all): O(f * log(f) + f * m^2)
Now we are not finding a specific move, but all the moves, so we loop through the moves twice
which gives us m^2

-f: O(f * log(m) + f * t * m ) 

-s: O(f * log(m)  + f * t * m)    For f and , they are all pretty much the same

-d: O(f^2 * log(m) + f^2)
Because we iterate through the characters twice in the commandD function, it adds a time complexity of f^2

MISC. COMMENTS TO GRADER:  
Nothing to comment, thx for grading






