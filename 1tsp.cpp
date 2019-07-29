#include <iostream>
#include <memory>
#include <vector>
#include <utility>

class Board {
public:
  int x_size;
  int y_size;
  std::vector<std::pair<int,int>> points;

  void print() {
    // TODO figure out C++ dynamically sized arrays with actual class features
    char board_chrs[y_size][x_size];
    memset(board_chrs, '.', x_size * y_size * sizeof(char));
    for (auto const& pair: this->points) {
      board_chrs[pair.second][pair.first] = 'X';
    }
    std::cout << board_chrs << std::endl;
  }
};

int dist2(std::pair<int,int> p1, std::pair<int,int> p2) {
  return ((p2.first - p1.first) * (p2.first - p1.first)) +
         ((p2.second - p1.second) * (p2.second - p1.second));
}

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
  // For convenience, start with first listed point on board.

  return {{{1, 0}, {2, 1}}};
}

Path closest_pair(Board b) {
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
