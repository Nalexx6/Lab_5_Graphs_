//
// Created by Win10Pro on 05.05.2020.
//

#include "Matrix_graph.h"

Matrix_graph::Matrix_graph(int &vertices, bool oriented) {

    this->vertices = vertices;
    this->oriented = oriented;

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

    costs = new int* [vertices];
    for(int i = 0; i < vertices; i++){
        costs[i] = new int [vertices];
    }

    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            costs[i][j] = -1;
        }
    }
    component = new int [vertices];
    for(int i = 0; i < vertices; i++){
        component[i] = 0;
    }
};

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

    std::cout<<"   ";
    for(int i = 0; i < vertices; i++){
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
    for(int i = 0; i < vertices; i++){
        std::cout<<i<<": ";
        for(int j = 0; j < vertices; j++){
            if(adj[i][j] != nullptr)
                std::cout<<*adj[i][j]<<" ";
            else
                std::cout<<"N ";
        }
        std::cout<<"\n";
    }


}

int Matrix_graph::dfs(bool connectivity) {

    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
     int components = 0;
     for(int i = 0; i < vertices; i++){
         if(visited[i] == 0) {
             dfs_(i, connectivity);
             if(connectivity) {
                 components++;
                 for (int i = 0; i < vertices; i++) {
                     if (visited[i] != 0)
                         component[i]++;
                 }
             }
             else
                 std::cout<<"\n";
         }
     }
    return components;
}

void Matrix_graph::dfs_(int v, bool& connectivity) {

    if(visited[v] != 0)
        return;
    visited[v]++;
    if(!connectivity){
        std::cout<<v<<"->";
    }
    for(int i = 0; i < vertices; i++){
        if(adj[v][i] != nullptr){
            dfs_(i, connectivity);
        }
    }

}

void Matrix_graph::bfs() {

    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            bfs(i);
            std::cout<<"\n";
        }
    }
}

void Matrix_graph::bfs(int v) {

    std::queue <int> queue;
    visited[v]++;
    queue.push(v);
    while(!queue.empty()){

        v = queue.front();
        queue.pop();
        std::cout<<v<<"->";
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

int Matrix_graph::exist_unvisited() {

    int k = 0;
    int min = -1;
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            k++;
            min = i;
        }
    }
    return min;

}

void Matrix_graph::copy_vector(std::vector<int> &vector_1, std::vector<int> &vector_2) {

    vector_2.clear();
    for(int i = 0; i < vector_1.size(); i++){
        vector_2.emplace_back(vector_1[i]);
    }

}

std::vector<int> **Matrix_graph::dijkstra_distance() {

    std:: vector <int>** distances = new std::vector <int>* [vertices];

    for(int i = 0; i < vertices; i++){
        distances[i] = dijkstra_distance(i);
    }

    return distances;

}

std::vector<int> *Matrix_graph::dijkstra_distance(int v) {

    std::vector <int>* distances = new std::vector <int> [vertices];
    for(int i = 0; i < vertices; i++){
        distances[i] = {};
    }

    for(int i = 0; i < vertices; i++){
        if(component[i] == component[v]){
            costs[v][i] = INT32_MAX;
            visited[i] = 0;
        }
    }
    costs[v][v] = 0;

    find_distance(v, distances);
    return distances;

}

void Matrix_graph::find_distance(int v, std::vector<int> *distances) {

    while(exist_unvisited() >= 0) {
        int min = exist_unvisited();
        for (int i = 0; i < vertices; i++) {

            if ((costs[v][i] < costs[v][min] && visited[i] == 0) || (i == v && visited[v] == 0)) {
                min = i;
            }

        }
        visited[min]++;
        for (int i = 0; i < vertices; i++) {
            if (adj[min][i] != nullptr){
                if((costs[v][i] > costs[v][min] + *adj[min][i]) &&
                visited[i] == 0) {

                costs[v][i] = costs[v][min] + *adj[min][i];
                copy_vector(distances[min], distances[i]);
                distances[i].emplace_back(min);

                }
            }
        }
    }

}

void Matrix_graph::top_sort() {

    sorted = new int [vertices];
    for(int i = 0; i < vertices; i++){
        sorted[i] = 0;
        visited[i] = 0;
    }
    int index = vertices - 1;
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            sort(i, index);
        }
    }

}

void Matrix_graph::sort(int v, int &index) {

    if(visited[v] != 0)
        return;
    visited[v]++;
    for(int i = 0; i < vertices; i++){
        if(adj[v][i] != nullptr) {
            sort(i, index);
        }

    }
    visited[v]++;
    sorted[index] = v;
    index--;

}

Matrix_graph *Matrix_graph::span_tree() {

    Matrix_graph* spanning_tree = new Matrix_graph(vertices, oriented);
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    span_tree(0, spanning_tree);
//    spanning_tree->output_graph();
    return spanning_tree;

}

void Matrix_graph::span_tree(int v, Matrix_graph *spanning_tree) {

    visited[v]++;
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0 && adj[v][i] != nullptr) {
            spanning_tree->add_edge(v, i, adj[v][i]);
            span_tree(i, spanning_tree);
        }
    }

}

int Matrix_graph::sum_weight() {

    int sum = 0;
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            if(adj[i][j] != nullptr)
                sum += *adj[i][j];
        }
    }
    if(!oriented)
        sum /= 2;
    return sum;

}
void Matrix_graph::merge_sort(std::vector <Span_edge>& array) {

    std::vector <Span_edge> for_merge {};
    for(int i = 0; i < array.size(); i++){
        for_merge.emplace_back(array[i]);
    }
    sort(array, for_merge, 0, array.size() - 1);

}

void Matrix_graph::merge(std::vector <Span_edge>& array, std::vector <Span_edge>& for_merge, int lo, int mid, int hi) {

    for(int i = lo; i < hi + 1; i++){
        for_merge[i] = array[i];
    }
    int i = lo, j = mid + 1;
    for(int k = lo; k < hi + 1; k++){
        if(i > mid){
            array[k] = for_merge[j];
            j++;
        } else if(j > hi){
            array[k] = for_merge[i];
            i++;
        } else if(for_merge[i].weight > for_merge[j].weight){
            array[k] = for_merge[j];
            j++;
        } else{
            array[k] = for_merge[i];
            i++;
        }

    }
}

void Matrix_graph::sort(std::vector <Span_edge>& array, std::vector <Span_edge>& for_merge, int lo, int hi) {

    if(hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    sort(array, for_merge, lo, mid);
    sort(array, for_merge, mid + 1, hi);
    merge(array, for_merge, lo ,mid, hi);

}

Matrix_graph *Matrix_graph::prim_spanning_tree() {

    edges = {};
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            if(adj[i][j] != nullptr) {
                edges.emplace_back(Span_edge(i, j, *adj[i][j]));
            }
        }
    }
    merge_sort(edges);
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    Matrix_graph* min_span_tree = new Matrix_graph(vertices, oriented);
    int* weight = new int(edges[0].weight);
    min_span_tree->add_edge(edges[0].v,edges[0].w, weight);
    visited[edges[0].v]++;
    visited[edges[0].w]++;
    while(exist_unvisited() != -1){
        for(int i = 1; i < edges.size(); i++){
            if((visited[edges[i].v] != 0 && visited[edges[i].w] == 0) || (visited[edges[i].w] != 0 && visited[edges[i].v] == 0)){
                weight = new int(edges[i].weight);
                min_span_tree->add_edge(edges[i].v,edges[i].w, weight);
                visited[edges[i].v]++;
                visited[edges[i].w]++;
                break;
            }
        }
    }
    return min_span_tree;
}
