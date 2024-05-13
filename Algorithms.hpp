#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include "Graph.hpp"
#include <string>
namespace ariel{
 class Algorithms{
  public:
    // this function will return a cycle in the graph. If there is no cycle, it will return 0
    static string isContainsCycle(Graph& g);

    // this function will return 1 if the graph is connected and 0 if it is not.
    static int isConnected( Graph& g);

    // this function will return the shortest path between two vertices as a string. If there is no path, it will return an empty string.
    static string shortestPath( Graph &g, int start, int end);

    // this function will return a string "The graph is bipartite"+the sets if the graph is bipartite and an empty string if it is not.
    static string isBipartite( Graph& g);

    // this function will return the negative cycle in the graph as a string if there is one. If there is no negative cycle, it will return "no negative cycle".
    static string negativeCycle( Graph& g);

    // the following functions are helper functions for the above . 


    // this function will return the  neighbors of a vertex in the graph 
    static  vector<int> getNeighbors(Graph& graph,int vertex);

    // Recursive DFS helper function
    static bool DFSUtil(ariel::Graph& graph, size_t v, vector<bool>& visited); 
    
    // DFS function using recursion and tracking parent for cycle detection
    static bool dfsForCycle(  vector<  vector<size_t>>& G,   vector<bool>& visited,   vector<int>& parent, size_t curr);
    
    // Function to convert vector to string
    static vector<size_t> CycleVectrorToString(size_t startNode, size_t endNode, vector<size_t>& parent);

    // a helper function to check if the graph is cyclic
    static bool isCyclicUtil(size_t ver, vector<bool>& visited,   vector<bool>& recStack,   vector<size_t>& parent,  Graph& graph,   vector<size_t>& cycle);

};
}
#endif
