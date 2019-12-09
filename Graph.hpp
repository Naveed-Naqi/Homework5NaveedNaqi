#include <iostream>
#include <forward_list>
#include <vector>

template <typename Object> 
struct Vertex {

    Vertex(Object val, int weight = -1, Vertex* next = nullptr) : val_(val), weight_(weight), next_(next) {}

    Vertex* next_;
    Object val_;
    int weight_;
};

template <typename Object> 
class Graph {

public: 

    void AddEdge(const Object& source, const Object& destination, int weight);
    void AddVertex(const Object& new_elem);

    void PrintAdjList() const;

private:

    void TraverseList(Vertex<Object>* curr_vertex) const;
    std::vector<Vertex<Object>*> adj_list_;
};

template <typename Object> 
void Graph<Object>::TraverseList(Vertex<Object>* curr_vertex) const {

    while(curr_vertex != nullptr) {
        std::cout << "Value: " << curr_vertex->val_ << "\n";
        std::cout << "Cost: " << curr_vertex->weight_ << "\n";
        curr_vertex = curr_vertex->next_;
    }
}

template <typename Object> 
void Graph<Object>::AddVertex(const Object& new_elem) {

    Vertex<Object>* new_vertex = new Vertex<int>(new_elem);
    adj_list_.push_back(new_vertex);
}

template <typename Object> 
void Graph<Object>::AddEdge(const Object& source, const Object& destination, int weight) {

    for(auto curr_vertex : adj_list_) {

        if(curr_vertex->val_ == source) {
            
            Vertex<Object>* new_vertex = new Vertex<Object> (destination, weight);
            Vertex<Object>* temp = curr_vertex->next_;

            curr_vertex->next_ = new_vertex;
            new_vertex->next_ = temp;
            return;
        }
    }
}

template<typename Object>
void Graph<Object>::PrintAdjList() const {

    for(auto curr_vertex : adj_list_) {
        TraverseList(curr_vertex);
    }
}