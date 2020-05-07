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

        std::cout<<"If you want to execute another mode press 'y', press 'n', if you don`t\n";
        std::cin>>response;

    }
}

void Mode::demo() {

}

void Mode::benchmark() {

}
