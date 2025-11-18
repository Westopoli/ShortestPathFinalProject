/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This source file defines a min-priority queue class which
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

#include "PQueue.hpp"

#include <vector>
#include <stdexcept>

/* Defined solely for course requirement. */
PQueue::PQueue(){
    // No logical implementation required
}

/* Redundant, but satisfies course requirement.
   Abstracts STL vector clear().                */
PQueue::~PQueue(){
    heapQueue.clear();
}

/* Maintains heap property by first inserting a
   new node at the end of the vector. Afterwards,
   the new node is bubbled up as needed.          */
void PQueue::push(const Vertex& newNode){
    heapQueue.push_back(newNode);
    int indexLast = heapQueue.size() - 1;
    bubble_up(indexLast);   // Variable indexLast used for explicit logic

    return;
}

/* Maintains heap property by first copying
   last node to the top of the queue. Last
   node is then popped, and first node is
   bubbled down as needed.                  */
void PQueue::pop(){
    if(heapQueue.empty()){  // Data security check
        throw std::runtime_error("[ERROR]: Queue is empty. Unable to complete request.");
    }
    heapQueue[0] = heapQueue.back();    // If only one element was enqueued...
    heapQueue.pop_back();               // ...this is all that is needed
    if(heapQueue.empty()){
        return;
    }
    else{
        int indexFirst = 0;             // If still one or more elements remain...
        bubble_down(indexFirst);        // ...then bubble the new top element down
    }

    return;
}

/* Read-only, so constant. */
const Vertex& PQueue::top() const{
    if(heapQueue.empty()){  // Data security check
        throw std::runtime_error("[ERROR]: Queue is empty. Unable to complete request.");
    }

    return heapQueue[0];
}

/* Read-only, so constant. */
int PQueue::get_size() const{
    return heapQueue.size();
}

/* Read-only, so constant. */
bool PQueue::empty() const{
    return heapQueue.empty();
}

/* Calls STL vector function clear() to deallocate priority queue.
   Although STL vector.size() may exceed int range, main() will restrict
   the number of neighbors to stay within int bounds.                 */
void PQueue::clear(){
    heapQueue.clear();

    return;
}

/* Zero-indexed vector logic for locating parent. */
int PQueue::find_parent(int child){
    return (child - 1) / 2;
}

/* Zero-indexed vector logic for locating left child. */
int PQueue::find_left(int parent){
    return (parent * 2) + 1;
}

/* Zero-indexed vector logic for locating right child. */
int PQueue::find_right(int parent){
    return (parent * 2) + 2;
}

/* Helpers used to condense logic. Function
   examines last node and moves it higher
   in the priority queue as needed. Utilizes
   Vertex::operator>() for comparisons.      */
void PQueue::bubble_up(int child){
    int parent = find_parent(child);
    while(child != 0 && parent >= 0 && heapQueue[parent] > heapQueue[child]){  // Use custom operator>() from class Vertex
        swap(child, parent);
        child = parent;
        parent = find_parent(child);
    }
    
    return;
}

/* Helpers used to condense logic. Recursive
   function examines first node and moves it
   lower in the priority queue as needed.
   Utilizes Vertex::operator<() for comparisons. */
void PQueue::bubble_down(int parent){
    int childL = find_left(parent);
    int childR = find_right(parent);
    int smallest = parent;

    if(childL < heapQueue.size()){   // Safely compare left child
        if(heapQueue[childL] < heapQueue[smallest]){     // Use custom operator<() from class Vertex
            smallest = childL;       // Update index of smallest key if needed
        }
    }

    if(childR < heapQueue.size()){  // Safely compare right child
        if(heapQueue[childR] < heapQueue[smallest]){    // Use custom operator<() from class Vertex
            smallest = childR;      // Update index of smallest key if needed
        }
    }

    if(smallest != parent){        // If the smallest key isn't the parent...
        swap(smallest, parent);    // ...swap the parent with the smallest
        bubble_down(smallest);          // ...and see if bubble down is needed again
    }

    return;
}

/* Swaps two nodes in the vector-base heap. */
void PQueue::swap(int i, int j){
    Vertex temp = heapQueue[i];
    heapQueue[i] = heapQueue[j];
    heapQueue[j] = temp;

    return;
}

