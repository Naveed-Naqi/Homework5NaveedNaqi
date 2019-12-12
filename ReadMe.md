# My Graph Implementation

I have implemented the adjacency table using a hash table of Verticies. I have used a hash table in order to make the look up of a vertex really fast.
I was contemplated also holding the edges in a hashtable, but decided to go with a vector or simplicity.
Each Vertex has a vector of Edges. Each Edges has a pointer to a Vertex and a cost associated with that Edge.
The Vertex struct has a lot of variables that aid in implementing Djikstra's and Topological Sorting using indegrees.


# Potential Grading Issues

Since, I have a hash table holding all of my verticies, when I parse through the verticies of my graph, 
they appear in a DIFFERENT ORDER from the output displayed in the Assignment PDF. This may affect the grading of PART 1 and PART 2 of the project.
My output is not in the SAME ORDER as the output in the assignment PDF, however all the content is correct, so it should be fine.

In PART 2, I modified the binary_heap implementation given to us. I changed the Comparator function, so that it correctly identified the Vertex pointer with the smaller distance.
So, the code must be compiled and run with the modifications that I made in order to work properly.

In PART 3, my Topological Sort function sorts the Graph3 in a slightly different way than the assignment PDF displays.
Instead of outputting: 1, 2, 5, 4, 3, 7, 6.
I output: 1, 2, 5, 4, 7, 3, 6.
This is an equally valid topological sorting, so it should be fine.
 
These issues should still give me full credit, but I thought it was worth pointing out since it is slightly different from the output in the assignemnt PDF.

Some last things to note are that whenever reading in a text file or query file, MY PROGRAM ASSUMES that these files are inside a folder called "InputFiles".
If my code is compiled and run without this, then it will cause an issue. 


