//
// Created by Win10Pro on 05.05.2020.
//

#include "Functions.h"

Matrix_graph* Functions::matrix_random_graph(int vertices, int edges, bool oriented) {

    Matrix_graph* graph = new Matrix_graph(vertices, oriented);

    for(int i = 0; i < edges; i++) {
        if(i == vertices * (vertices - 1) / 2 + 1) {
            std::cout << "There are no possible edges ot add - graph is full\n";
            break;
        }
        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        int* weight = new int(Random::rand(vertices - 1 ,  2 * vertices - 1));
        if(graph->edge_exists(v, w) || v == w){
            i--;
        } else {
            graph->add_edge(v, w, weight);
        }
    }
    return graph;
}

List_graph* Functions::list_random_graph(int vertices, int edges, bool oriented) {

    List_graph* graph = new List_graph(vertices, oriented);

    for(int i = 0; i < edges; i++) {
        unsigned v = Random::rand(0, vertices - 1);
        unsigned w = Random::rand(0, vertices - 1);
        int weight = Random::rand(0 ,  2 * vertices - 1);
        if(graph->edge_exists(v , w) || v == w){
            i--;
        } else {
            graph->add_edge(v, w, weight);
        }
    }
    return graph;
}

List_graph *Functions::matrix_to_lst(Matrix_graph *graph) {

    List_graph* listGraph = new List_graph(graph->vertices, graph->oriented);

    for(int i = 0; i < graph->vertices; i++){
        for(int j = 0; j < graph->vertices; j++){
            if(graph->edge_exists(i,j)){
                listGraph->add_edge(i, j, *graph->adj[i][j]);
            }
        }
    }
//    listGraph->output_graph();
    return listGraph;
}

Matrix_graph *Functions::list_to_matrix(List_graph *graph) {

    Matrix_graph* matrixGraph = new Matrix_graph(graph->vertices, graph->oriented);

    int* weight;
    for(int i = 0; i < graph->vertices; i++){
        for(int j = 0; j < graph->adj[i].size(); j++){

            weight = new int(graph->adj[i][j].weight);
            matrixGraph->add_edge(i, graph->adj[i][j].vertex, weight);

        }
    }
//    matrixGraph->output_graph();
    return matrixGraph;
}

