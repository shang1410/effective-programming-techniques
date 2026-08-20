//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_INTERFACE_H
#define LISTA_3_INTERFACE_H

#include "Tree.h"

class Interface {
    private:
        Tree tree;
        void printHelp() const;

    public:
        void run();
};


#endif //LISTA_3_INTERFACE_H