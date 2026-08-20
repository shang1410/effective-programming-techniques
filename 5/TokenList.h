//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_TOKENLIST_H
#define LISTA_3_TOKENLIST_H

#include <string>

using namespace std;

class TokenList  {
    private:
        string* tokens;
        int count;
        int capacity;

    public:
        TokenList();
        ~TokenList();
        void add(const string& token);
        int getCount() const;
        string get(int index) const;
};


#endif //LISTA_3_TOKENLIST_H