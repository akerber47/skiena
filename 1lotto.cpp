#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <vector>
#include <utility>

// Represent a ticket with bit packing, starting with the rightmost bit.
// If the set of possible numbers is too big, this will break.
using ticket = unsigned int;

ticket mark(ticket t, int num) {
  return t | (1 << (num - 1);
}

ticket marks(std::vector<int> nums) {
  ticket t = 0;
  for (auto &num: nums) {
    t |= (1 << (num - 1);
  }
  return t;
}

int num_marks(ticket t) {
  int ct = 0;
  while (t != 0) {
    ct += (t & 1);
    t >>= 1;
  }
  return ct;
}

int num_overlap(ticket t1, ticket t2) {
  return num_marks(t1 & t2);
}

// List of all possible tickets with k marks from among n numbers
// Must have 0 <= k <= n (or this is impossible)
std::vector<ticket> get_all_tickets(n, k) {
  if (k == n) {
    // Mark all k spots
    return {~(~0U << n)};
  } else if (k == 0) {
    // Mark nothing
    return {0U};
  } else {
    // good ol brute force recursive functions
    // Every ticket with k marks either has:
    // - no mark in the nth spot, and k marks in the first n-1 spots, or:
    // - a mark in the nth spot, and k-1 marks in the first n-1 spots
    auto tix = get_all_tickets(n - 1, k);
    auto tix_missing_n = get_all_tickets(n - 1, k - 1);
    for (auto &t: tix_missing_n) {
      tix.push_back(mark(t, n);
    }
    return tix;
  }
}

