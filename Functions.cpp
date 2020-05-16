//
// Created by Win10Pro on 05.05.2020.
//

#include "Functions.h"

Matrix_graph* Functions::matrix_random_graph(int vertices, int edges) {

    bool weighted = false, oriented = false;
    Matrix_graph* graph = new Matrix_graph(vertices, oriented, weighted);

    for(int i = 0; i < edges; i++) {
        if(i == vertices * (vertices - 1) / 2 + 1) {
            std::cout << "There are no possible edges ot add - graph is full\n";
            break;
        }
        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        int* weight = new int(Random::rand(vertices - 1 ,  2 * vertices - 1));
        if(graph->edge_exists(v, w)){
            i--;
        } else {
            graph->add_edge(v, w, weight);
//            std::cout << v << "\t" << w << "\t" << *weight << std::endl;
        }
    }
    return graph;
}

List_graph* Functions::list_random_graph(int vertices, int edges) {

    bool weighted = true, oriented = false;
    List_graph* graph = new List_graph(vertices, oriented, weighted);

    for(int i = 0; i < edges; i++) {
        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        int weight = Random::rand(0 ,  2 * vertices - 1);
        if(graph->edge_exists(v , w)){
            i--;
        } else {
            graph->add_edge(v, w, weight);
//            std::cout << v << "\t" << w << "\t" << weight << std::endl;
        }
    }
    return graph;
}

void Functions::matrix_interactive() {

    Matrix_graph* graph = matrix_random_graph(1, 0);
    char response = 'y';
    while(response == 'y') {

        std::cout<<"Hello, please choose the choose what you want to do with your graph:\n"
                   "1 - Create NEW random graph with adjusted quantity of vertices and edges\n"
                   "2 - Add edge to graph\n"
                   "3 - Output graph\n"
                   "4 - Find amount of connectivity components in graph\n"
                   "5 - Find amount of cycles in graph\n"
                   "6 - Find lowest-cost path from one vertex to another\n"
                   "7 - Find lowest-cost path from one vertex to all other vertices\n"
                   "8 - Find lowest-cost path between all vertices\n";
        int key;
        std::cin>>key;
        if(key == 1){
            int vertices, edges;
            std::cout<<"Please enter the number of vertices in your graph\n";
            std::cin>>vertices;
            std::cout<<"Please enter the number of edges\n";
            std::cin>>edges;
            graph = matrix_random_graph(vertices, edges);
            std::cout<<"This is your graph\n";
            graph->output_graph();
        }
        if(key == 2){
            int v, w, weight;
            std::cout<<"Please enter v and w - first and second vertex of your edge\n";
            std::cin>>v>>w;
            std::cout<<"Please enter weight of your edge (>=0)";
            std::cin>>weight;
            int* weight_p = new int (weight);
            graph->add_edge(v, w, weight_p);

        }
        if(key == 3){
            std::cout<<"This is your graph(number is weight if edge exists, N - if not)\n";
            graph->output_graph();
        }
        if(key == 4){
            std::cout<<"Your graph has "<<graph->dfs(true)<<" connectivity components\n";
        }
        if(key == 5){
            int cycles = graph->acyclicity();
            if(cycles == 0)
                std::cout<<"Your graph is acyclic\n";
            else
                std::cout<<"Your graph has "<<cycles<<" cycles\n";
        }
        if(key == 6){
            int v, w;
            std::cout<<"Please enter v, w - vertices for which you want to find path\n";
            std::cin>>v>>w;
            std::vector<int> path = graph->dijkstra_distance(v)[w];
            std::cout<<"Cost: "<<graph->costs[v][w]<<"\n";
            std::cout<<"Path: ";
            for(int i = 0; i < path.size(); i++){
                std::cout<<path[i]<<"->";

            }
            std::cout<<w<<"\n";
        }
        if(key == 7){
            int v;
            std::cout<<"Please enter v - vertex for which you want to find paths\n";
            std::cin>>v;
            std::vector<int>* path = graph->dijkstra_distance(v);
            for(int j = 0; j < graph->vertices; j++) {
                std::cout <<"Vertex: "<<j<< "\tCost: " << graph->costs[v][j] << "\n";
                std::cout << "Path: ";
                for (int i = 0; i < path[j].size(); i++) {
                    std::cout << path[j][i] << "->";

                }
                std::cout << j << "\n";
            }
        }
        if(key == 8){
            graph->dijkstra_distance();
            for(int i = 0 ; i < graph->vertices; i++){
                std::cout<<"\t"<<i;
            }
            for(int i = 0; i < graph->vertices; i++){
                std::cout<<i<<": ";
                for(int j = 0; j < graph->vertices; j++){
                    std::cout<<graph->costs[i][j]<<"\t";
                }
            }
        }
        std::cout<<"If you want to do anything else with graph press 'y', press 'n', if you don`t\n";
        std::cin>>response;

    }

}

