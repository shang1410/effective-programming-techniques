//
// Created by XYZ on 30.11.2025.
//

#include "Error.h"

Error::Error(){
    errorDescription = "Nieznany blad";
}


Error::Error(const string& errorDescription){
    this->errorDescription = errorDescription;
}


Error::Error(const Error& cOther){
    errorDescription = cOther.errorDescription;
}


Error::~Error(){}


Error& Error::operator=(const Error& cOther){
    if (this != &cOther) errorDescription = cOther.errorDescription;

    return *this;
}


string Error::getDescription() const{
    return errorDescription;
}

void Error::setDescription(const string& errorDescription){
    this->errorDescription = errorDescription;
}

