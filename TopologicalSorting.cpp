#include "Utils.hpp"

template<typename Object>
void PrintVector(std::vector<Object> some_vector) {

    if(some_vector.empty()) { return; }

    std::cout << some_vector[0];

    for(int i = 1; i < some_vector.size(); ++i) {
        std::cout << ", " << some_vector[i];
    }

    std::cout << ".\n";
}

void TopologicalSorting(Graph<int> new_graph) {

    std::size_t num_verticies = new_graph.GetSize();
    Vertex<int>* curr_vertex = new_graph.GetNewVertexWithIndegreeZero();
    std::vector<int> sorted_verticies;

    while(curr_vertex != nullptr) {
        new_graph.RemoveVertex(curr_vertex->val_);
        sorted_verticies.push_back(curr_vertex->val_);
        curr_vertex = new_graph.GetNewVertexWithIndegreeZero();
    }

    if(sorted_verticies.size() != num_verticies) { 
        std::cout << "Cycle found \n";
        return;
    }

    PrintVector(sorted_verticies);
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << std::endl;
        return 0;
    }

    const std::string input_graph = std::string(argv[1]);

    Graph<int> new_graph = CreateGraph(input_graph);
    TopologicalSorting(new_graph);

    return 0;
}