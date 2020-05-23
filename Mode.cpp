//
// Created by Win10Pro on 05.05.2020.
//

#include "Mode.h"

void Mode::interactive() {

    char response = 'y';
    while(response == 'y') {

        std::cout<<"Hello, please choose the structure\n"
                   "1 - Matrix\n"
                   "2 - List\n";
        int key;
        std::cin>>key;
        if(key == 1)
            Functions::matrix_interactive();
        if(key == 2)
            Functions::list_interactive();

        std::cout<<"If you want to execute interactive for another type of graph press 'y', press 'n', if you don`t\n";
        std::cin>>response;

    }
}

void Mode::demo() {

    char response = 'y';
    while(response == 'y') {

        std::cout<<"Hello, please choose the structure\n"
                   "1 - Matrix\n"
                   "2 - List\n";
        int key;
        std::cin>>key;
        if(key == 1)
            Functions::matrix_demo();
        if(key == 2)
            Functions::list_demo();

        std::cout<<"If you want to execute demo for another type of graph press 'y', press 'n', if you don`t\n";
        std::cin>>response;

    }

}

void Mode::benchmark() {

    std::ofstream f("../Files/Benchmark data.txt", std::ios::trunc);
    List_graph *listGraph;
    Matrix_graph *matrixGraph;

    std::string breakpoint;
    std::cout<<"Firstly we will execute benchmark for complete graph\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;
    f << "-------------------------DATA FOR COMPLETE GRAPH-------------------\n";

    for(int N = 32; N <= 2048; N *= 4){

        f << "-----------------Data for "<< N <<" vertices---------\n";

        std::cout<<"\nCreating graphs for "<< N<<" vertices...\n";
//        clock_t start, end;
        matrixGraph = Functions::matrix_random_graph(N, (N - 1) * N / 2, false);

        listGraph = Functions::matrix_to_lst(matrixGraph);

        std::cout<<"Processing List_graph algorithms...\n";
        f<<"\nList\n";
        Functions::list_benchmark(listGraph, f);
        listGraph->destroy_graph();

        std::cout<<"Processing Matrix_graph algorithms...\n";
        f << "\nMatrix\n";
        Functions::matrix_benchmark(matrixGraph, f);
        matrixGraph->destroy_graph();

    }

    f << "\n-------------------------DATA FOR SPARSE GRAPH-------------------\n";

    std::cout<<"\nNow we will execute benchmark for sparse (E = 10 * V) graph\n"
               "cin anything to continue\n";
    std::cin>>breakpoint;

    for(int N = 64; N <= 4096; N *= 4){

        f << "-----------------Data for "<< N <<" vertices---------\n";

        std::cout<<"\nCreating graphs for "<< N<<" vertices...\n";
        listGraph = Functions::list_random_graph(N, 10 * N , false);

        matrixGraph = Functions::list_to_matrix(listGraph);

        std::cout<<"Processing List_graph algorithms...\n";
        f<<"\nList\n";
        Functions::list_benchmark(listGraph, f);
        listGraph->destroy_graph();

        std::cout<<"Processing Matrix_graph algorithms...\n";
        f << "\nMatrix\n";
        Functions::matrix_benchmark(matrixGraph, f);
        matrixGraph->destroy_graph();

    }
    f.close();

    std::cout<<"\nResults of benchmark are accessible in Benchmark data.txt\n";


}