void Functions::matrix_interactive() {

    Matrix_graph* graph = matrix_random_graph(1, 0, false);
    char response = 'y';
    while(response == 'y') {

        std::cout<<"Hello, please choose the choose what you want to do with your graph:\n"
                   "1 - Create NEW random graph with adjusted quantity of vertices and edges\n"
                   "2 - Add edge to graph\n"
                   "3 - Output graph\n"
                   "4 - Go round our graph using DFS\n"
                   "5 - Go round our graph using BFS\n"
                   "6 - Find amount of connectivity components in graph\n"
                   "7 - Find amount of cycles in graph\n"
                   "8 - Find lowest-cost path from one vertex to another\n"
                   "9 - Find lowest-cost path from one vertex to all other vertices\n"
                   "10 - Find lowest-cost path between all vertices\n"
                   "11 - Sort vertices in your graph topologically\n"
                   "12 - Build spanning tree(based on dfs algorithm)\n"
                   "13 - Build minimum spanning tree(Prim algorithm)\n";
        int key;
        std::cin>>key;
        if(key == 1){
            int vertices, edges;
            char ori;
            bool oriented;
            std::cout<<"Please enter the number of vertices in your graph\n";
            std::cin>>vertices;
            std::cout<<"Please enter the number of edges\n";
            std::cin>>edges;
            std::cout<<"Enter 'y', if your graph is oriented, or 'n' if not\n";
            std::cin>>ori;
            oriented = ori == 'y';
            graph = matrix_random_graph(vertices, edges, oriented);
            std::cout<<"This is your graph\n";
            graph->output_graph();
        }
        if(key == 2){
            int v, w, weight;
            std::cout<<"Please enter v and w - first and second vertex of your edge\n";
            std::cin>>v>>w;
            std::cout<<"Please enter weight of your edge (>=0)";
            std::cin>>weight;
            int* weight_p = new int (weight);
            graph->add_edge(v, w, weight_p);

        }
        if(key == 3){
            std::cout<<"This is your graph(number is weight if edge exists, N - if not)\n";
            graph->output_graph();
        }
        if(key == 4){
            std::cout<<"This is order in which DFS go through all vertices\n";
            graph->dfs(false);
        }
        if(key == 5){
            std::cout<<"This is order in which BFS go through all vertices\n";
            graph->bfs(false);
        }
        if(key == 6){
            std::cout<<"Your graph has "<<graph->dfs(true)<<" connectivity components\n";
        }
        if(key == 7){
            int cycles = graph->acyclicity();
            if(cycles == 0)
                std::cout<<"Your graph is acyclic\n";
            else
                std::cout<<"Your graph has "<<cycles<<" cycles\n";
        }
        if(key == 8){
            int v, w;
            graph->dfs(true);
            std::cout<<"Please enter v, w - vertices for which you want to find path\n";
            std::cin>>v>>w;
            std::vector<int> path = graph->dijkstra_distance(v)[w];
            std::cout<<"Cost: "<<graph->costs[v][w]<<"\n";
            std::cout<<"Path: ";
            if(path.empty() && w != v){
                std::cout<<"No path - this vertex is in another connectivity component\n";
            }
            else{
            for(int i = 0; i < path.size(); i++){
                std::cout<<path[i]<<"->";

            }
            std::cout<<w<<"\n";
            }
        }
        if(key == 9){
            graph->dfs(true);
            int v;
            std::cout<<"Please enter v - vertex for which you want to find paths\n";
            std::cin>>v;
            std::vector<int>* path = graph->dijkstra_distance(v);
            for(int j = 0; j < graph->vertices; j++) {
                std::cout <<"Vertex: "<<j<< "\tCost: " << graph->costs[v][j] << "\n";
                std::cout << "Path: ";
                if(path[j].empty() && j != v){
                    std::cout<<"No path - this vertex is in another connectivity component\n";
                }
                else {
                    for (int i = 0; i < path[j].size(); i++) {
                        std::cout << path[j][i] << "->";

                    }
                    std::cout << j << "\n";
                }
            }
        }
        if(key == 10){
            graph->dfs(true);
            graph->dijkstra_distance();
            std::cout<<" ";
            for(int i = 0 ; i < graph->vertices; i++){
                std::cout<<i<<"\t";
            }
            std::cout<<"\n";
            for(int i = 0; i < graph->vertices; i++){
                std::cout<<i<<": ";
                for(int j = 0; j < graph->vertices; j++){
                    std::cout<<graph->costs[i][j]<<"\t";
                }
                std::cout<<"\n";
            }
        }
        if(key == 11){
            if(graph->acyclicity() != 0){
                std::cout<<"Your graph has cycles - sorting is impossible\n";
            } else if(!graph->oriented){
                std::cout<<"Your graph is unoriented - sorting is impossible\n";
            } else{
                graph->top_sort();
                for(int i = 0; i < graph->vertices; i++){
                    std::cout<<graph->sorted[i]<<"\t";
                }
                std::cout<<"\n";
            }
        }
        if(key == 12){
            if(graph->dfs(true) != 1){
                std::cout<<"Your graph has more than one connectivity components - building is impossible\n";
            } else if(graph->oriented){
                std::cout<<"This algorithm works only for unoriented graphs\n";
            } else{
                std::cout<<"This is our spanning tree\n";
                Matrix_graph* span_tree = graph->span_tree();
                span_tree->output_graph();
                std::cout<<"Summarized weight of our tree = "<<span_tree->sum_weight()<<"\n";
            }
        }
        if(key == 13){
            if(graph->dfs(true) != 1){
                std::cout<<"Your graph has more than one connectivity components - building is impossible\n";
            } else if(graph->oriented){
                std::cout<<"This algorithm works only for unoriented graphs\n";
            } else{
                std::cout<<"This is our minimum spanning tree\n";
                Matrix_graph* min_span_tree = graph->prim_spanning_tree();
                min_span_tree->output_graph();
                std::cout<<"Summarized weight of our tree = "<<min_span_tree->sum_weight()<<"\n";
            }
        }
        std::cout<<"If you want to do anything else with graph press 'y', press 'n', if you don`t\n";
        std::cin>>response;

    }
    graph->destroy_graph();
    delete graph;

}

