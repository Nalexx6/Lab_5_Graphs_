//
// Created by Win10Pro on 05.05.2020.
//

#include "Matrix_graph.h"

Matrix_graph::Matrix_graph(int &vertices, bool oriented, bool weighted) {

    this->vertices = vertices;
    this->oriented = oriented;
    this->weighted = weighted;

    adj = new int**[vertices];
    for(int i = 0; i < vertices; i++){
        adj[i] = new int* [vertices];
    }
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            adj[i][j] = nullptr;
        }
    }

}

bool Matrix_graph::edge_exists(int v, int w) {

    if(adj[v][w]) {
//        std::cout << "Edge " << v << " -> " << w << " already exists\n";
        return true;
    }
    return false;
}

void Matrix_graph::add_edge(unsigned int v, unsigned int w, int* weight) {

    if (oriented) {
            adj[v][w] = weight;
    } else {
            adj[v][w] = weight;
            adj[w][v] = weight;
    }

}

void Matrix_graph::output_graph() {

    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            if(adj[i][j] != nullptr)
                std::cout<<*adj[i][j]<<"\t";
            else
                std::cout<<"0\t";
        }
        std::cout<<"\n";
    }
    for(int i = 0; i < vertices; i++){
        std::cout<<"Vertex "<<i<<" is adjacent with vertices:\t";
        for (int j = 0; j < vertices; ++j) {
            if(adj[i][j] != nullptr)
                std::cout<<j<<"\t";
        }
        std::cout<<"\n";
    }

}
