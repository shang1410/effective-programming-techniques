//
// Created by XYZ on 30.11.2025.
//

#ifndef LISTA4_ERROR_H
#define LISTA4_ERROR_H

#include <string>

using namespace std;

class Error {
    public:
        Error();
        Error(const string& errorDescription);
        Error(const Error& other);
        ~Error();
        Error& operator=(const Error& other);

        string getDescription() const;
        void setDescription(const string& errorDescription);

    private:
        string errorDescription;
};


#endif //LISTA4_ERROR_H