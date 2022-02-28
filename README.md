                                                           Algorithms and Data Structures project

The aim of the project is to implement a system capable of ranking graphs of different sizes on the base of the least sum of distances from a node.
The input consists of two numbers, the number of nodes of the graphs and the length of the
ranking (k), followed by a series of commands, of only two types:
1. AddGraph [adjacency-matrix]
2. TopK

The goal is to print the top-k graphs at each TopK command, in ascending order by
sum of the shortest paths between node 0 and all the other reachable nodes of the graph
from 0.

IMPLEMENTATION

Programming language :
-	C


The main data structures used to manage the system are of 2 types: 

-	Binary heap
-	Red Black Tree

Algorithms used are:
-	Heapsort
-	Dijkstra

Tools used for dynamic memory allocation error checking, visualization of time employed by each function, and memory usage include :
-	 Valgrind -Memcheck,
-	 Valgrind-callgrind
-	 Valgrind -massif 

Test cases

The implementation has been tested and debugged with Public Tests and evaluated through Private Tests by a special platform able to determine the memory occupied and the execution time of the program. 

Compilation and Execution

To run the program compile the main.c file from the command line with the following flags:

-          gcc -Wmaybe-uninitialized -Wuninitialized -Wall -pedantic -Werror -g3 main.c -o main 
To run the program using one of the public inputs and check the output obtained with its output: 
-          cat input.txt | ./main> output.txt 
-          diff output.txt public_output.txt


![image](https://user-images.githubusercontent.com/61747783/155986022-d56c1d2f-7120-4d6a-a264-74c3524899a4.png)

