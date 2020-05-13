//
// Created by Win10Pro on 05.05.2020.
//

#include "Matrix_graph.h"

Matrix_graph::Matrix_graph(int &vertices, bool oriented, bool weighted) {

    this->vertices = vertices;
    this->oriented = oriented;
    this->weighted = weighted;

    visited = new int [vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }

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
                std::cout<<*adj[i][j]<<" ";
            else
                std::cout<<"N ";
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

void Matrix_graph::dfs(bool connectivity) {

    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
     int components = 0;
     for(int i = 0; i < vertices; i++){
         if(visited[i] == 0) {
             dfs_(i);
             if(connectivity)
                 components++;
         }
     }
//     for(int i = 0; i < vertices; i++){
//         std::cout<<visited[i]<<"\t";
//     }
    if(connectivity)
        std::cout<<"Graph has "<<components<<" connectivity components\n";

}

void Matrix_graph::dfs_(int v) {

    if(visited[v] != 0)
        return;
    visited[v]++;
    for(int i = 0; i < vertices; i++){
        if(adj[v][i] != nullptr){
            dfs_(i);
        }
    }
    visited[v]++;

}

void Matrix_graph::bfs() {

    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            bfs(i);
        }
    }
    for(int i = 0; i < vertices; i++){
        std::cout<<visited[i]<<"\t";
    }
    std::cout<<"\n";

}

void Matrix_graph::bfs(int v) {

    std::queue <int> queue;
    visited[v]++;
    queue.push(v);
    while(!queue.empty()){

        v = queue.front();
        queue.pop();
        for(int i = 0; i < vertices; i++){
            if(visited[i] == 0 && adj[v][i] != nullptr) {
                visited[i]++;
                queue.push(i);
            }
        }

    }
}

int Matrix_graph::acyclicity() {

    int cycles = 0;
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            find_cycle(i, -1, -1, cycles);
        }
    }
    return cycles;
}

void Matrix_graph::find_cycle(int v, int prev, int prev_prev, int &cycles) {

    if(visited[v] != 0){
        if(visited[v] == 1) {
            if (oriented || v != prev_prev) {
                cycles++;
            }
//            std::cout<< v <<"\t"<<prev<<"\t"<< cycles << "\n";
        }
        return;
    }

    visited[v]++;

    for(int i = 0; i < vertices; i++){
        if(adj[v][i] != nullptr) {
            find_cycle(i, v, prev, cycles);
        }

    }
    visited[v]++;

}

