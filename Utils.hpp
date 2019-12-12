/*
** Author: Naveed Naqi
** Date: 12/10/2019
** Description: This file contains some utility functions that will be needed across all other files in the project.
** The primary goal of this utils file is to provide a set of functions to create a graph from the given text file.
*/

#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <climits>

int StringToInt(std::string some_string);
float StringToFloat(std::string some_string);

/*
** Assumes that the first line of the text file being read is the size of the input graph.
** @param: input_graph is a text file that contains an adjacency list representation of a graph.
** return: returns the size of the graph.
*/
std::size_t GetSizeFromFile(std::string input_graph);

/*
** Adds the corresponding edges to a graph.
** Assumes that the curr_line is formated like an adjacency list, with the source vertex at the beginning of the string
** and all destination verticies and their weights following that.
** @param: input_graph is a text file that contains an adjacency list representation of a graph.
*/
void CreateEdges(Graph<int>& new_graph, std::string curr_line);

/*
** Creates a graph that matches the given input_graph.
** Assumes there is a text file in a folder called InputFiles that has the same name as the input string input_graph.
** @param: input_graph is a text file that contains an adjacencny list representation of a graph.
** ASSUMES there are no random line breaks in the graph or other random spaces. It must be formatted correctly.
** @return: returns the completed graph.
*/
Graph<int> CreateGraph(std::string input_graph);


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

void CreateEdges(Graph<int>& new_graph, std::string curr_line) {

    //Source val should actually be the value before the first space, so I should change this.
    int source_val = 0;
    int edges_start_index = 0;
    std::size_t size = curr_line.size();

    for(; edges_start_index < size; ++edges_start_index) {
        if(curr_line[edges_start_index] == ' ') {
            source_val = StringToInt(curr_line.substr(0, edges_start_index)); 
            break;
        }
    }

    if(new_graph.FindVertex(source_val) == nullptr && edges_start_index != size) {
        new_graph.AddVertex(source_val);
    }

    if(size <= edges_start_index+1   || edges_start_index == size) { return; }

    int start_pos = edges_start_index+1;
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
