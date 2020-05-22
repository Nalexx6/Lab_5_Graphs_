//
// Created by Win10Pro on 05.05.2020.
//

#include "List_graph.h"

List_graph::List_graph(int &vertices, bool oriented) {

    this->vertices = vertices;
    this->oriented = oriented;

    adj = new std::vector <Edge> [vertices];

    visited = new int [vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
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

    component= new int [vertices];
    for(int i = 0; i < vertices; i++){
        component[i] = 0;
    }

    sorted = new int [vertices];

}

List_graph::~List_graph() = default;

bool List_graph::edge_exists(int v, int w) {

    for(int i = 0; i < adj[v].size(); i++){
        if(adj[v][i].vertex == w){
            return true;
        }
    }
    return false;
}

void List_graph::add_edge(unsigned int v, unsigned int w, int weight) {


    if(edge_exists(v, w)){
        return;
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
            std::cout<<adj[i][j].vertex<<"("<<adj[i][j].weight<<")"<<"\t";
        }
        std::cout<<"\n";
    }

}

int List_graph::dfs(bool connectivity) {

    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    int components = 0;
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0) {
            dfs_1(i, connectivity);
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

void List_graph::dfs_1(int v, bool& connectivity) {

    if(visited[v] != 0)
        return;
    visited[v]++;
    if(!connectivity){
        std::cout<<v<<"->";
    }
    for(int i = 0; i < adj[v].size(); i++){
            dfs_1(adj[v][i].vertex, connectivity);

    }
    visited[v]++;

}


void List_graph::bfs(bool benchmark) {

    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            bfs(i, benchmark);
            if(!benchmark)
                std::cout<<"\n";
        }
    }


}

void List_graph::bfs(int v, bool benchmark) {

    std::queue <int> queue;
    visited[v]++;
    queue.push(v);
    while(!queue.empty()){

        v = queue.front();
        queue.pop();
        if(!benchmark)
            std::cout<<v<<"->";
        for(int i = 0; i < adj[v].size(); i++){
            if(visited[adj[v][i].vertex] == 0) {
                visited[adj[v][i].vertex]++;
                queue.push(adj[v][i].vertex);
            }
        }

    }

}

int List_graph::acyclicity() {
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    int cycles = 0;
    for(int i = 0; i < vertices; i++){
        if(visited[i] == 0){
            find_cycle(i, -1, -1, cycles);
        }
    }

    return cycles;

}

void List_graph::find_cycle(int v, int prev, int prev_prev, int& cycles) {

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
    for(int i = 0; i < adj[v].size(); i++){
        find_cycle(adj[v][i].vertex, v , prev,cycles);

    }
    visited[v]++;

}

std::vector <int>** List_graph::dijkstra_distance() {

    std:: vector <int>** distances = new std::vector <int>* [vertices];

    for(int i = 0; i < vertices; i++){
        distances[i] = dijkstra_distance(i);
    }

    return distances;

}

std::vector <int>* List_graph::dijkstra_distance(int v) {


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

int List_graph::exist_unvisited() {

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

void List_graph::copy_vector(std::vector<int>& vector_1, std::vector <int>& vector_2) {

    vector_2.clear();
    for(int i = 0; i < vector_1.size(); i++){
        vector_2.emplace_back(vector_1[i]);
    }
}

void List_graph::find_distance(int v, std::vector <int>* distances) {

    while(exist_unvisited() >= 0) {
        int min = exist_unvisited();
        for (int i = 0; i < vertices; i++) {

            if ((costs[v][i] < costs[v][min] && visited[i] == 0) || (i == v && visited[v] == 0)) {
                min = i;
            }

        }
        visited[min]++;
        for (int i = 0; i < adj[min].size(); i++) {
            if ((costs[v][adj[min][i].vertex] > costs[v][min] + adj[min][i].weight) &&
                visited[adj[min][i].vertex] == 0) {

                costs[v][adj[min][i].vertex] = costs[v][min] + adj[min][i].weight;
                copy_vector(distances[min], distances[adj[min][i].vertex]);
                distances[adj[min][i].vertex].emplace_back(min);

            }
        }
    }

}

void List_graph::top_sort() {

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

void List_graph::sort(int v, int &index) {

    if(visited[v] != 0)
        return;
    visited[v]++;
    for(int i = 0; i < adj[v].size(); i++){
        sort(adj[v][i].vertex, index);

    }
    visited[v]++;
    sorted[index] = v;
    index--;

}

List_graph *List_graph::span_tree() {

    List_graph* spanning_tree = new List_graph(vertices, oriented);
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }
    span_tree(0, spanning_tree);
//    spanning_tree->output_graph();
    return spanning_tree;

}

void List_graph::span_tree(int v, List_graph *spanning_tree) {

    visited[v]++;
    for(int i = 0; i < adj[v].size(); i++){
        if(visited[adj[v][i].vertex] == 0) {
            spanning_tree->add_edge(v, adj[v][i].vertex, adj[v][i].weight);
            span_tree(adj[v][i].vertex, spanning_tree);
        }
    }
}

int List_graph::sum_weight() {
    int sum = 0;
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < adj[i].size(); j++){
            sum+=adj[i][j].weight;
        }
    }
    if(!oriented)
        sum /= 2;
    return sum;
}

void List_graph::merge_sort(std::vector <Span_edge>& array) {

    std::vector <Span_edge> for_merge {};
    for(int i = 0; i < array.size(); i++){
        for_merge.emplace_back(array[i]);
    }
    sort(array, for_merge, 0, array.size() - 1);
    for_merge.clear();

}

void List_graph::merge(std::vector <Span_edge>& array, std::vector <Span_edge>& for_merge, int lo, int mid, int hi) {

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

void List_graph::sort(std::vector <Span_edge>& array, std::vector <Span_edge>& for_merge, int lo, int hi) {

    if(hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    sort(array, for_merge, lo, mid);
    sort(array, for_merge, mid + 1, hi);
    merge(array, for_merge, lo ,mid, hi);

}

List_graph *List_graph::prim_spanning_tree() {

    edges = {};
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < adj[i].size(); j++){
            edges.emplace_back(Span_edge(i, adj[i][j].vertex, adj[i][j].weight));
        }
    }
    merge_sort(edges);
    for(int i = 0; i < vertices; i++){
        visited[i] = 0;
    }

    List_graph* min_span_tree = new List_graph(vertices, oriented);
    min_span_tree->add_edge(edges[0].v,edges[0].w, edges[0].weight);
    visited[edges[0].v]++;
    visited[edges[0].w]++;
    while(exist_unvisited() != -1){
        for(int i = 1; i < edges.size(); i++){
            if((visited[edges[i].v] != 0 && visited[edges[i].w] == 0) || (visited[edges[i].w] != 0 && visited[edges[i].v] == 0)){
                min_span_tree->add_edge(edges[i].v,edges[i].w, edges[i].weight);
                visited[edges[i].v]++;
                visited[edges[i].w]++;
                break;
            }
        }
    }
    edges.clear();
    return min_span_tree;
}

void List_graph::destroy_graph() {

    delete[] sorted;
    for(int i = 0; i < vertices; i++) {
        delete[] costs[i];
    }
    delete[] costs;
    delete[] component;
    delete[] visited;
    for(int i = 0; i < vertices; i++) {
//        for(int j = 0; j < vertices; j++) {
//            delete adj[i][j];
//        }
        adj[i].clear();
    }
    delete[] adj;

}
