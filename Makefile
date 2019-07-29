all: 0test 1tsp

0.test: 0test.o
0.tsp: 1tsp.o

CXX=clang++
CXXFLAGS=--std=c++14
# Use C++ to link .o files
LINK.o=$(LINK.cc)
