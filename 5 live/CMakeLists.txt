cmake_minimum_required(VERSION 4.0)
project(Lista5mod)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lista5mod main.cpp
        Product.cpp
        Product.h
        MySmartPointer.h
        Helper.cpp
        Helper.h
        RefCounter.cpp
        RefCounter.h)
