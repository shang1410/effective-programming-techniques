//
// Created by XYZ on 30.11.2025.
//

#ifndef LISTA4_RESULT_H
#define LISTA4_RESULT_H


#include <vector>
#include <cstddef>

using namespace std;

template <typename T, typename E>
class Result {
    public:
        Result(const T& valueClass);
        Result(E* errorPointer);
        Result(vector<E*>& errors);
        Result(const Result<T, E>& other);
        ~Result();

        static Result<T, E> okClass(const T& valueClass);
        static Result<T, E> failClass(E* errorPointer);
        static Result<T, E> failClass(vector<E*>& errors);

        Result<T, E>& operator=(const Result<T, E>& other);

        bool isSuccess();
        T getValue();
        vector<E*>& getErrors();

    private:
        T* valuePointer;
        vector<E*> errors;

        void copyErrors(const vector<E*>& sourceErrors);
        void clearErrors();
};

template <typename E>
class Result<void, E> {
    public:
        Result();
        Result(E* errorPointer);
        Result(vector<E*>& errors);
        Result(const Result<void, E>& otherClass);
        ~Result();

        static Result<void, E> okClass();
        static Result<void, E> failClass(E* errorPointer);
        static Result<void, E> failClass(vector<E*>& errors);

        Result<void, E>& operator=(const Result<void, E>& otherClass);

        bool isSuccess();
        vector<E*>& getErrors();

    private:
        vector<E*> errors;

        void copyErrors(const vector<E*>& sourceErrors);
        void clearErrors();
};


#endif //LISTA4_RESULT_H