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

#include "Vertex.hpp"

#include <string>

/* Defined solely for course requirement. */
Vertex::Vertex(){
   // No logical implementation required
}

/* Custom constructor. */
Vertex::Vertex(unsigned long dist, const std::string& lbl){
   set_distance(dist);
   set_label(lbl);
}

/* Defined solely for course requirement. */
Vertex::~Vertex(){
   // No logical implementation required
}

/* Operator overload compares two Vertex objects by distance. */
bool Vertex::operator<(const Vertex& other) const{
         return (distance < other.distance);
}

/* Operator overload compares two Vertex objects by distance. */
bool Vertex::operator>(const Vertex& other) const{
   return (distance > other.distance);
}

void Vertex::set_distance(unsigned long dist){
   distance = dist;
}

void Vertex::set_label(const std::string& lbl){
   this->label = lbl;
}

/* Unused function in this assignment, but allows modularity. */
unsigned long Vertex::get_distance() const{
   return distance;
}

/* Unused function in this assignment, but allows modularity. */
std::string Vertex::get_label() const{
   return label;
}