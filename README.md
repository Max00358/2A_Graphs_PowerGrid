# 2A_Graphs_PowerGrid
In this project, a graph data structure is implemented to store a weighted, undirected graph. In addition, **Kruskal's algorithm, merge sort** and **union find path compression** technique is applied to find a Minimum Spanning Tree (MST) of the graph. This algorithm is implemented in, at worst, O(|E|log(|V|)) time, where |E| is the number of edges in the graph and |V| is the number of vertices.<br/>

Functionalities:<br/>
  * **LOAD**: Load a dataset into a graph.<br/>
  * **INSERT**: Insert a new edge into the graph from vertex a to vertex b with weight w. If either a or b are not in the graph, add them. Valid values a and b will be positive integers between 1 and 50000 inclusive and valid values of w will be a positive integer weight greater than 0. <br/>
  * **PRINT**: Print all vertices adjacent to vertex a. Valid values for a will be a positive integer between 1 and 50000. The order in which you print the vertices is not important. The Autograder will be programmed to handle any ordering. <br/>
  * **DELETE**: Delete the vertex a and any edges containing a. Note that this means you will need to remove the vertex a from the edge set of all vertices adjacent to a. This command may produce an unconnected graph.<br/>
  * **MST**: Find the MST of the graph. You may assume that the graph is connected. <br/>
  * **COST**: Determine the cost (the sum of the weights) of the power grid computed via the MST. You may assume the cost will never overflow an int on eceubuntu. <br/>
  * **END**: Last command for all input files.
  
  
