//
// Created by Win10Pro on 05.05.2020.
//

#ifndef LAB_5_GRAPHS__FUNCTIONS_H
#define LAB_5_GRAPHS__FUNCTIONS_H

#include "Matrix_graph.h"
#include "List_graph.h"
#include "Random.h"

class Functions {

public:


    static Matrix_graph* matrix_random_graph(int vertices, int edges);
    static List_graph* list_random_graph(int vertices, int edges);

    static void matrix_interactive();
    static void list_interactive();

};


#endif //LAB_5_GRAPHS__FUNCTIONS_H
