all: test

test: test.o

CXX=clang++
CXXFLAGS=--std=c++14
LINK.o=$(LINK.cc)
