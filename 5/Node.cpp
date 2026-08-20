//
// Created by XYZ on 13.12.2025.
//

#include "Node.h"

Node::Node() {
    counter = NULL;
}

void Node::setCounter(OperationCounter* cnt) {
    counter = cnt;
}