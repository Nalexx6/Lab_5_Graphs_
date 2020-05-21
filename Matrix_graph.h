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
    int vertices;
    int*** adj;
    int* visited;
    int* component;

    Matrix_graph(int& vertices, bool oriented);

    //Graph structure
    bool edge_exists(int v, int w);
    void add_edge(unsigned int v, unsigned int w, int* weight);
    void output_graph();

    //Depth first search
    int dfs(bool connectivity);
    void dfs_(int v, bool& connectivity);

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

    //Topological sorting
    int* sorted;
    void top_sort();
    void sort(int v, int& index);

    //Build spanning tree(dfs)
    Matrix_graph* span_tree();
    void span_tree(int v, Matrix_graph* spanning_tree);
    int sum_weight();

    //Min spanning tree(Prim)
    class Span_edge{
    public:
        unsigned v;
        unsigned w;
        int weight;
        Span_edge(unsigned v, unsigned w, int weight){
            this->v = v;
            this->w = w;
            this->weight = weight;
        }
        Span_edge() = default;

    };
    Matrix_graph* prim_spanning_tree();
    std::vector <Span_edge> edges;
    //Merge sort for all edges, to find min weight
    void merge_sort(std::vector <Span_edge>& array);
    void merge(std::vector <Span_edge>& array, std::vector <Span_edge>& for_merge, int lo, int mid, int hi);
    void sort(std::vector <Span_edge>& array, std::vector <Span_edge>& for_merge, int lo, int hi);
};


#endif //LAB_5_GRAPHS__MATRIX_GRAPH_H
