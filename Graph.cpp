/*           Jonathan D Rivera-Rosado U80549443
   **********************************************************
               Project 4 Dijkstra's Algorithm
   **********************************************************
   This source file defines a custom graph class. Each
   graph element consists of (source-vertex, map of
   neighbor-vertices/distances from source-vertex).
   The pair above is encapsulated by
   (std::string, class Edge) and represents an adjacency
   list for immutable reference in the algorithm.
   
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

#include "Graph.hpp"
#include "PQueue.hpp"

#include <string>
#include <stdexcept>
#include <map>
#include <algorithm>

/* Defined solely for course requirement. */
Graph::Graph(){
    // No logical implementation required
}

/* Uses overloaded clear() to invoke STL map.clear(),
   freeing all memory allocated for map in Graph as well
   as Graph elements.                                    */
Graph::~Graph(){
    clear();
}

/* Function adds a new vertex after checking for duplicates. */
void Graph::addVertex(const std::string& label){
    if(adjacencyList.find(label) != adjacencyList.end()){
        throw std::runtime_error("[ERROR] Specified vertex has already been added. Unable to complete request.");
    }
    adjacencyList.insert({label, Edge()});  // Insert a new (source vector/neighbor map pair), but map is empty

    return;
}

/* Function removes any instances of the target
   vertex. This includes traversing the list of
   neighboring vertices as well as the adjacency list. */
void Graph::removeVertex(std::string label){
    if(adjacencyList.find(label) == adjacencyList.end()){
        throw std::runtime_error("[ERROR] Specified vertex not found in adjacency list. Unable to complete request.");
    }
    for(auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it){ // Remove from list of neighboring vertices...
        it->second.remove_neighbor(label);
    }
    adjacencyList.erase(label); // ...and from list of source vertices

    return;    
}

/* Function adds an edge by inserting a new label/weight pair to a source vertex's list
   of neighbors. This function confirms [a] no self-loop edges are formed by a single
   vertex, [b] both the source vertex and destination vertex exist in the adjacency
   list before adding neighbors, and [c] the intended edge does not already exist.
   Once [a]-[c] are confirmed, an edge is declared in undirected fashion.               */
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    if(label1 == label2){   // [a] No self-loops
        throw std::runtime_error("[ERROR] Program does not support self-loop condition. Unable to complete request.");
    }
    if(adjacencyList.find(label1) == adjacencyList.end() || adjacencyList.find(label2) == adjacencyList.end()){ // [b] Both are source vertices
        throw std::runtime_error("[ERROR] One or more specified vertex does not exist. Unable to complete request.");
    }
    if(adjacencyList[label1].get_neighbors().find(label2) != adjacencyList[label1].get_neighbors().end()){ // [c] No duplicate edges
        throw std::runtime_error("[ERROR] Specified edge already exists. Unable to complete request.");
    }

    adjacencyList[label1].insert(label2, weight);   // Undirected edges...
    adjacencyList[label2].insert(label1, weight);   // ...are now formed

    return;
}

/* Confirms that [a] both the source and destination vertices exist in the
   adjacency list, and [b] an edge exists between them. After confirming
   [a] and [b], removes the corresponding (neighbor, distance) elements from
   both vertices’ Edge objects, maintaining an undirected graph.
   NOTE: Function is not called in this Dijkstra's algorithm implementation. */
void Graph::removeEdge(std::string label1, std::string label2){ // Not called in this Dijkstra algorithm implementation however
    // [a] Confirm that both vertices exist
    if(adjacencyList.find(label1) == adjacencyList.end() || adjacencyList.find(label2) == adjacencyList.end()){
        throw std::runtime_error("[ERROR] One or more specified vertex does not exist. Unable to complete request.");
    }
    // [b] Confirm that there is an edge between both vertices
    const std::map<std::string, unsigned long>& locate1 = adjacencyList[label1].get_neighbors();
    if(locate1.find(label2) == locate1.end()){
        throw std::runtime_error("[ERROR] No edge exists between specified vertices. Unable to complete request.");
    }
    // If [a] and [b] are confirmed, remove applicable neighbor of both vertices
    else{
        adjacencyList[label1].remove_neighbor(label2);
        adjacencyList[label2].remove_neighbor(label1);
    }

    return;
}