void Functions::list_interactive() {

    List_graph* graph = list_random_graph(1, 0);
    char response = 'y';
    while(response == 'y') {

        std::cout<<"Hello, please choose the choose what you want to do with your graph:\n"
                   "1 - Create NEW random graph with adjusted quantity of vertices and edges\n"
                   "2 - Add edge to graph\n"
                   "3 - Output graph\n"
                   "4 - Find amount of connectivity components in graph\n"
                   "5 - Find amount of cycles in graph\n"
                   "6 - Find lowest-cost path from one vertex to another\n"
                   "7 - Find lowest-cost path from one vertex to all other vertices\n"
                   "8 - Find lowest-cost path between all vertices\n";
        int key;
        std::cin>>key;
        if(key == 1){
            int vertices, edges;
            std::cout<<"Please enter the number of vertices in your graph\n";
            std::cin>>vertices;
            std::cout<<"Please enter the number of edges\n";
            std::cin>>edges;
            graph = list_random_graph(vertices, edges);
            std::cout<<"This is your graph\n";
            graph->output_graph();
        }
        if(key == 2){
            int v, w, weight;
            std::cout<<"Please enter v and w - first and second vertex of your edge\n";
            std::cin>>v>>w;
            std::cout<<"Please enter weight of your edge (>=0)";
            std::cin>>weight;
            graph->add_edge(v, w, weight);

        }
        if(key == 3){
            std::cout<<"This is your graph(weight of edge is in parentheses)\n";
            graph->output_graph();
        }
        if(key == 4){
            std::cout<<"Your graph has "<<graph->dfs(true)<<" connectivity components\n";
        }
        if(key == 5){
            int cycles = graph->acyclicity();
            if(cycles == 0)
                std::cout<<"Your graph is acyclic\n";
            else
                std::cout<<"Your graph has "<<cycles<<" cycles\n";
        }
        if(key == 6){
            int v, w;
            std::cout<<"Please enter v, w - vertices for which you want to find path\n";
            std::cin>>v>>w;
            std::vector<int> path = graph->dijkstra_distance(v)[w];
            std::cout<<"Cost: "<<graph->costs[v][w]<<"\n";
            std::cout<<"Path: ";
            for(int i = 0; i < path.size(); i++){
                std::cout<<path[i]<<"->";

            }
            std::cout<<w<<"\n";
        }
        if(key == 7){
            int v;
            std::cout<<"Please enter v - vertex for which you want to find paths\n";
            std::cin>>v;
            std::vector<int>* path = graph->dijkstra_distance(v);
            for(int j = 0; j < graph->vertices; j++) {
                std::cout << "Vertex: "<<j<<"\tCost: " << graph->costs[v][j] << "\n";
                std::cout << "Path: ";
                for (int i = 0; i < path[j].size(); i++) {
                    std::cout << path[j][i] << "->";

                }
                std::cout << j << "\n";
            }
        }
        if(key == 8){
            graph->dijkstra_distance();
            for(int i = 0 ; i < graph->vertices; i++){
                std::cout<<"\t"<<i;
            }
            for(int i = 0; i < graph->vertices; i++){
                std::cout<<i<<": ";
                for(int j = 0; j < graph->vertices; j++){
                    std::cout<<graph->costs[i][j]<<"\t";
                }
            }
        }
        std::cout<<"If you want to do anything else with graph press 'y', press 'n', if you don`t\n";
        std::cin>>response;

    }
}
