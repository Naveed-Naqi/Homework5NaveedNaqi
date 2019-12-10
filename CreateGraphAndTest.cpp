/*
** Author: Naveed Naqi
** Date: 12/10/2019
** Description: This file creates and tests the Graph implementation outlined in the Graph.hpp file.
** When running this file you must supply two text files, both contained in a folder called InputFiles.
** The first file must be describing a graph with the first line being the number of verticies, 
** and the rest of the file being an adjacency list representation.
** The second file must contain a list of vertex pairs that are contained within the graph.
*/

#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <climits>

int StringToInt(std::string some_string) {
    std::stringstream conversion(some_string);
    int val = 0;
    conversion >> val;
    return val;
}

float StringToFloat(std::string some_string) {
    std::stringstream conversion(some_string);
    float val = 0;
    conversion >> val;
    return val;
}

/*
** Assumes that the first line of the text file being read is the size of the input graph.
** @param: input_graph is a text file that contains an adjacency list representation of a graph.
** return: returns the size of the graph.
*/
std::size_t GetSizeFromFile(std::string input_graph) {
    std::ifstream input_file;
    input_file.open("InputFiles/"+input_graph);

    if(!input_file) {
        std::cerr << "Unable to open " + input_graph;
        exit(1);
    }

    std::string curr_line = "";
    std::getline(input_file, curr_line);
    input_file.close();

    return StringToInt(curr_line);
}

/*
** Adds the corresponding edges to a graph.
** Assumes that the curr_line is formated like an adjacency list, with the source vertex at the beginning of the string
** and all destination verticies and their weights following that.
** @param: input_graph is a text file that contains an adjacency list representation of a graph.
*/
void CreateEdges(Graph<int>& new_graph, std::string curr_line) {

    int source_val = StringToInt(curr_line.substr(0,1));

    if(new_graph.FindVertex(source_val) == nullptr) {
        new_graph.AddVertex(source_val);
    }


    std::size_t size = curr_line.size();
    if(size < 3) { return; }

    int start_pos = 2;
    int num_spaces = 0;
    int vertex_val = 0;
    float weight = 0;

    for(int i = start_pos; i < size; ++i) {
        
        if(curr_line[i] == ' ') {
            num_spaces++;

            if(num_spaces == 1) {

                vertex_val = StringToInt(curr_line.substr(start_pos, i-start_pos+1));

                if (new_graph.FindVertex(vertex_val) == nullptr) {
                    new_graph.AddVertex(vertex_val);
                }
                start_pos = i+1;
            }

            if(num_spaces == 2) {
                
                weight = StringToFloat(curr_line.substr(start_pos, i-start_pos+1));
                new_graph.AddEdge(source_val, vertex_val, weight);
                start_pos = i+1;
                num_spaces = 0;
            }
        }
    }

    weight = StringToFloat(curr_line.substr(start_pos, size-start_pos+1));
    new_graph.AddEdge(source_val, vertex_val, weight);
}

/*
** Creates a graph that matches the given input_graph.
** Assumes there is a text file in a folder called InputFiles that has the same name as the input string input_graph.
** @param: input_graph is a text file that contains an adjacencny list representation of a graph.
** @return: returns the completed graph.
*/
Graph<int> CreateGraph(std::string input_graph) {

    std::ifstream input_file;
    std::size_t graph_size = GetSizeFromFile(input_graph);
    Graph<int> new_graph(graph_size);

    input_file.open("InputFiles/"+input_graph);

    if(!input_file) {
        std::cerr << "Unable to open " + input_graph;
        exit(1);
    }

    std::string curr_line = "";
    std::size_t  line_num = 1;

    while(std::getline(input_file, curr_line)) {
        
        //Skip the first line because it contains the size of the graph and we already have that.
        if(line_num != 1) {
            CreateEdges(new_graph, curr_line);
        }

        line_num++;
    }

    input_file.close();

    return new_graph;
}

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
        std::cout << "Usage: " << argv[0] << "<GRAPH_FILE> <GRAPH_QUERY>" << std::endl;
        return 0;
    }

    const std::string input_graph = std::string(argv[1]);
    const std::string input_query = std::string(argv[2]);

    Graph<int> new_graph = CreateGraph(input_graph);
    TestGraph(new_graph, input_query);
    return 0;
}