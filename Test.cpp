#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {0, 6, 9, 5},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
     CHECK_THROWS(g1 - g6);
}

TEST_CASE("Test graph multiplication by scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * 2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    ariel::Graph g3 = g1 / 2;
    CHECK(g3.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test graph subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g2 - g1;
    vector<vector<int>> expectedGraph = {
        {0, 0, 1},
        {0, 0, 1},
        {1, 1, 0}};
    CHECK(g3.printGraph() == "[0, 0, 1]\n[0, 0, 1]\n[1, 1, 0]");
}

TEST_CASE("Test graph division by scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 4, 0},
        {-6, 0, 10},
        {0, 6, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 / 2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 0},
        {-3, 0, 5},
        {0, 3, 0}};
    CHECK(g2.printGraph() == "[0, 2, 0]\n[-3, 0, 5]\n[0, 3, 0]");
}

TEST_CASE("Test graph equality")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    CHECK(g1 == g1);
    CHECK(g2 == g2);
    CHECK_FALSE(g1 == g2);
}

TEST_CASE("Test graph inequality")

{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    CHECK(g1 != g2);
    CHECK(g2 != g1);
    CHECK_FALSE(g1 != g1);
    CHECK_FALSE(g2 != g2);
}

TEST_CASE("Test graph equals"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    CHECK(g1 == g1);
    CHECK(g2 == g2);
    CHECK_FALSE(g1 == g2);
}

TEST_CASE("Test graph less than")

{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    CHECK(g1 < g2);
    CHECK_FALSE(g2 < g1);
     CHECK((g1== g1));
    CHECK(g2 != g1);
}

TEST_CASE("Test empty graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 1},
        {2, 0, 4},
        {1, 4, 0}};
    g2.loadGraph(weightedGraph);
    CHECK(g1 != g2);
    CHECK(!(g1 == g2));
    CHECK(g1 < g2);
    ariel::Graph g3;
    g3=g1+g2;
    CHECK(g2==g3);
    g3=g2-g1;
    CHECK(g2==g3);
    g3=g1*g2;
    CHECK(g3==g1);
}

TEST_CASE("Test graph addition with empty graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> emptyGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g2.loadGraph(emptyGraph);
    ariel::Graph g3 = g1 + g2;
    CHECK(g3.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test graph multiplication with empty graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> emptyGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g2.loadGraph(emptyGraph);
    ariel::Graph g4 = g1 * g2;
    CHECK(g4.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test graph subtraction with empty graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> emptyGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g2.loadGraph(emptyGraph);
    ariel::Graph g4 =g1*-1;
    ariel::Graph g3 = g2 - g1;
    CHECK(g4==g3);
}

TEST_CASE("Test graph division by scalar with zero scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    CHECK_THROWS( g1 / 0);
    
}

TEST_CASE("Test graph equality with empty graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> emptyGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g2.loadGraph(emptyGraph);
    CHECK_FALSE(g1 == g2);
}

TEST_CASE("Test graph less than with empty graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> emptyGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g2.loadGraph(emptyGraph);
    CHECK_FALSE(g1 < g2);
    CHECK(g2 < g1);
}

