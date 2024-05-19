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
        isdirected = false;
        adjacencyMatrix = vector<vector<int>>(10, vector<int>(10, 0)); // Initialize the matrix with 10x10 zeros
    }

    void Graph::loadGraph(vector<vector<int>> graph)
    {
        // Check if the graph is a square matrix.
        if (graph.size() != graph[0].size())
        {
            cout << graph.size() << " " << graph[0].size() << endl;
            throw invalid_argument("The graph is not a square matrix");
        }
        if (graph.empty())
        {
            numVertices = 0;
            numEdges = 0;
            adjacencyMatrix = {}; // Already empty vector
            isdirected = false;
            return;
        }

        numVertices = graph.size();// Load the number of vertices to the graph
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
                if (adjacencyMatrix[i][i] != adjacencyMatrix[i][i] && adjacencyMatrix[i][i] != 0 && adjacencyMatrix[i][i] != 0)
                {
                    throw invalid_argument("multy-graph is not allowed");
                }
                if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[j][i] == 0 || adjacencyMatrix[j][i] != 0 && adjacencyMatrix[i][j] == 0)
                {
                    isdirected = true;
                }
                adjacencyMatrix[i][i]=0;// remove self loops caused by matrix initialization
            }
        }
        numEdges = (int)numofedges / 2;
        numVertices = (int)graph.size();
    }
    vector<vector<int>> Graph::getAdjacencyMatrix()
    {
        return adjacencyMatrix;
    }
    string Graph::printGraph()
    {
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
    Graph Graph::getTranspose()
    {
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph graph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[j][i];
            }
        }
        graph.loadGraph(newAdjacencyMatrix);
        return graph;
    }

    // Unary + operator
    Graph Graph::operator+()
    {
        return *this; // return a reference to the current graph
    }

    // Multiplication operator
    Graph Graph::operator*(int scalar)
    {
        vector<vector<int>> GraphMat = getAdjacencyMatrix();
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph graph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = GraphMat[i][j] * scalar;
            }
        }
        graph.loadGraph(newAdjacencyMatrix);
        return graph;
    }

    Graph Graph::operator*=(int scalar)
    {
        return (*this) * scalar;
    }

    Graph Graph::operator/(int scalar)
    {
        vector<vector<int>> GraphMat = getAdjacencyMatrix();
        Graph graph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                getAdjacencyMatrix()[i][j] /= scalar;
            }
        }
        graph.loadGraph(GraphMat);
        return graph;
    }
    Graph Graph::operator/=(int scalar)
    {
        return (*this) / scalar;
    }
    // return a the sum of the current graph and the graph g
    Graph Graph::operator+(Graph &g)
    {
        if (numVertices != g.getNumVertices())
        {
            throw invalid_argument("The number of vertices in the two graphs must be equal.");
        }
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph graph;

        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] + g.getAdjacencyMatrix()[i][j];
            }
        }
        graph.loadGraph(newAdjacencyMatrix);
        return graph;
    }

    Graph Graph::operator+=(Graph &g)
    {
        return *this + g;
    }

    Graph Graph::operator-(Graph &g)
    {
        if (numVertices != g.getNumVertices())
        {
            throw invalid_argument("The number of vertices in the two graphs must be equal.");
        }
        vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
        Graph graph;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j] - g.getAdjacencyMatrix()[i][j];
            }
        }
        graph.loadGraph(newAdjacencyMatrix);
        return graph;
    }

    Graph Graph::operator-=(Graph &g)
    {
        return *this - g;
    }

    Graph Graph::operator-()
    {
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

    void Graph::operator++()
    {
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                adjacencyMatrix[i][j]++;
            }
        }
    } // g++
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

    bool Graph::operator==(Graph &g)
    {
        if (!(*this > g && *this < g))
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
        return true;
    }

    bool Graph::operator<(Graph &g)
    {
        if (isContained(g, *this)) // check if this is contained in g
        {
            return true;
        }
        if (this->getNumEdges() < g.getNumEdges())
        {
            return true;
        }
        else if (numEdges == g.getNumEdges())
        {
            if (numVertices < g.getNumVertices())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    bool Graph::operator>(Graph &g)
    {
        return g < *this;
    }

    bool Graph::operator>=(Graph &g)
    {
        return (!(*this < g));
    }

    bool Graph::operator<=(Graph &g)
    {
        return (!(*this > g));
    }

    bool Graph::operator!=(Graph &g)
    {
        return !(*this == g);
    }

    Graph Graph::operator*(Graph &g)
    {
        if (numVertices != g.getNumVertices())
        {
            throw invalid_argument("The number of vertices in the two graphs must be equal.");
        }
        else
        {
            vector<vector<int>> newAdjacencyMatrix = vector<vector<int>>((size_t)numVertices, vector<int>((size_t)numVertices, 0));
            Graph graph;
            for (size_t i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    for (size_t k = 0; k < numVertices; k++)
                    {
                        newAdjacencyMatrix[i][j] += (adjacencyMatrix[i][k] * g.getAdjacencyMatrix()[k][j]);
                    }
                }
            }
            graph.loadGraph(newAdjacencyMatrix);
            return graph;
        }
    }

    ostream &operator<<(ostream &os, Graph &g)
    {
        os << "the graph is:" << endl;
        os << "{";
        for (size_t i = 0; i < g.getNumVertices(); i++)
        {
            os << "[";
            for (size_t j = 0; j < g.getNumVertices(); j++)
            {
                os << g.getAdjacencyMatrix()[i][j] << " ";
            }
            os << "]";
            os << endl;
        }
        os << "}";
        return os;
    }
    // check if g1 is contained in g2
    bool Graph::isContained(Graph &g1, Graph &g2)
    {
        if (g1.getNumVertices() > g2.getNumVertices())
        {
            return false;
        }
        for (size_t i = 0; i < g1.getNumVertices(); i++)
        {
            for (size_t j = 0; j < g1.getNumVertices(); j++)
            {
                if (g2.getAdjacencyMatrix()[i][j] != 0 && g1.getAdjacencyMatrix()[i][j] == 0) // if the bigger graph has a edge and the smaller graph deosnt
                {
                    return false; // the graph is not contained cause he is missing an edge
                }
            }
        }
        return true;
    }

} // namespace ariel
