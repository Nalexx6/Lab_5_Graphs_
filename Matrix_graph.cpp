//
// Created by Win10Pro on 05.05.2020.
//

#include "Matrix_graph.h"

Matrix_graph::Matrix_graph(int &vertices, bool oriented, bool weighted) {

    this->vertices = vertices;
    this->oriented = oriented;
    this->weighted = weighted;

    adj = new double**[vertices];
    for(int i = 0; i < vertices; i++){
        adj[i] = new double* [vertices];
    }
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            adj[i][j] = nullptr;
        }
    }

}

void Matrix_graph::add_edge(unsigned int v, unsigned int w, double* weight) {

    if (adj[v][w] == 0) {
        if (oriented) {
                adj[v][w] = weight;
        } else {
                adj[v][w] = weight;
                adj[w][v] = weight;
        }
    }
    else{
        std::cout<<"Edge "<<v<<" -> "<<w<<" already exists\n";
    }

}

void Matrix_graph::output_graph() {

    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            std::cout<<adj[i][j]<<"\t";
        }
        std::cout<<"\n";
    }
    for(int i = 0; i < vertices; i++){
        std::cout<<"Vertex "<<i<<" is adjacent with vertices:\t";
        for (int j = 0; j < vertices; ++j) {
            if(adj[i][j] != 0)
                std::cout<<j<<"\t";
        }
        std::cout<<"\n";
    }

}

