all: test

test: test.o

CXX=clang++
CXXFLAGS=--std=c++14
# Use C++ to link .o files
LINK.o=$(LINK.cc)
