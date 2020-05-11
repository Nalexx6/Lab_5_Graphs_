//
// Created by Win10Pro on 05.05.2020.
//

#include "List_graph.h"

List_graph::List_graph(int &vertices, bool oriented, bool weighted) {

    this->vertices = vertices;
    this->oriented = oriented;
    this->weighted = weighted;

    adj = new std::vector <Edge> [vertices];

    visited = new int [vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
}

bool List_graph::edge_exists(int v, int w) {

    for(int i = 0; i < adj[v].size(); i++){
        if(adj[v][i].vertex == w){
//            std::cout<<"Edge "<<v<<" -> "<<w<<" already exists\n";
            return true;
        }
    }
    return false;
}

void List_graph::add_edge(unsigned int v, unsigned int w, int weight) {

    for(int i = 0; i < adj[v].size(); i++){
        if(adj[v][i].vertex == w){
            std::cout<<"Edge "<<v<<" -> "<<w<<" already exists\n";
            return;
        }
    }
    if(oriented) {
        adj[v].emplace_back(Edge(w, weight));
    } else{
        if(v == w) {
            adj[v].emplace_back(w, weight);
        } else {
            adj[v].emplace_back(Edge(w, weight));
            adj[w].emplace_back(Edge(v, weight));
        }
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

void List_graph::dfs(bool connectivity) {

    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    int components = 0;
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0) {
            dfs_(i);
            components++;
        }
    }
//    for(int i = 0; i < vertices; i++){
//        std::cout<<visited[i]<<"\t";
//    }

    std::cout<<"Graph has "<<components<<" connectivity components\n";
}

void List_graph::dfs_(int v) {

    if(visited[v] != 0)
        return;
    visited[v]++;
    for(int i = 0; i < adj[v].size(); i++){
            dfs_(adj[v][i].vertex);

    }
    visited[v]++;

}

//void List_graph::bfs() {
//
//    for(int i = 0; i < vertices; i++){
//        if(visited[i] == 0){
//            bfs(i);
//        }
//    }
//    for(int i = 0; i < vertices; i++){
//        std::cout<<visited[i]<<"\t";
//    }
//    std::cout<<"\n";
//
//}
//
//void List_graph::bfs(int v) {
//
//    if(visited[v] != 0){
//        return;
//    }
//    visited[v]++;
//    s_queue.push(v);
//    for(int i = 0; i < adj[v].size(); i++){
//        bfs(i);
//    }
//    s_queue.pop();
//
//}
int List_graph::acyclicity() {
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    int cycles = 0;
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            find_cycle(i, i,cycles);
        }
    }

    return cycles;

}

void List_graph::find_cycle(int v, int prev, int& cycles) {

    if(visited[v] != 0){
        if(visited[v] == 1) {
            if (oriented || v != prev) {
                cycles++;
            }
            std::cout<< v <<"\t"<<prev<<"\t"<< cycles << "\n";
        }
        return;
    }

    visited[v]++;
    for(int i = 0; i < adj[v].size(); i++){
        find_cycle(adj[v][i].vertex, prev,cycles);

    }
    visited[v]++;

}
