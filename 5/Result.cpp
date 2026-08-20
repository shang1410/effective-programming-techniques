//
// Created by XYZ on 30.11.2025.
//

#include "Result.h"
#include "Tree.h"
#include "Error.h"

template <typename T, typename E>
Result<T, E>::Result(const T& valueClass) {
    valuePointer = new T(valueClass);
}

template <typename T, typename E>
Result<T, E>::Result(E* errorPointer)
{
    valuePointer = NULL;
    if (errorPointer != NULL) errors.push_back(errorPointer);
}

template <typename T, typename E>
Result<T, E>::Result(std::vector<E*>& errorsParam)
{
    valuePointer = NULL;
    copyErrors(errorsParam);
}

template <typename T, typename E>
Result<T, E>::Result(const Result<T, E>& other)
{
    if (other.valuePointer != NULL) valuePointer = new T(*(other.valuePointer));
    else valuePointer = NULL;

    copyErrors(other.errors);
}

template <typename T, typename E>
Result<T, E>::~Result()
{
    if (valuePointer != NULL)
    {
        delete valuePointer;
        valuePointer = NULL;
    }

    clearErrors();
}

template <typename T, typename E>
Result<T, E> Result<T, E>::okClass(const T& valueClass)
{
    return Result<T, E>(valueClass);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::failClass(E* errorPointer)
{
    return Result<T, E>(errorPointer);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::failClass(vector<E*>& errors)
{
    return Result<T, E>(errors);
}

template <typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& other)
{
    if (this != &other)
    {
        if (valuePointer != NULL)
        {
            delete valuePointer;
            valuePointer = NULL;
        }

        clearErrors();

        if (other.valuePointer != NULL) valuePointer = new T(*(other.valuePointer));

        copyErrors(other.errors);
    }

    return *this;
}

template <typename T, typename E>
bool Result<T, E>::isSuccess()
{
    return (valuePointer != NULL && errors.empty());
}

template <typename T, typename E>
T Result<T, E>::getValue()
{
    if (valuePointer != NULL)
    {
        return *valuePointer;
    }

    return T();
}

template <typename T, typename E>
vector<E*>& Result<T, E>::getErrors()
{
    return errors;
}

template <typename T, typename E>
void Result<T, E>::copyErrors(const vector<E*>& sourceErrors)
{
    for (size_t i = 0; i < sourceErrors.size(); i++)
    {
        if (sourceErrors[i] != NULL) errors.push_back(sourceErrors[i]);
    }
}

template <typename T, typename E>
void Result<T, E>::clearErrors()
{
    for (size_t i = 0; i < errors.size(); i++)
    {
        if (errors[i] != NULL) delete errors[i];
    }
    errors.clear();
}

// Specjalizacja dla void
template <typename E>
Result<void, E>::Result(){} // pusty wektor - sukces

template <typename E>
Result<void, E>::Result(E* pcError){
    if (pcError != NULL) errors.push_back(pcError);
}

template <typename E>
Result<void, E>::Result(vector<E*>& errorsParam){
    copyErrors(errorsParam);
}

template <typename E>
Result<void, E>::Result(const Result<void, E>& otherClass){
    copyErrors(otherClass.errors);
}

template <typename E>
Result<void, E>::~Result(){
    clearErrors();
}

template <typename E>
Result<void, E> Result<void, E>::okClass(){
    return Result<void, E>();
}

template <typename E>
Result<void, E> Result<void, E>::failClass(E* errorPointer){
    return Result<void, E>(errorPointer);
}

template <typename E>
Result<void, E> Result<void, E>::failClass(vector<E*>& vErrors){
    return Result<void, E>(vErrors);  // POPRAWIONO: było CResult
}

template <typename E>
Result<void, E>& Result<void, E>::operator=(const Result<void, E>& otherClass)
{
    if (this != &otherClass)
    {
        clearErrors();
        copyErrors(otherClass.errors);
    }

    return *this;
}

template <typename E>
bool Result<void, E>::isSuccess(){
    return errors.empty();
}

template <typename E>
vector<E*>& Result<void, E>::getErrors(){
    return errors;
}

template <typename E>
void Result<void, E>::copyErrors(const vector<E*>& sourceErrors)
{
    for (size_t i = 0; i < sourceErrors.size(); i++)
    {
        if (sourceErrors[i] != NULL)
        {
            errors.push_back(sourceErrors[i]);
        }
    }
}

template <typename E>
void Result<void, E>::clearErrors()
{
    for (size_t i = 0; i < errors.size(); i++)
    {
        if (errors[i] != NULL) delete errors[i];
    }
    errors.clear();
}


class Tree;
class Error;

template class Result<Tree, Error>;
template class Result<Tree*, Error>;
template class Result<void, Error>;
