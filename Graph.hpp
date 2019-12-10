/*
** Author: Naveed Naqi
** Date: 12/10/2019
** Description: This file is the implementation of a graph. The graph is represented as an adjancey list.
** All values are in the graph are unique nodes.
** We are using internal structs Vertex and Edge to aid in the internal implementation.
** The adjacency list is being implemented with a hashtable that matches Objects to Verticies. Each Vertex has a vector of Edges.
*/

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>

template <typename Object>
struct Vertex;

template <typename Object>
struct Edge;

template <typename Object>
struct Edge {

    Edge( Vertex<Object>* dest, float weight) : dest_(dest), weight_(weight) {}
    Vertex<Object>* dest_;
    float weight_;

    void Print() const {
        std::cout << "-> " << dest_->val_ << "(" << weight_ << ") \t";
    }
};

template <typename Object> 
struct Vertex {
    Vertex(const Object& val) : val_(val), indegree_(0) {}

    Object val_;
    std::size_t indegree_;
    std::vector<Edge<Object>> edges_;

    void PrintEdges() const {

        for(auto edge : edges_) {
            edge.Print();
        }

        std::cout << "\n";
    }
};

template <typename Object> 
class Graph {

public: 

    //Constructor for the Graph, that reserves a size for the adjacency list from the specified size.
    Graph(std::size_t size) {
        adj_list_.reserve(size);
    }

    /*
    ** Adds an edge between two verticies, with the assigned weight. The edge is directed from the source to the destination. 
    ** Assumes the verticies are already in the graph.
    ** @param: source is some Object that is already a vertex in the graph
    ** @param: destination is some Object that is already a vertex in the graph
    ** @param: weight is is some float that is the weight between the two verticies.
    */
    void AddEdge(const Object& source, const Object& destination, float weight);

    /*
    ** Adds a Vertex to the graph.
    ** Assumes the vertex is not already in the graph, otherwise it will overwrite the adjacency list.
    ** @param: new_elem is some Object that needs to be mapped into the adjacency list.
    */
    void AddVertex(const Object& new_elem);
    
    /*
    ** Adds a Vertex to the graph.
    ** @param: val_to_search_for is some Object that may or may not be in the adjacency list.
    ** @return: The pointer to the Vertex that is being searched for.
    */
    Vertex<Object>* FindVertex(const Object& val_to_search_for);

    void PrintAdjList() const;

private:

    std::unordered_map<Object, Vertex<Object>*> adj_list_;
};

template <typename Object> 
void Graph<Object>::AddVertex(const Object& new_elem) {

    Vertex<Object>* new_vertex = new Vertex<int>(new_elem);
    adj_list_[new_elem] = new_vertex;
}

template <typename Object> 
void Graph<Object>::AddEdge(const Object& source, const Object& destination, float weight) {


    Vertex<Object>* source_vertex = adj_list_[source];
    Vertex<Object>* destination_vertex = adj_list_[destination];
    Edge<Object> new_edge(destination_vertex, weight);

    source_vertex->edges_.push_back(new_edge);
}

template <typename Object>
Vertex<Object>* Graph<Object>::FindVertex(const Object& val_to_search_for) {

    return adj_list_.find(val_to_search_for) == adj_list_.end() ? nullptr : adj_list_[val_to_search_for];
}

template<typename Object>
void Graph<Object>::PrintAdjList() const {

    for(auto itr = adj_list_.begin(); itr != adj_list_.end(); ++itr) {
        std::cout << itr->first << " : "; 
        itr->second->PrintEdges();
    }
}