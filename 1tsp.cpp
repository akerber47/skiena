#include <iostream>
#include <memory>
#include <vector>
#include <utility>

struct Board {
    int x_size;
    int y_size;
    std::vector<std::pair<int,int>> points;
};

class Path {
public:
    Path(std::vector<std::pair<int,int>> pts) : pts{pts} {};

    void print() {
        for (auto const& pair : this->pts) {
            std::cout << pair.first << ", " << pair.second << std::endl;
        }
    }
    std::vector<std::pair<int,int>> pts;
};

Path nearest_neighbor(Board b) {
    return {{{1, 0}, {2, 1}}};
}

int main() {
    Board b {10, 10, {{1, 0}, {2, 1}, {3, 1}, {7, 7}, {3, 8}}};
    auto p = nearest_neighbor(b);
    p.print();
    std::cout << "Hello world!" << std::endl;
    auto x {11};
    std::cout << "C++ can use " << x << std::endl;
}
