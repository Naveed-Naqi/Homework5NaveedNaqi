#include "Graph.hpp"
#include <fstream>
#include <sstream>


/*
** @param: input_graph is a text file that contains an adjacencny list representation of a graph.
*/
Graph<int> CreateGraph(std::string input_graph) {

    std::ifstream input_file;
    Graph<int> new_graph;

    input_file.open("InputFiles/"+input_graph);

    if(!input_file) {
        std::cerr << "Unable to open " + input_graph;
        exit(1);
    }

    std::string curr_line = "";
    std::size_t  line_num = 1;

    while(std::getline(input_file, curr_line)) {

        if(line_num != 1) {

            //std::stringstream string_to_int(std::string(line_num[0]));
            std::cout << curr_line[0] << "\n";
        }

        line_num++;
    }

    input_file.close();

    return new_graph;
}

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << "<input_graph> <input_query>" << std::endl;
        return 0;
    }

    const std::string input_graph = std::string(argv[1]);
    const std::string input_query = std::string(argv[2]);

    Graph<int> new_graph = CreateGraph(input_graph);
}