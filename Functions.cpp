//
// Created by Win10Pro on 05.05.2020.
//

#include "Functions.h"

void Functions::matrix_random_graph(int vertices, int edges) {

    bool weighted = false, oriented = false;
    Matrix_graph* graph = new Matrix_graph(vertices, oriented, weighted);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> generator(0,vertices - 1); // distribution in range [1, 6]

    for(int i = 0; i < edges; i++) {

        unsigned v = generator(rng);
        unsigned w = generator(rng);
        graph->add_edge(v, w, 0);
        std::cout<<v<<"\t"<<w<< std::endl;
    }
    graph->output_graph();
}

void Functions::list_random_graph(int vertices, int edges) {

    bool weighted = false, oriented = false;
    List_graph* graph = new List_graph(vertices, oriented, weighted);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> generator(0,vertices - 1); // distribution in range [1, 6]

    for(int i = 0; i < edges; i++) {

        unsigned v = generator(rng);
        unsigned w = generator(rng);
        graph->add_edge(v, w, 0);
        std::cout<<v<<"\t"<<w<< std::endl;
    }
    graph->output_graph();

}

void Functions::matrix_interactive() {

    matrix_random_graph(5, 7);

}

void Functions::list_interactive() {

    list_random_graph(5, 7);

}
