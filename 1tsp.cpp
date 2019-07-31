#include <iostream>
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
    std::cout << buf << std::endl;
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
  // For convenience, start with first listed point on board.
  // Assume the board has at least 2 points (or the problem is trivial).
  /*
  Path path = {{b.pts[0]}};
  while (path.pts.length < b.pts.length) {
    auto last = path.pts.back();
    auto min_dist = INT_MAX;
    auto min_pt = b.pts[1];
    for (auto const &pt: b.pts) {
      if (dist2(last, pt) < min_dist) {
        min_pt = pt;
        min_dist = dist2(last, pt);
      }
    }
    path.append(min_pt);
  */

  return {{{1, 0}, {2, 1}}};
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
  Board b {10, 10, {{1, 0}, {2, 1}, {3, 1}, {7, 7}, {3, 8}}};
  b.print();
  auto p = nearest_neighbor(b);
  p.print();
}
