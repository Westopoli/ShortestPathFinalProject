/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This source file defines a class of (key/value) pairs
   which represent (distance/vertex label). The pair will
   hold the current shortest distance from startLabel in the
   implementation shortestPath() in class Graph. The Vertex
   class is to be used with the min-heap priority queue
   implemented by class PQueue which will always keep the
   shortest distance from startLabel at the top of the queue.
   Also provided are overloads for operators "<" and ">"
   which simplify sort logic in PQueue.                       */

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>

class Vertex{
public:
   Vertex();    // Default constructor included to fulfill course requirements
   Vertex(unsigned long dist, const std::string& dest); // Custom constructor, calls set_distance() and set_label()
   ~Vertex();   // Default destructor included to fulfill course requirements.
   bool operator<(const Vertex& other) const; // Operator overload
   bool operator>(const Vertex& other) const; // Operator overload
   unsigned long get_distance() const;     // Although not utilized in this assignment, provided for modularity
   std::string get_label() const;  // Although not utilized in this assignment, provided for modularity

protected:
   void set_distance(unsigned long dist);   // Serves as helper for custom Vertex()
   void set_label(const std::string& lbl);  // Serves as helper for custom Vertex()

private:
   unsigned long distance = 0;     // Key
   std::string label = "";   // Value      
};


#endif