void Functions::list_interactive() {

    List_graph* graph = list_random_graph(1, 0, false);
    char response = 'y';
    while(response == 'y') {

        std::cout<<"Hello, please choose the choose what you want to do with your graph:\n"
                   "1 - Create NEW random graph with adjusted quantity of vertices and edges\n"
                   "2 - Add edge to graph\n"
                   "3 - Output graph\n"
                   "4 - Go round our graph using DFS\n"
                   "5 - Go round our graph using BFS\n"
                   "6 - Find amount of connectivity components in graph\n"
                   "7 - Find amount of cycles in graph\n"
                   "8 - Find lowest-cost path from one vertex to another\n"
                   "9 - Find lowest-cost path from one vertex to all other vertices\n"
                   "10 - Find lowest-cost path between all vertices\n"
                   "11 - Sort vertices in your graph topologically\n"
                   "12 - Build spanning tree(based on dfs algorithm)\n"
                   "13 - Build minimum spanning tree(Prim algorithm)\n";
        int key;
        std::cin>>key;
        if(key == 1){
            int vertices, edges;
            char ori;
            bool oriented;
            std::cout<<"Please enter the number of vertices in your graph\n";
            std::cin>>vertices;
            std::cout<<"Please enter the number of edges\n";
            std::cin>>edges;
            std::cout<<"Enter 'y', if your graph is oriented, or 'n' if not\n";
            std::cin>>ori;
            oriented = ori == 'y';
            graph = list_random_graph(vertices, edges, oriented);
            std::cout<<"This is your graph\n";
            graph->output_graph();
        }
        if(key == 2){
            int v, w, weight;
            std::cout<<"Please enter v and w - first and second vertex of your edge\n";
            std::cin>>v>>w;
            std::cout<<"Please enter weight of your edge (>=0)";
            std::cin>>weight;
            graph->add_edge(v, w, weight);

        }
        if(key == 3){
            std::cout<<"This is your graph(weight of edge is in parentheses)\n";
            graph->output_graph();
        }
        if(key == 4){
            std::cout<<"This is order in which DFS go through all vertices\n";
            graph->dfs(false);
        }
        if(key == 5){
            std::cout<<"This is order in which BFS go through all vertices\n";
            graph->bfs(false);
        }
        if(key == 6){
            std::cout<<"Your graph has "<<graph->dfs(true)<<" connectivity components\n";
        }
        if(key == 7){
            int cycles = graph->acyclicity();
            if(cycles == 0)
                std::cout<<"Your graph is acyclic\n";
            else
                std::cout<<"Your graph has "<<cycles<<" cycles\n";
        }
        if(key == 8){
            int v, w;
            graph->dfs(true);
            std::cout<<"Please enter v, w - vertices for which you want to find path\n";
            std::cin>>v>>w;
            std::vector<int> path = graph->dijkstra_distance(v)[w];
            std::cout<<"Cost: "<<graph->costs[v][w]<<"\n";
            std::cout<<"Path: ";
            if(path.empty() && w != v){
                std::cout<<"No path - this vertex is in another connectivity component\n";
            }
            else{
                for(int i = 0; i < path.size(); i++){
                    std::cout<<path[i]<<"->";

                }
                std::cout<<w<<"\n";
            }
        }
        if(key == 9){
            graph->dfs(true);
            int v;
            std::cout<<"Please enter v - vertex for which you want to find paths\n";
            std::cin>>v;
            std::vector<int>* path = graph->dijkstra_distance(v);
            for(int j = 0; j < graph->vertices; j++) {
                std::cout <<"Vertex: "<<j<< "\tCost: " << graph->costs[v][j] << "\n";
                std::cout << "Path: ";
                if(path[j].empty() && j != v){
                    std::cout<<"No path - this vertex is in another connectivity component\n";
                }
                else {
                    for (int i = 0; i < path[j].size(); i++) {
                        std::cout << path[j][i] << "->";

                    }
                    std::cout << j << "\n";
                }
            }
        }
        if(key == 10){
            graph->dfs(true);
            graph->dijkstra_distance();
            std::cout<<" ";
            for(int i = 0 ; i < graph->vertices; i++){
                std::cout<<i<<"\t";
            }
            std::cout<<"\n";
            for(int i = 0; i < graph->vertices; i++){
                std::cout<<i<<": ";
                for(int j = 0; j < graph->vertices; j++){
                    std::cout<<graph->costs[i][j]<<"\t";
                }
                std::cout<<"\n";
            }
        }
        if(key == 11){
            if(graph->acyclicity() != 0){
                std::cout<<"Your graph has cycles - sorting is impossible\n";
            } else if(!graph->oriented){
                std::cout<<"Your graph is unoriented - sorting is impossible\n";
            } else{
                graph->top_sort();
                for(int i = 0; i < graph->vertices; i++){
                    std::cout<<graph->sorted[i]<<"\t";
                }
                std::cout<<"\n";
            }
        }
        if(key == 12){
            if(graph->dfs(true) != 1){
                std::cout<<"Your graph has more than one connectivity components - building is impossible\n";
            } else if(graph->oriented){
                std::cout<<"This algorithm works only for unoriented graphs\n";
            } else{
                std::cout<<"This is our spanning tree\n";
                List_graph* span_tree = graph->span_tree();
                span_tree->output_graph();
                std::cout<<"Summarized weight of our tree = "<<span_tree->sum_weight()<<"\n";
            }
        }
        if(key == 13){
            if(graph->dfs(true) != 1){
                std::cout<<"Your graph has more than one connectivity components - building is impossible\n";
            } else if(graph->oriented){
                std::cout<<"This algorithm works only for unoriented graphs\n";
            } else{
                std::cout<<"This is our minimum spanning tree\n";
                List_graph* min_span_tree = graph->prim_spanning_tree();
                min_span_tree->output_graph();
                std::cout<<"Summarized weight of our tree = "<<min_span_tree->sum_weight()<<"\n";
            }
        }
        std::cout<<"If you want to do anything else with graph press 'y', press 'n', if you don`t\n";
        std::cin>>response;
    }
    graph->destroy_graph();
    delete graph;

}

