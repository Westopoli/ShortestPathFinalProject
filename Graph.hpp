/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This header file declares a custom graph class. Each
   graph element consists of (source-vertex, map of
   neighbor-vertices/distances from source-vertex).
   The pair above is encapsulated by
   (std::string, class Edge) and represents an adjacency
   list for immutable reference in the algorithm.
   
   Class Edge provides further
   encapsulation of (neighbor-vertices, distances from
   source-vertex).
   
   The adjacency list is implemented in a map-of-maps
   manner because it allows for two
   benefits. With this implementation of Dijkstra's 
   algorithm, enforcement of "no duplicates" is made simpler
   by STL map functions. Also, because the look-up time for a
   map element is less than that of a vector, a map is the
   preferred sub-ADT for this algorithm.
      
   Details on the algorithm's implementation are provided
   below in shortestPath(), but the design operates by
   working from the start-vertex, examining the path to each
   neighbor, and building a path toward the end-vertex.
   With the help of class PQueue, only the current shortest
   known path is evaluated, until the end-vertex is reached.
   
   By the end of the algorithm, both the shortest distance
   and the path to obtain the shortest distance are made
   available to the caller.                                  */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

#include <string>
#include <map>

class Graph : public GraphBase{
public:
    Graph(); // Default constructor included to fulfill course requirements
    ~Graph(); // Default destructor included to fulfill course requirements. Calls clear()
    void addVertex(const std::string& label); // Checks for duplicates before adding a vertex
    void removeVertex(std::string& label); // Removes all instances of a vertex, whether it is a source or neighbor vertex
    void addEdge(std::string label1, std::string label2, unsigned long weight); // Observes project guidelines, then adds and undirected edge 
    void removeEdge(std::string label1, std::string label2); // Removes an undirected edge. Not called in this Dijkstra algorithm implementation, however
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path); // Dijkstra's algorithm, calls reconstruct()
    void clear(); // Clears map of all elements (all instances of all vertices)

protected:  // Helper function, rebuilds shortest vector path from start to end
    void reconstruct(std::vector<std::string&> &fnlPath, const std::map<std::string, std::string>& fnlEdges, const std::string& start, const std::string& end); 

private:
    std::map<std::string, Edge> adjacencyList;
};


#endif

