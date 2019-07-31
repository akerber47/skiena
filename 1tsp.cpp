#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <utility>

class Board {
public:
  int x_size;
  int y_size;
  std::vector<std::pair<int,int>> pts;

  void print() {
    std::vector<std::vector<char>>
      board(y_size, std::vector<char>(x_size, '.'));
    for (auto const& pair: this->pts) {
      board[pair.second][pair.first] = 'X';
    }
    std::string buf;
    for (auto const &row: board) {
      buf = "";
      for (auto const &c: row) {
        buf += c;
        buf += ' ';
      }
      std::cout << buf << std::endl;
    }
  }
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

int dist2(std::pair<int,int> p1, std::pair<int,int> p2) {
  return ((p2.first - p1.first) * (p2.first - p1.first)) +
         ((p2.second - p1.second) * (p2.second - p1.second));
}

Path nearest_neighbor(Board b) {
  std::vector visited(b.pts.size(), false);
  // For convenience, start with first listed point on board.
  // Assume the board has at least one point.
  Path path = {{b.pts[0]}};
  visited[0] = true;
  while (path.pts.size() < b.pts.size()) {
    auto last = path.pts.back();
    auto min_dist = std::numeric_limits<int>::max();
    auto min_pt_i = -1; // placeholder
    for (int i = 0; i < b.pts.size(); i++) {
      if (!visited[i] && dist2(last, b.pts[i]) < min_dist) {
        min_pt_i = i;
        min_dist = dist2(last, b.pts[i]);
      }
    }
    path.pts.push_back(b.pts[min_pt_i]);
    visited[min_pt_i] = true;
  }
  return path;
}

struct Dist2Pairs {
  int dist;
  std::pair<int,int> pt1;
  std::pair<int,int> pt2;
};

Path closest_pair(Board b) {
  return {{{1, 0}, {2, 1}}};
}

int main() {
  Board b {10, 10, {{1, 0}, {2, 1}, {3, 1}, {8, 1}, {7, 7}, {3, 8}}};
  b.print();
  auto p = nearest_neighbor(b);
  p.print();
}