void Functions::matrix_demo() {

    std::string breakpoint;
    int vertices = 5, edges = 7, v = 2;
    bool oriented = false;
    Matrix_graph* graph = new Matrix_graph(vertices, oriented);
    std::cout<<"Firstly we will create oriented graph with "<<vertices<<" vertices and "<<edges<<" edges\n"
                "cin anything to continue\n";
    std::cin>>breakpoint;
//    graph = matrix_random_graph(vertices, edges, oriented);
    int* weight = new int(2);
    graph->add_edge(0, 1, weight);
    weight = new int(5);
    graph->add_edge(3, 1, weight);
    weight = new int(3);
    graph->add_edge(4, 3, weight);
    weight = new int(8);
    graph->add_edge(4, 2, weight);
    weight = new int(7);
    graph->add_edge(0, 4, weight);
    weight = new int(1);
    graph->add_edge(3, 0, weight);
    weight = new int(4);
    graph->add_edge(1, 2, weight);

    graph->output_graph();
    std::cout<<"This is your graph(number is weight if edge exists, N - if not)\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    std::cout<<"Your graph has "<<graph->dfs(true)<<" connectivity components\n"
                "cin anything to continue\n";
    std::cin>>breakpoint;
    int cycles = graph->acyclicity();
    if(cycles == 0)
        std::cout<<"Your graph is acyclic\n";
    else
        std::cout<<"Your graph has "<<cycles<<" cycles\n";
    std::cout<<"cin anything to continue\n";
    std::cin>>breakpoint;


    graph->dfs(false);
    std::cout<<"This is order in which DFS go through all vertices\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    graph->bfs(false);
    std::cout<<"This is order in which BFS go through all vertices\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    std::vector<int>* path = graph->dijkstra_distance(v);
    for(int j = 0; j < graph->vertices; j++) {
        std::cout <<"Vertex: "<<j<< "\tCost: " << graph->costs[v][j] << "\n";
        std::cout << "Path: ";
        if(path[j].empty() && j != v){
            std::cout<<"No path - this vertex is in another connectivity component\n";
        }
        else {
            for (int i = 0; i < path[j].size(); i++) {
                std::cout << path[j][i] << "->";

            }
            std::cout << j << "\n";
        }
    }
    std::cout<<"This is lowest-cost paths from vertex" <<v<<" to all other vertices\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;


    graph->dfs(true);
    graph->dijkstra_distance();
    std::cout<<" ";
    for(int i = 0 ; i < graph->vertices; i++){
        std::cout<<i<<"\t";
    }
    std::cout<<"\n";
    for(int i = 0; i < graph->vertices; i++){
        std::cout<<i<<": ";
        for(int j = 0; j < graph->vertices; j++){
            std::cout<<graph->costs[i][j]<<"\t";
        }
        std::cout<<"\n";
    }
    std::cout<<"This is lowest-cost paths between all vertices\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    Matrix_graph* span_tree = graph->span_tree();
    span_tree->output_graph();
    std::cout<<"Summarized weight of our tree = "<<span_tree->sum_weight()<<"\n";
    std::cout<<"This is our spanning tree(DFS algorithm)\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    Matrix_graph* min_span_tree = graph->prim_spanning_tree();
    min_span_tree->output_graph();
    std::cout<<"Summarized weight of our tree = "<<min_span_tree->sum_weight()<<"\n";
    std::cout<<"This is our minimum spanning tree(Prim algorithm)\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    std::cout<<"To execute topological sort our graph need to be oriented, so we need build new graph with the same\n"
               "amount of vertices and 4 edges to avoid cycles, but oriented\n";
    graph = matrix_random_graph(vertices, 4, oriented);
    graph->output_graph();
    std::cout<<"This is our new graph\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;
    graph->top_sort();
    for(int i = 0; i < graph->vertices; i++){
        std::cout<<graph->sorted[i]<<"\t";
    }
    std::cout<<"\n";
    std::cout<<"This is result of topological sorting of your graph\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    std::cout<<"This is the end of demo mode\n";

    graph->destroy_graph();
    delete graph;





}

