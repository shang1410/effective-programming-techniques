//
// Created by XYZ on 1.12.2025.
//

#include "ResultSaver.h"

template <typename T>
bool ResultSaver<T>::save(const string& filename, Result<T, Error>& result) {
    ofstream file(filename.c_str());

    if (!file.is_open()) {
        return false;
    }

    if (result.isSuccess()) {
        file << "Sukces" << endl;
        file << "Brak bledow" << endl;
    } else {
        file << "Niepowiedzenie" << endl;
        vector<Error*>& errors = result.getErrors();
        file << "Liczba bledow: " << errors.size() << endl;
        file << "Bledy:" << endl;

        for (size_t i = 0; i < errors.size(); i++) {
            file << "  [" << (i + 1) << "] " << errors[i]->getDescription() << endl;
        }
    }

    file.close();
    return true;
}


bool ResultSaver<Tree*>::save(const string& filename, Result<Tree*, Error>& result) {
    ofstream file(filename.c_str());

    if (!file.is_open()) {
        return false;
    }

    if (result.isSuccess()) {
        file << "Sukces" << endl;
        Tree* tree = result.getValue();

        if (tree != NULL) {
            file << "Drzewo (postac prefiksowa)" << endl;
            file << tree->toString() << endl;
        } else {
            file << "Brak drzewa" << endl;
        }
    } else {
        file << "Niepowodzenie" << endl;
        vector<Error*>& errors = result.getErrors();
        file << "Liczba bledow: " << errors.size() << endl;
        file << "Bledy:" << endl;

        for (size_t i = 0; i < errors.size(); i++) {
            file << "  [" << (i + 1) << "] " << errors[i]->getDescription() << endl;
        }
    }

    file.close();
    return true;
}

template class ResultSaver<Tree*>;
