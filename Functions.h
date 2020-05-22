//
// Created by Win10Pro on 05.05.2020.
//

#ifndef LAB_5_GRAPHS__FUNCTIONS_H
#define LAB_5_GRAPHS__FUNCTIONS_H

#include "Matrix_graph.h"
#include "List_graph.h"
#include "Random.h"

#include <ctime>
#include <fstream>


class Functions {

public:

    //Auxiliary
    static Matrix_graph* matrix_random_graph(int vertices, int edges, bool oriented);
    static List_graph* list_random_graph(int vertices, int edges, bool oriented);
    static List_graph* matrix_to_lst(Matrix_graph* graph);
    static Matrix_graph* list_to_matrix(List_graph* graph);

    //Interactive
    static void matrix_interactive();
    static void list_interactive();

    //Demo
    static void matrix_demo();
    static void list_demo();

    //Benchmark
    static void matrix_benchmark(Matrix_graph* graph, std::ofstream& f);
    static void list_benchmark(List_graph* graph, std::ofstream& f);

};


#endif //LAB_5_GRAPHS__FUNCTIONS_H