void Functions::list_demo() {

    std::string breakpoint;
    int vertices = 5, edges = 7, v = 2;
    bool oriented = false;
    List_graph* graph = new List_graph(vertices, oriented);
    std::cout<<"Firstly we will create oriented graph with "<<vertices<<" vertices and "<<edges<<" edges\n"
                                                                                                 "cin anything to continue\n";
    std::cin>>breakpoint;
//    graph = matrix_random_graph(vertices, edges, oriented);
    graph->add_edge(0, 1, 2);

    graph->add_edge(3, 1, 5);
    graph->add_edge(4, 3, 3);
    graph->add_edge(4, 2,8);
    graph->add_edge(0, 4, 7);
    graph->add_edge(3, 0, 1);
    graph->add_edge(1, 2, 4);

    graph->output_graph();
    std::cout<<"This is your graph(weight of edge is in parentheses)\n"
                "cin anything to continue\n";
    std::cin>>breakpoint;

    std::cout<<"Your graph has "<<graph->dfs(true)<<" connectivity components\n"
                                                    "cin anything to continue\n";
    std::cin>>breakpoint;
    int cycles = graph->acyclicity();
    if(cycles == 0)
        std::cout<<"Your graph is acyclic\n";
    else
        std::cout<<"Your graph has "<<cycles<<" cycles\n";
    std::cout<<"cin anything to continue\n";
    std::cin>>breakpoint;


    graph->dfs(false);
    std::cout<<"This is order in which DFS go through all vertices\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    graph->bfs(false);
    std::cout<<"This is order in which BFS go through all vertices\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    std::vector<int>* path = graph->dijkstra_distance(v);
    for(int j = 0; j < graph->vertices; j++) {
        std::cout <<"Vertex: "<<j<< "\tCost: " << graph->costs[v][j] << "\n";
        std::cout << "Path: ";
        if(path[j].empty() && j != v){
            std::cout<<"No path - this vertex is in another connectivity component\n";
        }
        else {
            for (int i = 0; i < path[j].size(); i++) {
                std::cout << path[j][i] << "->";

            }
            std::cout << j << "\n";
        }
    }
    std::cout<<"This is lowest-cost paths from vertex" <<v<<" to all other vertices\n"
                                                            "cin anything to continue\n";
    std::cin>>breakpoint;


    graph->dfs(true);
    graph->dijkstra_distance();
    std::cout<<" ";
    for(int i = 0 ; i < graph->vertices; i++){
        std::cout<<i<<"\t";
    }
    std::cout<<"\n";
    for(int i = 0; i < graph->vertices; i++){
        std::cout<<i<<": ";
        for(int j = 0; j < graph->vertices; j++){
            std::cout<<graph->costs[i][j]<<"\t";
        }
        std::cout<<"\n";
    }
    std::cout<<"This is lowest-cost paths between all vertices\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    List_graph* span_tree = graph->span_tree();
    span_tree->output_graph();
    std::cout<<"Summarized weight of our tree = "<<span_tree->sum_weight()<<"\n";
    std::cout<<"This is our spanning tree(DFS algorithm)\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    List_graph* min_span_tree = graph->prim_spanning_tree();
    min_span_tree->output_graph();
    std::cout<<"Summarized weight of our tree = "<<min_span_tree->sum_weight()<<"\n";
    std::cout<<"This is our minimum spanning tree(Prim algorithm)\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    std::cout<<"To execute topological sort our graph need to be oriented, so we need build new graph with the same\n"
               "amount of vertices and 4 edges to avoid cycles, but oriented\n";
    graph = list_random_graph(vertices, 4, oriented);
    graph->output_graph();
    std::cout<<"This is our new graph\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;
    graph->top_sort();
    for(int i = 0; i < graph->vertices; i++){
        std::cout<<graph->sorted[i]<<"\t";
    }
    std::cout<<"\n";
    std::cout<<"This is result of topological sorting of your graph\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    std::cout<<"This is the end of demo mode\n";

    graph->destroy_graph();
    delete graph;
}

