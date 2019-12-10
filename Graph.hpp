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
#include <climits>

template <typename Object>
struct Vertex;

template <typename Object>
struct Edge;

template <typename Object>
struct Edge {

    Edge(Vertex<Object>* dest, float weight) : dest_(dest), weight_(weight) {}
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

    int FindIndexOfEdge(const Object& val_to_search_for) {

        for(int i = 0; i < edges_.size(); ++i) {
            if(edges_[i].dest_->val_ == val_to_search_for) {
                return i;
            }
        }

        return INT_MIN;
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

    /*
    ** Finds weight of some directed edge between a source and destination value.
    ** @param: source is some vertex that is in the graph.
    ** @param: destination is some other vertex that is in the graph.
    ** @return: the weight of the directed edge between source and destination. Returns INT_MIN if no edge is found.
    */
    float FindWeightOfEdge(const Object& source, const Object& destination);

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

template <typename Object>
float Graph<Object>::FindWeightOfEdge(const Object& source, const Object& destination) {

    Vertex<Object>* new_vertex = adj_list_[source];
    int index_of_edge = new_vertex->FindIndexOfEdge(destination);
    float weight = INT_MIN;

    if(index_of_edge != INT_MIN) {
        weight = new_vertex->edges_[index_of_edge].weight_;
    }
    
    return weight;
}

template<typename Object>
void Graph<Object>::PrintAdjList() const {

    for(auto itr = adj_list_.begin(); itr != adj_list_.end(); ++itr) {
        std::cout << itr->first << " : "; 
        itr->second->PrintEdges();
    }
}