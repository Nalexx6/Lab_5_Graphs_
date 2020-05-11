//
// Created by Win10Pro on 05.05.2020.
//

#ifndef LAB_5_GRAPHS__LIST_GRAPH_H
#define LAB_5_GRAPHS__LIST_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>

class List_graph {

private:

    class Edge{
    public:
        unsigned vertex;
        int weight;
        Edge(unsigned vertex, int weight){
            this->vertex = vertex;
            this->weight = weight;
        }
    };
    int vertices;

public:

    bool oriented;
    bool weighted;
    std::vector <Edge>* adj;
    int* visited;
    std::queue <int> s_queue;

    List_graph(int& vertices, bool oriented, bool weighted);

    bool edge_exists(int v, int w);

    void add_edge(unsigned int v, unsigned int w, int weight);
    void output_graph();

    void dfs(bool connectivity);
    void dfs_(int v);
    int acyclicity();
    void find_cycle(int v, int prev, int& cycles);
    void bfs();
    void bfs(int v);



};


#endif //LAB_5_GRAPHS__LIST_GRAPH_H
