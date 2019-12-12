#include "CodeFromBookToUse/binary_heap.h"
#include "Utils.hpp"

void Dijkstra(Graph<int>& new_graph, Vertex<int>* starting_vertex) {

    BinaryHeap<Vertex<int>*> heap;
    new_graph.ResetDistanceAndKnownStatus();
    starting_vertex->distance_ = 0;
    starting_vertex->prev_ = starting_vertex;

    heap.insert(starting_vertex);

    while(!heap.isEmpty()) {

        Vertex<int>* curr_vertex = heap.findMin();
        heap.deleteMin();

        for(auto edge : curr_vertex->edges_) {
            
            int curr_distance = edge.dest_->distance_;
            int new_distance = curr_vertex->distance_ + edge.weight_;

            if(new_distance < curr_distance) {
                edge.dest_->distance_ = new_distance;
                edge.dest_->prev_ = curr_vertex;
            }

            if(!edge.dest_->known_) {
                heap.insert(edge.dest_);
            }
        }

        curr_vertex->known_ = true;
    }

    new_graph.PrintShortestPaths(starting_vertex);
}

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << "<GRAPH_FILE> <STARTING_VERTEX>" << std::endl;
        return 0;
    }

    const std::string input_graph = std::string(argv[1]);
    const int starting_vertex_val = StringToInt(std::string(argv[2]));

    Graph<int> new_graph = CreateGraph(input_graph);
    Vertex<int>* starting_vertex = new_graph.FindVertex(starting_vertex_val);

    if(starting_vertex == nullptr) {
        std::cout << "This vertex is not in the graph. Please try again.";
        return 0;
    }

    Dijkstra(new_graph, starting_vertex);

    return 0;
}