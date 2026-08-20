cmake_minimum_required(VERSION 4.0)
project(Lista_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lista_3 main.cpp
        Tree.cpp
        Tree.h
        OperatorNode.cpp
        OperatorNode.h
        ConstantNode.cpp
        ConstantNode.h
        VariableNode.cpp
        VariableNode.h
        Node.h
        TokenList.cpp
        TokenList.h
        Interface.cpp
        Interface.h
        ValueList.cpp
        ValueList.h
        Result.cpp
        Result.h
        Error.cpp
        Error.h
        Result.cpp
        ResultSaver.cpp
        ResultSaver.h
)
