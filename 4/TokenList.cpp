//
// Created by XYZ on 15.11.2025.
//

#include "TokenList.h"

using namespace std;

TokenList::TokenList() {
    tokens = NULL;
    count = 0;
    capacity = 0;
}

TokenList::~TokenList() {
    delete[] tokens;
}

void TokenList::add(const std::string& token) {
    if (count >= capacity) {
        capacity = capacity * 2 + 1;
        string* newTokens = new string[capacity];
        for (int i = 0; i < count; i++) {
            newTokens[i] = tokens[i];
        }
        delete[] tokens;
        tokens = newTokens;
    }
    tokens[count++] = token;
}

int TokenList::getCount() const {
    return count;
}

std::string TokenList::get(int index) const {
    if (index >= 0 && index < count) {
        return tokens[index];
    }
    return "";
}