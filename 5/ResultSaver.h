//
// Created by XYZ on 1.12.2025.
//

#ifndef RESULT_SAVER_H
#define RESULT_SAVER_H

#include "Result.h"
#include "Error.h"
#include "Tree.h"
#include <string>
#include <fstream>

//using namespace std;

template <typename T>
class ResultSaver {
public:
    static bool save(const string& filename, Result<T, Error>& result);
};


template<>
class ResultSaver<Tree*> {
public:
    static bool save(const string& filename, Result<Tree*, Error>& result);
};




#endif //LISTA_3_RESULTSAVER_H