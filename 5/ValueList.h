//
// Created by XYZ on 15.11.2025.
//

#ifndef LISTA_3_VALUELIST_H
#define LISTA_3_VALUELIST_H


class ValueList {
    private:
        double* values;
        int count;
        int capacity;

    public:
        ValueList();
        ~ValueList();
        void add(double value);
        int getCount() const;
        const double* getValues() const;
};


#endif //LISTA_3_VALUELIST_H