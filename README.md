Hi there, this is a little bit of explaining about this project:
pursuant to the previous task i have added some operators to the Graph


**Namespace**

* `ariel`: Encapsulates the functionalities within the `ariel` namespace.
**Graph.cpp**
  This class represents the Graph object with some functionalities that needed
  
**Algorithms.hpp**

This header file defines the `Algorithms` class which provides various graph algorithms implemented in C++.


**Class: Algorithms**

This class provides various graph algorithms:

* `isConnected(Graph& g)`: Checks if a graph is connected and returns 1 if it is, 0 otherwise.
* `shortestPath(Graph &g, int start, int end)`: Finds the shortest path between two vertices in a graph and returns it as a string. If there is no path, it returns "-1".
* `isContainsCycle(Graph& g)`: Checks if a graph contains a cycle and returns a string represnt the cycle if not retuns "0"
* `isBipartite(Graph& g)`: Checks if a graph is bipartite and returns a string indicating the bipartition or an empty string if the graph is not bipartite.
* `negativeCycle(Graph& g)`: Check if there a negative cycle in a graph. If there is no negative cycle, it returns "no negative cycle".
The code also posses a helper functions and all of the function was with the help of Gemini with various prompts (variant on the task)

**Compiling and Running**

The project uses a Makefile to compile and run the code. You can compile the code using the following command:

```bash
make
```

This will create an executable named `demo`. You can then run the program using the following command:

```bash
./demo
```
or
```bash
./test 
```
