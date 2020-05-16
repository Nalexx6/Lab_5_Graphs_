//
// Created by Win10Pro on 05.05.2020.
//

#ifndef LAB_5_GRAPHS__MATRIX_GRAPH_H
#define LAB_5_GRAPHS__MATRIX_GRAPH_H

#include <iostream>
#include <queue>

class Matrix_graph {

private:

public:

    bool oriented;
    bool weighted;
    int vertices;
    int*** adj;
    int* visited;

    Matrix_graph(int& vertices, bool oriented, bool weighted);

    //Graph structure
    bool edge_exists(int v, int w);
    void add_edge(unsigned int v, unsigned int w, int* weight);
    void output_graph();

    //Depth first search
    int dfs(bool connectivity);
    void dfs_(int v);

    //Breadth first search
    void bfs();
    void bfs(int v);

    //Find amount of cycles in graph
    int acyclicity();
    void find_cycle(int v, int prev, int prev_prev, int& cycles);

    //Finding lowest-cost path(Dijkstra)
    int exist_unvisited();
    static void copy_vector(std::vector <int>& vector_1, std::vector <int>& vector_2);
    int** costs;
    std::vector <int>** dijkstra_distance();
    std::vector <int>* dijkstra_distance(int v);
    void find_distance(int v, std::vector <int>* distances);

};


#endif //LAB_5_GRAPHS__MATRIX_GRAPH_H
