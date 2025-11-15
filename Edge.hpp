/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This source file defines a class which uses STL map to
   store a collection of destination/distance (key/value)
   pairs. The intent is that for every Edge object
   instantiated, a relationship will exist between that
   object's identifier and each of its neighbor key/value
   pairs. Effectively, a list of all available neighbor
   vertices for any specified vertex will be supplied, as well
   as the distance between the source-vertex and destination-
   vertex. For example: map A = {(B, 5), (C, 7)} implies that
   source-vertex A has neighbors B and C, whose edges are a
   length of 5u and 7u respectively.                           */

#ifndef EDGE_HPP
#define EDGE_HPP

#include <map>
#include <string>

class Edge{
public:
    Edge();   // Default constructor included to fulfill course requirements
    ~Edge();  // Default destructor included to fulfill course requirements. Calls clear()
    void insert(const std::string& vertex, unsigned long distance);       // Utilizes STL map.insert() to add neighbors. Ignores duplicates
    const std::map<std::string, unsigned long>& get_neighbors() const;    // Returns address of a specific source-vertex's mapped neighbors
    int get_size() const;   // Utilizes STL map.size() to return the number of neighbors
    void remove_neighbor(const std::string& target);    // Called by wrapper class Graph
    void clear();   // Clears map of all elements/neighbors

private:
    std::map<std::string, unsigned long> neighbors;    // (key/value) = (neighbor vertex/distance from source)
};

#endif