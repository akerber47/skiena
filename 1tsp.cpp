#include <iostream>
#include <limits>
#include <memory>
#include <queue>
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
  std::vector<bool> visited(b.pts.size(), false);
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

struct D2P {
  int dist;
  int pt1_i;
  int pt2_i;
};
bool operator<(const D2P lhs, const D2P rhs) {
  return lhs.dist < rhs.dist;
}

Path closest_pair(Board b) {
  std::vector<int> visits(b.pts.size(), 0);
  std::priority_queue<D2P> d2p;
  int pairs_added = 0;
  std::vector<std::vector<int>> neighbors(b.pts.size());
  for (int i = 0; i < b.pts.size(); i++) {
    for (int j = i; j < b.pts.size(); j++) {
      d2p.push(D2P {dist2(b.pts[i], b.pts[j]), i, j});
    }
  }
  while (pairs_added < b.pts.size()) {
    auto next_pair = d2p.top();
    d2p.pop();
    if (visits[next_pair.pt1_i] < 2 && visits[next_pair.pt2_i] < 2) {
      neighbors[next_pair.pt1_i].push_back(next_pair.pt2_i);
      neighbors[next_pair.pt2_i].push_back(next_pair.pt1_i);
      pairs_added++;
      visits[next_pair.pt1_i]++;
      visits[next_pair.pt2_i]++;
    }
  }
  // For convenience, start with first listed point on board.
  Path path = {{b.pts[0]}};
  int prev_i = -1;
  int i = 0;
  while (path.pts.size() < b.pts.size()) {
    if (neighbors[i][0] != prev_i) {
      path.pts.push_back(b.pts[neighbors[i][0]]);
      prev_i = i;
      i = neighbors[i][0];
    } else {
      path.pts.push_back(b.pts[neighbors[i][1]]);
      prev_i = i;
      i = neighbors[i][1];
    }
  }
  return path;
}

int main() {
  Board b {10, 10, {{1, 0}, {2, 1}, {3, 1}, {8, 1}, {7, 7}, {3, 8}}};
  b.print();
  auto p = nearest_neighbor(b);
  p.print();
  p = closest_pair(b);
  p.print();
}
