#include <iostream>
#include <forward_list>
#include <vector>
#include "CodeFromBookToUse/dsexceptions.h"

template <typename Object>
struct Edge {

    Edge(Object source, Object destination, int weight) : source_(source), destination_(destination), weight_(weight) {}

    Object source_;
    Object destination_;
    Object weight_;
};

template <typename Object> 
struct Vertex {

    Vertex(Object val, int weight = 0, Vertex* next = nullptr) : val_(val), weight_(weight), next_(next) {}

    bool operator==(const Vertex& rhs) {
        return this->val_ == rhs.val_;
    }

    Vertex* next_;
    Object val_;
    int weight_;
};

template <typename Object> 
class Graph {

public: 

    Graph() : size_(0) {};

    void AddEdge(const Object& source, const Object& destination, int weight);
    void AddVertex(const Object& new_elem);

    void PrintAdjList() const;
    std::size_t GetSize() const;

private:
    std::size_t size_;
    std::vector<Vertex<Object>*> adj_list_;
};

template <typename Object> 
void Graph<Object>::AddVertex(const Object& new_elem) {

    Vertex<Object>* new_vertex = new Vertex<int>(new_elem);
    adj_list_.push_back(new_vertex);
    size_++;
}

template <typename Object> 
void Graph<Object>::AddEdge(const Object& source, const Object& destination, int weight) {

    for(auto curr_vertex : adj_list_) {

        if(curr_vertex->val_ == source) {
            
            Vertex<Object>* new_vertex = new Vertex<Object> (source, weight);
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
        std::cout << "Current Value: " << curr_vertex->val_ << "\n";

        if(curr_vertex->next_ != nullptr) {
            std::cout << "Next Value: " << curr_vertex->next_->val_ << "\n";
        }

    }
}

int main() {

    Graph<int> test;
    
    test.AddVertex(3);
    test.AddVertex(4);
    test.AddEdge(3, 4, 5);
    test.PrintAdjList();


    return 0;
}