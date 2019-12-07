#include <iostream>
#include <forward_list>
#include <vector>

template <typename Object>
struct Edge {

    Edge(Object source, Object destination, int weight) : source_(source), destination_(destination), weight_(weight) {}

    Object source_;
    Object destination_;
    Object weight_;
};

template <typename Object> 
struct Vertex {

    Vertex(Object val, int cost, Vertex* next = nullptr) : val_(val), cost_(cost), next_(next) {}

    Vertex* next_;
    Object val_;
    int cost_;
};

template <typename Object> 
class Graph {

private:

    std::vector<Vertex<Object>*> edges;
};