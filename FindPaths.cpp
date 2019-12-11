#include "CodeFromBookToUse/binary_heap.h"
#include "Utils.hpp"

void Dijkstra(Graph<int>& new_graph, int starting_vertex_val) {

    BinaryHeap<Vertex<int>*> heap;
    Vertex<int>* starting_vertex = new_graph.FindVertex(starting_vertex_val);
    Vertex<int>* vertex2 = new_graph.FindVertex(2);
    Vertex<int>* vertex3 = new_graph.FindVertex(3);
    Vertex<int>* vertex5 = new_graph.FindVertex(5);
    heap.insert(starting_vertex);
    heap.insert(vertex2);
    heap.insert(vertex3);
    heap.insert(vertex5);

    Vertex<int>* min = heap.findMin();
    std::cout << min->val_;
    //heap.insert(v1);

}

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << "<GRAPH_FILE> <STARTING_VERTEX>" << std::endl;
        return 0;
    }

    const std::string input_graph = std::string(argv[1]);
    const int starting_vertex_val = StringToInt(std::string(argv[2]));

    //Add code making sure the input_vertex actually exists in the graph.

    Graph<int> new_graph = CreateGraph(input_graph);
    Dijkstra(new_graph, starting_vertex_val);

    return 0;
}