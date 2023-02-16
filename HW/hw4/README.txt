HOMEWORK 4: TOOL RENTAL LISTS


NAME:  < Danny Zou >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Collaborators:
Nobody

References:
https://www.geeksforgeeks.org/list-cpp-stl/
https://www.geeksforgeeks.org/list-erase-function-in-c-stl/
https://cplusplus.com/reference/list/list/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >

ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.

i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file: O(i)

Rental event: O(i^c)

Return event - no pending customer(s): O(e)

Return event - with pending customer(s): O(e^p)

Entire program: O(I+(I^c)+(e^p)+(e^I)+(c)+(I^c+c)) 



MISC. COMMENTS TO GRADER:
I tried to make it efficient but it backfired

