
BINS=0test 1tsp 1lotto

all: $(BINS)

0test: 0test.o
1tsp: 1tsp.o
1lotto: 1lotto.o

CXX=clang++
CXXFLAGS=--std=c++17 -g
# Use C++ to link .o files
LINK.o=$(LINK.cc)


clean:
	rm -f $(BINS) *.o
