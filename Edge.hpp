/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This header file declares a class which uses STL map to
   store a collection of destination/distance (key/value)
   pairs. The intent is that for every Edge object
   instantiated, a relationship will exist between that
   object's identifier and each of its neighbor key/value
   pairs. Effectively, class Edge supplies a list of all
   available neighbor vertices for any specified vertex, as
   well as the distance between the source-vertex and a
   destination-vertex. For example: map A = {(B, 5), (C, 7)}
   implies that source-vertex A has neighbors B and C, whose
   edges are a length of 5units and 7units respectively.      */

#ifndef EDGE_HPP
#define EDGE_HPP

#include <map>
#include <string>

class Edge{
public:
    Edge();   // Default constructor included to fulfill course requirements
    ~Edge();  // Default destructor included to fulfill course requirements. Calls clear()
    void insert(const std::string& vertex, unsigned long distance);       // Adds one neighbor/distance pair at a time
    const std::map<std::string, unsigned long>& get_neighbors() const;    // Returns address of a specific vertex's neighbors (Edge object reference)
    int get_size() const;   // Returns the number of neighbors
    void remove_neighbor(const std::string& target);    // Called by wrapper class Graph
    void clear();   // Clears map of all elements (neighbors)

private:
    std::map<std::string, unsigned long> neighbors;    // (key/value) = (neighbor vertex/distance from source)
};


#endif