void Functions::matrix_benchmark(Matrix_graph *graph, std::ofstream &f) {

    clock_t start, end;
    std::vector <int>* distances;
    Matrix_graph* span_tree;

    start = clock();
    graph->dfs(true);
    end = clock();
    f <<"DFS: "<<end-start<<" ms\n";

    start = clock();
    graph->bfs(true);
    end = clock();
    f <<"BFS: "<<end-start<<" ms\n";

    start = clock();
    graph->acyclicity();
    end = clock();
    f <<"Find cycles: "<<end-start<<" ms\n";

    start = clock();
    distances = graph->dijkstra_distance(0);
    end = clock();
    f <<"Find lowest-cost distances: "<<end-start<<" ms\n";
    for(int i = 0; i < graph->vertices; i++){
        distances[i].clear();
    }
    delete[] distances;

    start = clock();
    span_tree = graph->span_tree();
    end = clock();
    f <<"Building span tree: "<<end-start<<" ms\n";
    span_tree->destroy_graph();

    start = clock();
    span_tree = graph->prim_spanning_tree();
    end = clock();
    f <<"Building minimum span tree: "<<end-start<<" ms\n";
    span_tree->destroy_graph();


}

void Functions::list_benchmark(List_graph *graph, std::ofstream &f) {

    clock_t start, end;
    std::vector <int>* distances;
    List_graph* span_tree;

    start = clock();
    graph->dfs(true);
    end = clock();
    f <<"DFS: "<<end-start<<" ms\n";

    start = clock();
    graph->bfs(true);
    end = clock();
    f <<"BFS: "<<end-start<<" ms\n";

    start = clock();
    graph->acyclicity();
    end = clock();
    f <<"Find cycles: "<<end-start<<" ms\n";

    start = clock();
    distances = graph->dijkstra_distance(0);
    end = clock();
    f <<"Find lowest-cost distances: "<<end-start<<" ms\n";
    for(int i = 0; i < graph->vertices; i++){
        distances[i].clear();
    }
    delete[] distances;

    start = clock();
    span_tree = graph->span_tree();
    end = clock();
    f <<"Building span tree: "<<end-start<<" ms\n";
    span_tree->destroy_graph();

    start = clock();
    span_tree = graph->prim_spanning_tree();
    end = clock();
    f <<"Building minimum span tree: "<<end-start<<" ms\n";
    span_tree->destroy_graph();

}
