//
// Created by Win10Pro on 05.05.2020.
//

#include "Functions.h"

void Functions::matrix_random_graph(int vertices, int edges) {

    bool weighted = false, oriented = false;
    Matrix_graph* graph = new Matrix_graph(vertices, oriented, weighted);

    for(int i = 0; i < edges; i++) {

        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        double* weight = Random::rand_double(vertices - 1 ,  2 * vertices - 1);
        if(v == w){
            i--;
        } else {
            graph->add_edge(v, w, weight);
            std::cout << v << "\t" << w << "\t" << weight << std::endl;
        }
    }
    graph->output_graph();
}

void Functions::list_random_graph(int vertices, int edges) {

    bool weighted = true, oriented = false;
    List_graph* graph = new List_graph(vertices, oriented, weighted);

    for(int i = 0; i < edges; i++) {

        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        double* weight = Random::rand_double(vertices - 1 ,  2 * vertices - 1);
        if(v == w){
            i--;
        } else {
            graph->add_edge(v, w, weight);
            std::cout << v << "\t" << w << "\t" << weight << std::endl;
        }
    }
    graph->output_graph();

}

void Functions::matrix_interactive() {

    matrix_random_graph(5, 7);

}

void Functions::list_interactive() {

    list_random_graph(5, 7);

}
