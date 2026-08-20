//
// Created by XYZ on 13.12.2025.
//

#ifndef LISTA5_REFCOUNTER_H
#define LISTA5_REFCOUNTER_H


class RefCounter
{
    public:
        RefCounter();
        int add();
        int dec();
        int get();
    private:
        int count;
};


#endif //LISTA5_REFCOUNTER_H