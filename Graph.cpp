#include "Graph.hpp"
#include <vector>
using namespace std;

namespace ariel
{
    // Constructor
    Graph::Graph(): numVertices(0), numEdges(0), isdirected(false), adjacencyMatrix(3, vector<int>(3, 0)) {}

    // Load the graph from a given matrix
    void Graph::loadGraph(vector<vector<int>> graph)
    {
        // Check if the graph is a square matrix.
        if (graph.size() != graph[0].size())
        {
            throw invalid_argument("The graph is not a square matrix");
        }
        if (graph.empty())
        {
            numVertices = 0;
            numEdges = 0;
            adjacencyMatrix = {}; 
            isdirected = false;
            return;
        }
        adjacencyMatrix = graph; // Load the matrix to the graph
        int numofedges = 0;
        numVertices = (int)graph.size(); // Set the number of vertices
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[j][i] != 0)
                {
                    numofedges++;
                }
                if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[j][i] == 0 || adjacencyMatrix[j][i] != 0 && adjacencyMatrix[i][j] == 0)
                {
                    isdirected = true;
                }
                adjacencyMatrix[i][i] = 0; // Remove self loops caused by matrix initialization
            }
        }
        if (isdirected)
        {
            numEdges = numofedges; // If the graph is directed, the number of edges is the number of edges in the matrix
        }
        numEdges = (int)numofedges / 2; // Otherwise, the number of edges is half the number of edges in the matrix
    }

    // Get the adjacency matrix of the graph
    vector<vector<int>> Graph::getAdjacencyMatrix()
    {
        if (adjacencyMatrix.empty())
        {
            throw invalid_argument("The graph is empty");
        }
        return adjacencyMatrix;
    }

    // Print the graph as a string
    string Graph::printGraph()
    {
        if (adjacencyMatrix.empty())
        {
            return "[]";
        }
        string str = "";
        for (size_t i = 0; i < getNumVertices(); i++)
        {
            str += "[";
            for (size_t j = 0; j < getNumVertices(); j++)
            {
                str += to_string(getAdjacencyMatrix()[i][j]);
                if (j != getNumVertices() - 1)
                {
                    str += ", ";
                }
            }
            str += "]";
            if (i != getNumVertices() - 1)
            {
                str += "\n";
            }
        }
        return str;
    }

    // Get the number of vertices in the graph
    size_t Graph::getNumVertices() const
    {
        return (size_t)this->numVertices;
    }

    // Get the number of edges in the graph
    int Graph::getNumEdges() const
    {
        return this->numEdges;
    }

    // Check if the graph is directed
    bool Graph::isDirected() const
    {
        return isdirected;
    }

    // Get the transpose of the graph
    Graph Graph::getTranspose()
    {
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph graph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[j][i]; // Assign the transpose of the matrix
            }
        }
        graph.loadGraph(newAdjacencyMatrix);
        return graph;
    }

    // Unary + operator
    Graph Graph::operator+()
    {
        return *this; // Return a reference to the current graph
    }

    // Multiplication operator
    Graph Graph::operator*(int scalar)
    {
        if (scalar == 0 || this->getNumVertices() == 0)
        {
            return Graph(); // Return an empty graph
        }
        vector<vector<int>> GraphMat = getAdjacencyMatrix(); // Get the adjacency matrix of the graph
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0)); // Create a new matrix for the new graph
        Graph graph; // Create a new graph
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = GraphMat[i][j] * scalar; // Multiply each element in the matrix by the scalar
            }
        }
        graph.loadGraph(newAdjacencyMatrix); // Load the new matrix to the graph
        return graph;
    }

    // Multiplication assignment operator
    Graph Graph::operator*=(int scalar)
    {
        return (*this) * scalar; // Return the graph after multiplying it by the scalar
    }

    // Division operator
    Graph Graph::operator/(int scalar)
    {
        if (scalar == 0)
        {
            throw invalid_argument("Cannot divide by zero"); // Throw an exception if the scalar is zero
        }
        if (this->getNumVertices() == 0)
        {
            return Graph(); // Return an empty graph
        }
        vector<vector<int>> GraphMat = getAdjacencyMatrix();
        Graph graph; // Create a new graph
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                GraphMat[i][j] /= scalar; // Divide each element in the matrix by the scalar
            }
        }
        graph.loadGraph(GraphMat);
        return graph;
    }

    // Division assignment operator
    Graph Graph::operator/=(int scalar)
    {
        return (*this) / scalar;
    }

    // Addition operator
    Graph Graph::operator+(Graph &graph1)
    {
        if (numVertices == 0 && graph1.getNumVertices() == 0)
        {
            return Graph(); // Return an empty graph
        }
        if (numVertices != graph1.getNumVertices())
        {
            throw invalid_argument("The number of vertices in the two graphs must be equal.");
        }
        if (numVertices == 0)
        {
            return graph1; // Return the graph g
        }
        if (graph1.getNumVertices() == 0)
        {
            return *this; // Return the current graph
        }
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph newGraph;

        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] + graph1.getAdjacencyMatrix()[i][j];
            }
        }
        graph1.loadGraph(newAdjacencyMatrix);
        return graph1;
    }

    // Addition assignment operator
    Graph Graph::operator+=(Graph &graph)
    {
        return *this + graph;
    }

    // Subtraction operator
    Graph Graph::operator-(Graph &graph1)
    {
        if (numVertices != graph1.getNumVertices())
        {
            throw invalid_argument("The number of vertices in the two graphs must be equal.");
        }
        if (numVertices == 0 && graph1.getNumVertices() == 0)
        {
            return Graph(); // Return an empty graph
        }
        if (numVertices == 0)
        {
            return -graph1; // Return the negative graph of g
        }
        if (graph1.getNumVertices() == 0)
        {
            return *this; // Return the current graph
        }
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph newGraph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] - graph1.getAdjacencyMatrix()[i][j];
            }
        }
        newGraph.loadGraph(newAdjacencyMatrix);
        return newGraph;
    }

    // Subtraction assignment operator
    Graph Graph::operator-=(Graph &graph)
    {
        return *this - graph;
    }

    // Unary minus operator
    Graph Graph::operator-()const
    {
        if (numVertices == 0)
        {
            return Graph(); // Return an empty graph
        }
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph graph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] *= -1;
            }
        }
        graph.loadGraph(newAdjacencyMatrix);
        return graph;
    }

    // Prefix increment operator
    void Graph::operator++()
    {
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                adjacencyMatrix[i][j]++;
            }
        }
    }

    // Prefix decrement operator
    void Graph::operator--()
    {
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                adjacencyMatrix[i][j]--;
            }
        }
    } // g--

    // Postfix increment operator
    void Graph::operator++(int)
    {
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                adjacencyMatrix[i][j]++;
            }
        }
    } //++g

    // Postfix decrement operator
    void Graph::operator--(int)
    {
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                adjacencyMatrix[i][j]--;
            }
        }
    } //--g

    // Equality operator
    bool Graph::operator==(Graph &graph)
    {
        if (numVertices == 0 && graph.getNumVertices() == 0)
        {
            return true; // return true if both graphs are empty
        }
        bool first = numVertices == graph.getNumVertices();
        bool last = false;
        if (first)
        {
            for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    if (adjacencyMatrix[i][j] != graph.getAdjacencyMatrix()[i][j])
                    {
                        first = false;
                        break;
                    }
                }
                if (!first)
                {
                    break;
                }
            }
        }
        last = *this <= graph && *this >= graph;
        return first || last;
    }

    // Less than operator
    bool Graph::operator<(Graph &graph)
    {
        return (Graph::isContained(graph, *this) || (this->getNumEdges() < graph.getNumEdges()) // check if this is contained in g or that have less edges
                || (numEdges == graph.getNumEdges() && numVertices < graph.getNumVertices()));  // if numofedges is equal check the number of vertices
    }

    // Greater than operator
    bool Graph::operator>(Graph &graph)
    {
        return graph < *this;
    }

    // Greater than or equal to operator
    bool Graph::operator>=(Graph &graph)
    {
        return (!(*this < graph));
    }

    // Less than or equal to operator
    bool Graph::operator<=(Graph &graph)
    {
        return (!(*this > graph));
    }

    // Not equal to operator
    bool Graph::operator!=(Graph &graph)
    {
        return !(*this == graph);
    }

    // Matrix multiplication operator
    Graph Graph::operator*(Graph &graph1)
    {

        if (numVertices != graph1.getNumVertices())
        {
            throw invalid_argument("The number of vertices in the two graphs must be equal.");
        }
        if (numVertices == 0 || graph1.getNumVertices() == 0)
        {
            return Graph(); // return the empty graph
        }
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph newGraph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                for (size_t k = 0; k < numVertices; k++)
                {
                    newAdjacencyMatrix[i][j] += (adjacencyMatrix[i][k] * graph1.getAdjacencyMatrix()[k][j]);
                }
            }
        }
        graph1.loadGraph(newAdjacencyMatrix);
        return graph1;
    }

    // Output stream operator
    ostream &operator<<(ostream &osStream, Graph &graph)
    {
        osStream << "the graph is:" << endl;
        osStream << "{";
        for (size_t i = 0; i < graph.getNumVertices(); i++)
        {
            osStream << "[";
            for (size_t j = 0; j < graph.getNumVertices(); j++)
            {
                osStream << graph.getAdjacencyMatrix()[i][j] << " ";
            }
            osStream << "]";
            osStream << endl;
        }
        osStream << "}";
        return osStream;
    }

    // Check if graph1 is contained in graph2
    bool Graph::isContained(Graph &graph1, Graph &graph2)
    {
        if (graph1.getNumVertices() > graph2.getNumVertices())
        {
            return false;
        }
        for (size_t i = 0; i < graph1.getNumVertices(); i++)
        {
            for (size_t j = 0; j < graph1.getNumVertices(); j++)
            {
                if (graph2.getAdjacencyMatrix()[i][j] != 0 && graph1.getAdjacencyMatrix()[i][j] == 0 // if the bigger graph has an edge and the smaller graph doesn't
                    || graph1.getAdjacencyMatrix()[i][j] != 0 && graph2.getAdjacencyMatrix()[i][j] == 0)
                {                 // if the smaller graph has an edge and the bigger graph doesn't
                    return false; // the graph is not contained because it is missing an edge
                }
            }
        }
        return true;
    }

} // namespace ariel
