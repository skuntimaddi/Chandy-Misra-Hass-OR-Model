# Chandy-Misra-Hass-OR-Model
Implemenation of Chandy-Misra-Hass OR Model deadlock detection algotithm
Source Code:
The source code file is CMH_OR.cpp. 

Language used:
C++

Build environment:
The source file was built on Ubuntu operating system.
The compiler used was g++ for Linux.
 

Description:
The source code used two recursive functions:
1.	engaging_query: This routine counts the number of paths that are start from a node which initiates the probes and end at the same node. In other words the routine sned engaging query to all the incident edges on the node. The routine counts number of such paths and reports them ad number of deadlocks found in the graph.
2.	reply_query: This reply routine send the reply query from each node in response to the engaging query. In other words this routine traces the path to the node that initiated the probe in reverse and counts the number of paths available. The number of paths are reported as number of nodes available in the system.
The other routines are
3.	Main: function which takes in the user input
4.	display_graph: A function which displays the graph in matrix form.
The program should detect the number of deadlocks [i.e., the forward paths] equal to number of knots [i.e., the reverse paths] to conclude that the Chandy-Misra-Hass algorithm for OR model is validated.

Inputs:
1.	The user need to provide the following inputs:
2.	Number of sites
3.	Number of processes per site
4.	If there is an edge incident form one node to another in the graph, Enter 1
5.	If no edge is incident on one node Enter 0.
6.	Enter the node number initiating the probe.

Outputs:
1.	Display of graph in matrix form
2.	Number of deadlocks detected
3.	Number of knots detected
4.	Conclusion.

Sample output:
For a 6 node graph with dependency as given below
P1 -> P2
P2 -> P3
P2 -> P4
P2 -> P5
P2 -> P6
P3 -> P4
P4 -> P5
P5 -> P6
P6 -> P1


The input would be 
Enter number of sites(minimum value greater than 1):
3
Enter number of processes for site1: (minimum value greater than 1)
2
Enter number of processes for site2: (minimum value greater than 1)
2
Enter number of processes for site3: (minimum value greater than 1)
2
Enter the process initiating the probe (Between 1 and no. of processes)
2

The output would be 
The wait-for graph is : 
	S1	S2	S3	S4	S5	S6	
S1	0	1	0	0	0	0	
S2	0	0	1	1	1	1	
S3	0	0	0	1	0	0	
S4	0	0	0	0	1	0	
S5	0	0	0	0	0	1	
S6	1	0	0	0	0	0

Initiating Probe.....

DIRECTION 	 PROBE 	 MESSAGES 	 WAIT FLAG
 S2 --> S3     (2,2,3) , 	1 , 	4
 S3 --> S4     (2,3,4) ,	 1 ,	 1
 S4 --> S5     (2,4,5) ,	 1 ,	 1
 S5 --> S6     (2,5,6) ,	 1 ,	 1
 S6 --> S1     (2,6,1) ,	 1 ,	 1
 S1 --> S2     (2,1,2) --------> DEADLOCK DETECTED HERE
 S2 --> S4     (2,2,4) , 	1 , 	4
 S4 --> S5     (2,4,5) ,	 1 ,	 1
 S5 --> S6     (2,5,6) ,	 1 ,	 1
 S6 --> S1     (2,6,1) ,	 1 ,	 1
 S1 --> S2     (2,1,2) --------> DEADLOCK DETECTED HERE
 S2 --> S5     (2,2,5) , 	1 , 	4
 S5 --> S6     (2,5,6) ,	 1 ,	 1
 S6 --> S1     (2,6,1) ,	 1 ,	 1
 S1 --> S2     (2,1,2) --------> DEADLOCK DETECTED HERE
 S2 --> S6     (2,2,6) , 	1 , 	4
 S6 --> S1     (2,6,1) ,	 1 ,	 1
 S1 --> S2     (2,1,2) --------> DEADLOCK DETECTED HERE
Number of deadlocks detected:4
Printing wait message array = [1 , 4 , 1 , 1 , 1 , 1 , ]

 Detecting knot by checking on the response messages.
 S2 --> S1     (2,2,1) , 	1 , 	4
 S1 --> S6     (2,1,6) , 	0 , 	0
 S6 --> S5     (2,6,5) , 	0 , 	0
 S5 --> S4     (2,5,4) , 	0 , 	0
 S4 --> S3     (2,4,3) , 	0 , 	0
 S3 --> S2     (2,3,2) --------> KNOT DETECTED HERE
 S4 --> S2     (2,4,2) --------> KNOT DETECTED HERE
 S5 --> S2     (2,5,2) --------> KNOT DETECTED HERE
 S6 --> S2     (2,6,2) --------> KNOT DETECTED HERE
Number of knots detected:4
Equal number of Deadlock and Knot detected. 
All sent messages were received. 
Hence the Chandy-Misra-Hass OR detected is validated..


