#include "Graph.hpp"
#include <fstream>
#include <sstream>

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
** @param: input_graph is a text file that contains an adjacencny list representation of a graph.
*/
std::size_t GetSize(std::string input_graph) {
    std::ifstream input_file;
    input_file.open("InputFiles/"+input_graph);

    std::string curr_line = "";
    std::getline(input_file, curr_line);

    return StringToInt(curr_line);
}

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

    for(int i = start_pos; i < size; i++) {
        
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
** @param: input_graph is a text file that contains an adjacencny list representation of a graph.
*/
Graph<int> CreateGraph(std::string input_graph) {

    std::ifstream input_file;
    std::size_t graph_size = GetSize(input_graph);
    Graph<int> new_graph(graph_size);

    input_file.open("InputFiles/"+input_graph);

    if(!input_file) {
        std::cerr << "Unable to open " + input_graph;
        exit(1);
    }

    std::string curr_line = "";
    std::size_t  line_num = 1;

    while(std::getline(input_file, curr_line)) {

        if(line_num != 1) {

            //std::cout << curr_line[0] << "\n";
            CreateEdges(new_graph, curr_line);
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
    new_graph.PrintAdjList();

    return 0;
}