#include <cmath>
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

int dist2(std::pair<int,int> p1, std::pair<int,int> p2) {
  return ((p2.first - p1.first) * (p2.first - p1.first)) +
         ((p2.second - p1.second) * (p2.second - p1.second));
}


class Path {
public:
  Path(std::vector<std::pair<int,int>> pts) : pts{pts} {};

  void print() {
    std::cout << "Path {" << std::endl;
    for (auto const& pair : this->pts) {
      std::cout << "  " << pair.first << "," << pair.second << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "Length: " << this->length() << std::endl;
  }

  float length() {
    float l = 0;
    for (int i = 0; i < this->pts.size() - 1; i++) {
      l += sqrt(dist2(this->pts[i], this->pts[i+1]));
    }
    return l;
  }

  std::vector<std::pair<int,int>> pts;
};

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
  path.pts.push_back(b.pts[0]);
  return path;
}

struct D2P {
  int dist;
  int pt1_i;
  int pt2_i;
};
bool operator<(const D2P lhs, const D2P rhs) {
  // Reversed because we want shorter edges to have higher priority.
  return lhs.dist > rhs.dist;
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
  while (true) {
    auto next_pair = d2p.top();
    d2p.pop();
    // Check if this edge could possibly be part of a cycle with the
    // existing edges (doesn't form a T-junction)
    if (visits[next_pair.pt1_i] < 2 && visits[next_pair.pt2_i] < 2) {
      neighbors[next_pair.pt1_i].push_back(next_pair.pt2_i);
      neighbors[next_pair.pt2_i].push_back(next_pair.pt1_i);
      // Now see if there's a cyclic path created by adding this edge.
      Path path = {{b.pts[next_pair.pt1_i], b.pts[next_pair.pt2_i]}};
      bool no_path = false;
      int prev_i = next_pair.pt1_i;
      int i = next_pair.pt2_i;
      // Trace this path as far as we can from pt2_i until we get
      // back to pt1_i.
      while (i != next_pair.pt1_i && neighbors[i].size() == 2) {
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
      // Check the path we ended up with
      if (path.pts.size() == b.pts.size() + 1) {
        return path;
      } else if (i == next_pair.pt1_i && path.pts.size() < b.pts.size() + 1) {
        // If the condition holds, we've looped back to pt1 but our cycle is
        // too short (it doesn't include all the vertices). We need to remove
        // this edge from consideration and try again.
        // A fancier data structure would definitely make cycle detection
        // easier, but I don't know it! (Why am I studying this again? :P )
        neighbors[next_pair.pt1_i].pop_back();
        neighbors[next_pair.pt2_i].pop_back();
        pairs_added--;
        visits[next_pair.pt1_i]--;
        visits[next_pair.pt2_i]--;
      }
      pairs_added++;
      visits[next_pair.pt1_i]++;
      visits[next_pair.pt2_i]++;
    }
  }
}

std::vector<Path> get_all_paths(
    std::vector<std::pair<int,int>> pts,
    Path acc) {
  std::cout << "acc @ get_all_paths:" << std::endl;
  acc.print();
  std::vector<Path> paths;
  for (int i = 0; i < pts.size(); i++) {
    acc.pts.push_back(pts[i]);
    acc.print();
    auto pt = pts[i];
    pts.erase(pts.begin() + i);
    auto paths_with_i = get_all_paths(pts, acc);
    paths.insert(paths.end(), paths_with_i.begin(), paths_with_i.end());
    pts.insert(pts.begin() + i, pt);
    acc.pts.pop_back();
  }
  return paths;
}

Path brute_force(Board b) {
  std::vector<Path> all_paths = get_all_paths(b.pts, Path {{}});
  Path min_path {{}};
  double min_length =
    std::numeric_limits<double>::max();
  for (auto &p: all_paths) {
    double l = p.length();
    if (l < min_length) {
      min_length = l;
      min_path = p;
    }
  }
  return min_path;
}


int main() {
  Board b {10, 10, {{1, 0}, {2, 1}, {3, 1}, {8, 1}, {7, 7}, {3, 8}}};
  b.print();
  auto p = nearest_neighbor(b);
  p.print();
  p = closest_pair(b);
  p.print();
  p = brute_force(b);
  p.print();
}
