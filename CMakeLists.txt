cmake_minimum_required(VERSION 3.20)
project(parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(parser src/main.cpp src/solver.h src/AST/node.h src/AST/evaluateAST.h src/Parser/parser.cpp src/Parser/parser.h tests/test.h)
