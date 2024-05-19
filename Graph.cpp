#include "Graph.hpp"
#include <vector>
using namespace std;
namespace ariel
{
    int numVertices;
    int numEdges;
    vector<vector<int>> adjacencyMatrix;
    bool isdirected;
    Graph::Graph()
    {
        numVertices = 0;
        numEdges = 0;
        isdirected=false;
        adjacencyMatrix = {};
    }
 
    void Graph::loadGraph(vector<vector<int>> graph)
    {
        if (graph.empty())
        {
            numVertices = 0;
            numEdges = 0;
            adjacencyMatrix = {}; // Already empty vector
            isdirected = false;
            return;
        }
        

        // Check if the graph is a square matrix.
        if (graph.size() == graph[0].size())
        {
            numVertices = graph.size();
        }
        else
        {
            throw invalid_argument("The graph is not a square matrix");
        }
        adjacencyMatrix = graph; // Load the mstrix to the graph
        int numofedges = 0;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[j][i] != 0)
                {
                    numofedges++;
                }
                if(adjacencyMatrix[i][j]!=adjacencyMatrix[j][i] && adjacencyMatrix[i][j]!=0 && adjacencyMatrix[j][i]!=0)
                {
                    throw invalid_argument("multy-graph is not allowed");
                }
                if(adjacencyMatrix[i][j]!=0 && adjacencyMatrix[j][i]==0 || adjacencyMatrix[j][i]!=0 && adjacencyMatrix[i][j]==0)
                {
                    isdirected=true;
                }
            }
        }
        numEdges = (int)numofedges / 2;
        numVertices = (int)graph.size();
        
    }
    vector<vector<int>> Graph::getAdjacencyMatrix()
    {
        return adjacencyMatrix;
    }
    void Graph::printGraph()
    {
        cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << endl;
    }
    size_t Graph::getNumVertices()
    {
        return (size_t)this->numVertices;
    }
    int Graph::getNumEdges()
    {
        return this->numEdges;
    }
    bool Graph::isDirected()
    {
        return isdirected;
    }
    Graph Graph::getTranspose(){
        Graph graph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                graph.adjacencyMatrix[i][j]=adjacencyMatrix[j][i];
            }
        }
       graph.loadGraph(adjacencyMatrix); 
        return graph;
    }
    
     // Unary + operator
    Graph Graph::operator+() {
        return *this;  // return a reference to the current graph
    }
    
     // Multiplication operator
     Graph Graph::operator*(int scalar){
            vector<vector<int>> GraphMat = getAdjacencyMatrix();
            Graph graph;
            for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    graph.getAdjacencyMatrix()[i][j]=GraphMat[i][j]*scalar;
                }
            }
           graph.loadGraph(adjacencyMatrix); 
        return graph;
    }
        // return a the sum of the current graph and the graph g
        Graph Graph::operator+(Graph &g){
            if(numVertices!=g.getNumVertices())
            {
                throw invalid_argument("The number of vertices in the two graphs must be equal.");
            }
            
            Graph graph;
            for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    graph.getAdjacencyMatrix()[i][j]=adjacencyMatrix[i][j]+g.getAdjacencyMatrix()[i][j];
                }
            }
            graph.loadGraph(adjacencyMatrix);
            return graph;
        }

        Graph Graph::operator+=(Graph &g){
            return *this+g;
        }

        Graph Graph::operator-(Graph &g){
            if(numVertices!=g.getNumVertices())
            {
                throw invalid_argument("The number of vertices in the two graphs must be equal.");
            }
            
            Graph graph;
            for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    graph.getAdjacencyMatrix()[i][j]=adjacencyMatrix[i][j]-g.getAdjacencyMatrix()[i][j];
                }
            }
            graph.loadGraph(adjacencyMatrix);
            return graph;
        }

        Graph Graph::operator-=(Graph &g){
            return *this-g;
        }
    
        Graph Graph::operator-(){
            Graph graph;
            for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    graph.getAdjacencyMatrix()[i][j]*=-1;
                }
            }
            graph.loadGraph(adjacencyMatrix);
            return graph;
}
 bool Graph::operator==(Graph &g)
    {
        if (!(*this >= g && *this <= g))
        {
            return true;
        }
        else
        {
            if (numVertices != g.getNumVertices())
            {
                return false;
            }
            for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    if (adjacencyMatrix[i][j] != g.getAdjacencyMatrix()[i][j])
                    {
                        return false;
                    }
                }
            }
        }
    }

    bool Graph::operator<(Graph &g)
    {
        if (numVertices > g.getNumVertices()|| numEdges > g.getNumEdges())
        {
            return false;
        }
        else{
               for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    if (adjacencyMatrix[i][j]   !=0 &&  g.getAdjacencyMatrix()[i][j]==0)
                    {
                        return false;
                    }
                }
            }
                        
            if(numVertices>g.getNumVertices() || numEdges>g.getNumEdges())
            {
                return false;
            }
            return true;
        } 
   }

    bool Graph::operator>(Graph &g){
        return g<*this;
    }



















































}
