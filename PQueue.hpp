/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This header file declares a min-priority queue class which
   uses heap principles to sort key-value (distance-vertex)
   pairs in ascending order of key. Each PQueue element
   (pair) is a Vertex object. The intended use of
   PQueue is to maintain the current shortest distance-to-
   target at the top of the queue. Using this top element
   allows the algorithm to examine any available neighbors
   of the most recently viewed vertex and pursue the next
   step in the shortest path to the target. Once Dijkstra's
   algorithm is complete, the top PQueue element should
   contain the shortest total distance to the target vertex.  */

#ifndef PQUEUE_HPP
#define PQUEUE_HPP

#include "Vertex.hpp"

#include <vector>

class PQueue {
public:
    PQueue();   // Default constructor included to fulfill course requirements
    ~PQueue();  // Default destructor included to fulfill course requirements. Calls clear()
    void push(const Vertex& newNode);  // Inserts new element and calls bubble_up()
    void pop(); // Removes first element, maintaining heap property with STL vector functions. Calls bubble_down()
    const Vertex& top() const;  // Returns first element in queue
    int get_size() const;   // Not needed for the bounds of this assignment, but added for light modularity
    bool empty() const; // Helper function, used in multiple member functions
    void clear();  // Helper function, uses STL vector clear

protected:
    int find_parent(int indexChild);         // Helper function, encapsulates redundant logic
    int find_left(int indexParent);          // Helper function, encapsulates redundant logic
    int find_right(int indexParent);         // Helper function, encapsulates redundant logic
    void bubble_up(int indexChild);     // Helper function, swaps a child with its parent as needed
    void bubble_down(int indexParent);  // Helper function, swaps a parent with its child as needed
    void swap(int i, int j);

private:
    std::vector<Vertex> heapQueue;  // Location of zero-indexed min-priority queue
};

#endif


