//
// Created by Win10Pro on 05.05.2020.
//

#include "List_graph.h"

List_graph::List_graph(int &vertices, bool oriented, bool weighted) {

    this->vertices = vertices;
    this->oriented = oriented;
    this->weighted = weighted;
    adj = new std::vector <Edge> [vertices];

}

void List_graph::add_edge(unsigned int v, unsigned int w, double weight) {

    for(int i = 0; i < adj[v].size(); i++){
        if(adj[v][i].vertex == w){
            std::cout<<"Edge "<<v<<" -> "<<w<<" already exists\n";
            return;
        }
    }
//    if(!oriented){
//
//    }
    if(oriented) {
        adj[v].emplace_back(Edge(w, weight));
    } else{
        adj[v].emplace_back(Edge(w, weight));
        adj[w].emplace_back(Edge(v, weight));
    }

}

void List_graph::output_graph() {

    for(int i = 0; i < vertices; i++){
        std::cout<<"Vertex "<<i<<" adjacent with vertices:\t";
        for(int j = 0; j < adj[i].size(); j++){
            std::cout<<adj[i][j].vertex<<"\t";
        }
        std::cout<<"\n";
    }

}
