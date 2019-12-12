/*
** Author: Naveed Naqi
** Date: 12/10/2019
** Description: This file creates and tests the Graph implementation outlined in the Graph.hpp file.
** When running this file you must supply two text files, both contained in a folder called InputFiles.
** The first file must be describing a graph with the first line being the number of verticies, 
** and the rest of the file being an adjacency list representation.
** The second file must contain a list of vertex pairs that are contained within the graph.
*/

#include "Utils.hpp"

/*
** Tests a graph implementation in Graph.hpp by checking the edges between the vertex pairs that were specified in an input_query
** Assumes there is a text file in a folder called InputFiles that has the same name as the input string input_query.
** @param: input_query is a text file that contains a list of vertex pairs.
** @param: new_graph is a non-empty graph that has been created with the implementation specified in Graph.hpp
*/
void TestGraph(Graph<int>& new_graph, std::string input_query) {

    std::ifstream input_file;
    input_file.open("InputFiles/"+input_query);

    if(!input_file) {
        std::cerr << "Unable to open " + input_query;
        exit(1);
    }

    std::string curr_line = "";

    while(std::getline(input_file, curr_line)) {

        std::size_t size = curr_line.size();
        float weight_to_search_for = 0;
        int source = 0;
        int dest = 0;
                
        for(int i = 0; i < size; ++i) {
            if(curr_line[i] == ' ') {
                source = StringToInt(curr_line.substr(0, i+1));
                dest = StringToInt(curr_line.substr(i+1, size-i+2));

                weight_to_search_for = new_graph.FindWeightOfEdge(source, dest);

                if(weight_to_search_for != INT_MIN) {
                    std::cout <<  curr_line << ": Connected, weight of edge is " << weight_to_search_for << "\n";
                } else {
                    std::cout <<  curr_line << ": Not connected \n";
                }
            }
        }
    }
}

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <GRAPH_FILE> <GRAPH_QUERY>" << std::endl;
        return 0;
    }

    const std::string input_graph = std::string(argv[1]);
    const std::string input_query = std::string(argv[2]);

    Graph<int> new_graph = CreateGraph(input_graph);
    TestGraph(new_graph, input_query);
    return 0;
}