
BINS=0test 1tsp

all: $(BINS)

0test: 0test.o
1tsp: 1tsp.o

CXX=clang++
CXXFLAGS=--std=c++17
# Use C++ to link .o files
LINK.o=$(LINK.cc)


clean:
	rm -f $(BINS) *.o
