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

#include "Edge.hpp"

#include <map>
#include <string>

/* Defined solely for course requirement. */
Edge::Edge(){
    // No logical implementation required
}

/* Redundant, but satisfies course requirement.
   Uses overloaded clear() to invoke STL map.clear(). */
Edge::~Edge(){
    clear();
}

/* Because STL map.insert() prevents the entry of elements with
   duplicate keys, this function safely ignores dupicate keys.  */
void Edge::insert(const std::string& vertex, unsigned long distance){
    neighbors.insert({vertex, distance});
    return;
}

/* Allows caller to specify a source-vertex and retrieve all of its
   neighbor/distance pairs. Returns an Edge object reference.       */
const std::map<std::string, unsigned long>& Edge::get_neighbors() const{
    return neighbors;
}

/* Although STL map.size() may return number > int-range, main() will
   restrict the number of neighbors to stay within int bounds.        */
int Edge::get_size() const{
    return neighbors.size();
}

/* Uses STL map.erase() to remove a target neighbor/distance pair
   once caller identifies it.                                     */
void Edge::remove_neighbor(const std::string& target){
    neighbors.erase(target);
}

/* This function allows indirect call to STL map.clear(),
   encapsulating logic by abstraction.                    */
void Edge::clear(){
    neighbors.clear();
    return;

}