/* This function implements Dijkstra's algorithm. The algorithm works backwards, tracking the distance from each
   vertex back to the startLabel. While doing so, indirect paths between vertices which are shorter than those stored
   in adjacencyList may be disovered. If so, the shorter distance will be stored in the updateable map shortestDistance.
   As shortestDistance maintains the shortest path from currLabel to startLabel, the algorithm looks to confirm that
   currLabel == endLabel. With this confirmation, the shortest path from start to end is identified.                     */
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    // [a]-[b]
    // Ensure that the adjacency list contains the correct vertices to process
    if(adjacencyList.find(startLabel) == adjacencyList.end() || adjacencyList.find(endLabel) == adjacencyList.end()){
        throw std::runtime_error("[ERROR] One or more specified vertex does not exist. Unable to complete request.");
    }

    std::map<std::string, std::string> prevVertex;        // Tracks tentative edge path
    std::map<std::string, unsigned long> shortestDistance;  // Tracks tentative path distance
    for(auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it){
        shortestDistance[it->first] = ULONG_MAX;    // Assume that the distance from most vertices back to startLabel is infinite...
    }
    shortestDistance[startLabel] = 0;   // ...but we know the distance from startLabel to startLabel is 0

    /* At this point, startLabel provides the only confirmed data.
       [a] Starting from startLabel, check which neighbor offers the shortest path back to startLabel.
       [b] If that path is less than the current shortest distance known, update what is known.
       [c] Insert it in pQueue so that it can be sorted.
       [d] Whichever path-back-to-startLabel is shortest will then be processed next with top().
       [e] Once we can confirm that top() == endLabel, we can also confirm that we've found the shortest distance back to startLabel */

    PQueue pQueue;
    Vertex startVertex(shortestDistance[startLabel], startLabel);   // [a]/[d] Convert data to a Vertex object suitable for pQueue...
    pQueue.push(startVertex);                                       // ...and push it to pQueue
    while(!pQueue.empty()){     // Safe pQueue-state guard
        unsigned long currDistance = pQueue.top().get_distance();   // Obtain distance...
        std::string currLabel = pQueue.top().get_label();           // ...and label from first Vertex node in queue
        if(currLabel == endLabel){  // ...[e] If shortest path from startLabel to endLabel is found
            reconstruct(path, prevVertex, startLabel, endLabel);
            return currDistance;    // ...return the value
        }
        pQueue.pop();   // Node whose neighbors will be explored is no longer needed

        // Now we refer back to the immutable adjacency list
        const std::map<std::string, unsigned long>& neighborMap = adjacencyList[currLabel].get_neighbors(); // [b] Get the current Vertex node's neighbors
        for(auto it = neighborMap.begin(); it != neighborMap.end(); ++it){  // Iterate through the neighbors
            unsigned long testD = it->second + currDistance;            // The neighbor-current distance we plan to test...
            unsigned long shortestD = shortestDistance[it->first]; // ...against neighbor-startLabel distance we are unsure of
            if(testD < shortestD){                                     // If we found a shorter distance
                prevVertex[it->first] = currLabel;
                shortestDistance[it->first] = testD;    // ...then update what we know
                Vertex updatedVertex(shortestDistance[it->first], it->first);   // ...format new data for pQueue
                pQueue.push(updatedVertex); // [c] ...and push to pQueue for sorting. Whichever path-back-to-startLabel is shortest is processed next
            }
        }
    }
    return ULONG_MAX;   // Should the algorithm fail to locate any path from startLabel to endLabel

}

void Graph::reconstruct(std::vector<std::string> &fnlPath, const std::map<std::string, std::string>& fnlEdges, const std::string& start, const std::string& end){
    // The follow three cases avoid unnecessary logic
    if(start.empty() || end.empty()){
        throw std::runtime_error("[ERROR] Start and or edge vertex contains invalid data. Unable to complete request");
    }    
    if(fnlEdges.find(end) == fnlEdges.end()){
        throw std::runtime_error("[ERROR] End vertex does not exist. Unable to complete request.");
    }
    if(start == end){   // For one-vertex circular path
        fnlPath.push_back(start);
        return;
    }
    
    fnlPath.push_back(end); // Load end vertex first
    std::string curr = fnlEdges[end];
    while(curr != start){
        if(fnlEdges.find(curr) == fnlEdges.end()){  // The last case to inspect is a broken path from potentially corrupted data
            throw std::runtime_error("[ERROR] Break in vertex path detected. Unable to complete request.");
        }
        fnlPath.push_back(curr);    // Load current vertex...
        curr = fnlEdges[curr];      // ...and iterate to 
    }
    fnlPath.push_back(start);                     // After iterations are complete, load start vertex...
    std::reverse(fnlPath.begin(), fnlPath.end()); // ...and reverse the order
    
    return;
}

/* This function allows indirect call to STL map.clear(). The function
   clears all neighbor maps before clearing the adjacency list,
   releasing memory held by the maps before returning to caller.       */
void Graph::clear(){
    for(auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it){
        it->second.clear(); // Clear secondary Vertex.neighbors maps first...
    }
    adjacencyList.clear();  // ...then clear high-level map container

    return;
}