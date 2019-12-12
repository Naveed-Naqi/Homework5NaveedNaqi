#include "Utils.hpp"

void TopologicalSorting(Graph<int>& new_graph) {

}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << "<GRAPH_FILE> <STARTING_VERTEX>" << std::endl;
        return 0;
    }

    const std::string input_graph = std::string(argv[1]);

    Graph<int> new_graph = CreateGraph(input_graph);
    TopologicalSorting(new_graph);

    return 0;
}