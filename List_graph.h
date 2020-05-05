//
// Created by Win10Pro on 05.05.2020.
//

#ifndef LAB_5_GRAPHS__LIST_GRAPH_H
#define LAB_5_GRAPHS__LIST_GRAPH_H

#include <iostream>
#include <vector>

class List_graph {

private:

    class Edge{
    public:
        unsigned vertex;
        double weight;
        Edge(unsigned vertex, double weight){
            this->vertex = vertex;
            this->weight = weight;
        }
    };
    int vertices;

public:

    bool oriented;
    bool weighted;
    std::vector <Edge>* adj;

    List_graph(int& vertices, bool oriented, bool weighted);

    void add_edge(unsigned int v, unsigned int w, double weight);
    void output_graph();



};


#endif //LAB_5_GRAPHS__LIST_GRAPH_H
