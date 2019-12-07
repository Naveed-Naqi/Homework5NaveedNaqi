#include <iostream>
#include <vector>

template <typename Object> 
struct Vertex {

    Vertex (Object val, int cost, Vertex* next = nullptr) : val_(val), cost_(cost), next_(next) {}

    friend std::ostream & operator << (std::ostream &out, const Vertex* v) {
        out << "Value: " << v->val_ << "\n";
        out << "Cost: " << v->cost_ << "\n";
        return out;
    }

    Vertex* next_;
    Object val_;
    int cost_;
};

template <typename Object>
void PrintVector(const std::vector<Object>& some_list) {

    for(auto elem : some_list) {
        std::cout << elem << "\n";
    }

}

int main () {

    Vertex<int>* v1 = new Vertex<int>(1,3);
    Vertex<int>* v2 = new Vertex<int>(2,7);
    Vertex<int>* v3 = new Vertex<int>(3,8);
    Vertex<int>* v4 = new Vertex<int>(4,9);
    Vertex<int>* v5 = new Vertex<int>(5,10);

    std::vector<Vertex<int>*> edges;
    edges.push_back(v1);
    edges.push_back(v2);
    edges.push_back(v3);
    edges.push_back(v4);
    edges.push_back(v5);

    PrintVector(edges);

    return 0;
}