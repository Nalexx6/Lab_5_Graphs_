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


    List_graph(int& vertices, bool oriented, bool weighted);

    //Graph structure
    bool edge_exists(int v, int w);
    void add_edge(unsigned int v, unsigned int w, int weight);
    void output_graph();

    //Depth First Search(with finding amount of connectivity components)
    void dfs(bool connectivity);
    void dfs_(int v);

    //Find amount of cycles in graph
    int acyclicity();
    void find_cycle(int v, int prev, int prev_prev, int& cycles);

    //Breadth first search
    void bfs();
    void bfs(int v);

    //Finding lowest-cost path(Dijsktra)
    int** costs;
    std::vector <int>** dijkstra_distance();
    std::vector <int>* dijkstra_distance(int v);
    void find_distance(int v, int w, std::vector <int>* distances);




};


#endif //LAB_5_GRAPHS__LIST_GRAPH_H
