#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "doctest.h"
#include <iostream>
#include <vector>
using namespace std;
namespace ariel
{
    class Graph
    {
        vector<vector<int>> adjacencyMatrix;
        int numVertices;
        int numEdges;
        bool isdirected;

    public:
        Graph();
        // this function will load the graph to the object
        void loadGraph(vector<vector<int>> graph);

        // this function will print the graph
        string printGraph();

        // this function will return the adjacency matrix of the graph
        vector<vector<int>> getAdjacencyMatrix() ;

        // this function will return the number of vertices in the graph
        size_t getNumVertices() const;

        // this function will return the number of edges in the graph
        int getNumEdges()const;

        // this function will return true if the graph is directed and false if it is not
        bool isDirected()const;

        // this func will return the reverse graph
        Graph getTranspose();

        // this func is an unary operator that will return the graph
        Graph operator+();

        // this funcrion will return the graph after multiplying it by a scalar
        Graph operator*(int scalar);

        // this funcrion will return the graph after multiplying it by a scalar
        Graph operator*=(int scalar);

        // this function will return the graph after multiplying it by another graph
        Graph operator*(Graph &graph);

        // this function will return the graph after devideing it by a scalar
        Graph operator/=(int scalar);

        // this function will return the graph after devideing it by a scalar
        Graph operator/(int scalar);

        // this function will return the graph after adding two graphs together
        Graph operator+(Graph &graph);

        // this function will return the graph after adding two graphs together
        Graph operator+=(Graph &graph);

        // this function will return the graph after subtracting two graphs together
        Graph operator-(Graph &graph);

        // this function will return the graph after subtracting two graphs together
        Graph operator-=(Graph &graph);

        // this func is an unary operator that will return the graph
        Graph operator-()const;

        // this function will return the graph after addung 1 to each edge in the graph
        void operator++();

        // this function will return the graph after substracing 1 from each edge in the graph
        void operator--();

        // this function will return the graph after addung 1 to each edge in the graph
        void operator++(int);

        // this function will return the graph after substracing 1 from each edge in the graph
        void operator--(int);

        // this function will return if the two graphs are equal
        bool operator==(Graph &graph);

        // this function will return if the graph is lees than the other graph
        bool operator<(Graph &graph);

        // this function will return if the other graph is lees than the  graph
        bool operator>(Graph &graph);

        // this function will return if the other graph is lees than or equal than the  graph
        bool operator>=(Graph &graph);

        // this function will return if the other graph is lees than or equal than the  graph
        bool operator<=(Graph &graph);

        // this function will return if the other graph is not equal to the graph
        bool operator!=(Graph &graph);

        // this function will check if g1 is contained in g2
        static bool isContained(Graph &graph1, Graph &graph2);

        // this function will print the graph
        friend ostream &operator<<(ostream &os, Graph &graph);

    };
}
#endif
