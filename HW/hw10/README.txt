HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Danny Zou >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Collaborators:

Resources:

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >

NAIVE ALGORITHM: 

Order Notation: O((w * h)^2 * p)


Timing Experiment Data: 
tiny_5x5.ppm : 0.00s user 0.00s system 55% cpu 0.005 total
small_10x10.ppm : 0.00s user 0.00s system 57% cpu 0.006 total
squiggle_30x30.ppm : 0.02s user 0.00s system 93% cpu 0.022 total
lines_100x100.ppm : 0.67s user 0.00s system 99% cpu 0.674 total
data_structures_300x300.ppm : 52.81s user 0.09s system 99% cpu 52.904 total
dots_1000x1000.ppm : 


Discussion:
I believe that the big O notation for the function is going to be O((w * h)^2 * p) because it goes through every single
pixel for the first time, then loops through the pixels again to look for black pixels, then it compares every single pixel 
to every black pixel. Looking at our timing experiment data, I believe that my order notation is pretty reliable for predicting 
run times even though we can't really figure out how many black pixels each image has.

IMPROVED ALGORITHM:

Order Notation: O(w * h) + (w * h) * p )

Timing Experiment Data:
tiny_5x5.ppm : 0.00s user 0.00s system 3% cpu 0.147 total
small_10x10.ppm : 0.00s user 0.00s system 58% cpu 0.004 total
squiggle_30x30.ppm : 0.00s user 0.00s system 63% cpu 0.010 total
lines_100x100.ppm : 0.06s user 0.00s system 96% cpu 0.062 total
data_structures_300x300.ppm : 5.80s user 0.01s system 99% cpu 5.818 total
dots_1000x1000.ppm : 

Discussion:
Looking at the timing experiment data for the improved algorithm, it is noticeably way faster than the naive algorithm. Except 
for the tinest 5x5 picture, which was a lot slower for some reason, it cut down run time for every single image by atleast 50%.
All I did was find every single black pixel first by looping through the pixels. Then I compared every pixel with each black pixel 
to find the biggest distance. I believe that my order notation is pretty reliable for predicting  run times even though we can't 
really figure out how many black pixels each image has.

FAST MARCHING METHOD (with a map):

Order Notation:

Timing Experiment Data:

Discussion:



DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






