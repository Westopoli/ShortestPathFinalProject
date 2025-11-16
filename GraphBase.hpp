/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This header file declares a base class for custom graph
   class. Each graph element consists of (source-vertex, map
   of eighbor-vertices/distances from source-vertex). The
   pair above is encapsulated by (std::string, class Edge)
   and represents an adjacency list for immutable reference
   in the algorithm.
   
   Class Edge provides further
   encapsulation of (neighbor-vertices, distances from
   source-vertex).
   
   The adjacency list is implemented as a map from
   source-vertex to a map of neighbor-vertices and distances.
   The adjacency list supplies the necessary data and
   functions to implement Dijkstra's algorithm.
   
   Details on the algorithm's implementation are provided
   below in shortestPath(), but the design operates by
   working from the start-vertex, examining the path to each
   neighbor, and building a path toward the end-vertex.
   With the help of class PQueue, only the current shortest
   known path is evaluated, until the end-vertex is reached.
   
   By the end of the algorithm, both the shortest distance
   and the path to obtain the shortest distance are made
   available to the caller.                                  */

#ifndef GRAPHBASE_HPP
#define GRAPHBASE_HPP

#include <string>
#include <vector>

class GraphBase{
public:
    GraphBase() = default;  // Not necessary, but fulfills course requirements. No source file, so set to default
    virtual ~GraphBase() = default; // Prevents call to incorrect destructor from derived class objects. No source file, so set to default
    virtual void addVertex(std::string label) = 0; // Checks for duplicates before adding a vertex
    virtual void removeVertex(std::string label) = 0; // Removes all source and neighbor vertex instances
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight) = 0; // Observes project guidelines, then adds edge 
    virtual void removeEdge(std::string label1, std::string label2) = 0; // Removes the undirected edge between two vertices
    virtual unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) = 0; // Dijkstra's algorithm
};

#endif
