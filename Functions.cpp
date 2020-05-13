//
// Created by Win10Pro on 05.05.2020.
//

#include "Functions.h"

void Functions::matrix_random_graph(int vertices, int edges) {

    bool weighted = false, oriented = false, connectivity = true;
    Matrix_graph* graph = new Matrix_graph(vertices, oriented, weighted);

    for(int i = 0; i < edges; i++) {

        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        int* weight = new int(Random::rand(vertices - 1 ,  2 * vertices - 1));
        if(graph->edge_exists(v, w)){
            i--;
        } else {
            graph->add_edge(v, w, weight);
            std::cout << v << "\t" << w << "\t" << *weight << std::endl;
        }
    }
    graph->output_graph();
    graph->dfs(connectivity);
//    graph->bfs();
    std::cout<<"Graph has "<<graph->acyclicity()<<" cycles\n";
}

void Functions::list_random_graph(int vertices, int edges) {

    bool weighted = true, oriented = false, connectivity = true;
    List_graph* graph = new List_graph(vertices, oriented, weighted);

    for(int i = 0; i < edges; i++) {
        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        int weight = Random::rand(0 ,  2 * vertices - 1);
        if(graph->edge_exists(v , w)){
            i--;
        } else {
            graph->add_edge(v, w, weight);
            std::cout << v << "\t" << w << "\t" << weight << std::endl;
        }
    }
    graph->output_graph();
//    graph->dfs(connectivity);
    graph->bfs();
    std::cout<<"Graph has "<<graph->acyclicity()<<" cycles\n";

}

void Functions::matrix_interactive() {

    matrix_random_graph(7, 5);

}

void Functions::list_interactive() {

    list_random_graph(7, 5);

}
