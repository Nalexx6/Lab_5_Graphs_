//
// Created by Win10Pro on 05.05.2020.
//

#ifndef LAB_5_GRAPHS__MATRIX_GRAPH_H
#define LAB_5_GRAPHS__MATRIX_GRAPH_H

#include <iostream>

class Matrix_graph {

private:

    int vertices;


public:

    bool oriented;
    bool weighted;
    int*** adj;

    Matrix_graph(int& vertices, bool oriented, bool weighted);

    bool edge_exists(int v, int w);

    void add_edge(unsigned int v, unsigned int w, int* weight);
    void output_graph();

};


#endif //LAB_5_GRAPHS__MATRIX_GRAPH_H
