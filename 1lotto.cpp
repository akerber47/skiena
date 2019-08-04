#include <ios>
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
  return t | (1 << (num - 1));
}

ticket marks(std::vector<int> nums) {
  ticket t = 0;
  for (auto &num: nums) {
    t = mark(t, num);
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

void print_ticket(ticket t) {
  std::cout.flags(std::ios_base::hex | std::ios_base::showbase);
  std::cout << "  Ticket: " << t << std::endl;
  std::cout.flags(std::ios_base::dec);
  int n = 1;
  while (t != 0) {
    if (t & 1) {
      std::cout << "  " << n << " ";
    }
    t >>= 1;
    ++n;
  }
  std::cout << std::endl;
}

int num_overlap(ticket t1, ticket t2) {
  return num_marks(t1 & t2);
}

// List of all possible tickets with k marks from among n numbers
// Must have 0 <= k <= n (or this is impossible)
std::vector<ticket> get_all_tickets(int n, int k) {
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
      tix.push_back(mark(t, n));
    }
    return tix;
  }
}

// See if a set of tickets "covers" each predicted ticket (that is, for any
// choice of predicted ticket, some ticket we bought has at least l entries
// in common with it).
bool check_coverage(
    std::vector<ticket> bought,
    std::vector<ticket> predicted,
    int l
) {
  for (auto &t_pred: predicted) {
    bool covered = false;
    for (auto &t_bought: bought) {
      if (num_overlap(t_bought, t_pred) >= l) {
        covered = true;
        break;
      }
    }
    if (!covered) {
      return false;
    }
  }
  return true;
}

void find_min_tix(
    std::vector<ticket> tix_used,
    std::vector<ticket> tix_to_buy,
    std::vector<ticket> predicted,
    int l,
    // Used to check if we've found new minimum.
    // If so, plug it in!
    int &min_size,
    std::vector<ticket> &min_tix
) {
  // Check if the set that we're given covers
  int cur_size = tix_used.size();
  if (check_coverage(tix_used, predicted, l) && cur_size < min_size) {
    min_size = cur_size;
    min_tix = tix_used;
  } else if (cur_size < min_size) {
    for (int i = 0; i < tix_to_buy.size(); i++) {
      auto t = tix_to_buy[i];
      tix_used.push_back(t);
      tix_to_buy.erase(tix_to_buy.begin() + i);
      find_min_tix(tix_used, tix_to_buy, predicted, l, min_size, min_tix);
      tix_to_buy.insert(tix_to_buy.begin() + i, t);
      tix_used.pop_back();
    }
  }
  // Otherwise, we're too big, and we haven't found anything better, so give
  // up now.
}

// Produce a minimal-size set of tickets that covers enough entries from all
// possible winners. Use brute force.
std::vector<ticket> lotto(int n, int k, int j, int l) {
  auto predicted = get_all_tickets(n, j);
  auto tix_to_buy = get_all_tickets(n, k);
  // This problem is highly symmetric, but we'll ignore all the symmetry.
  // (after all, it's brute force...)
  int min_size = std::numeric_limits<int>::max();
  std::vector<ticket> min_tix;
  find_min_tix({}, tix_to_buy, predicted, l, min_size, min_tix);
  return min_tix;
}

int main() {
  auto tix = get_all_tickets(5, 3);
  for (auto &t: tix) {
    print_ticket(t);
  }
  tix = lotto(5, 3, 3, 2);
  std::cout << "Lotto(5, 3, 3, 2):" << std::endl;
  for (auto &t: tix) {
    print_ticket(t);
  }
  tix = lotto(7, 3, 3, 2);
  std::cout << "Lotto(7, 3, 3, 2):" << std::endl;
  for (auto &t: tix) {
    print_ticket(t);
  }
  tix = lotto(5, 4, 3, 3);
  std::cout << "Lotto(5, 4, 3, 3):" << std::endl;
  for (auto &t: tix) {
    print_ticket(t);
  }
  // Sadly, my computer (and possibly any computer) is too slow
  // to brute-force with the numbers in the book
  /*
  tix = lotto(15, 5, 5, 3);
  std::cout<< "Lotto(15, 5, 5, 3):" << std::endl;
  for (auto &t: tix) {
    print_ticket(t);
  }
  */
}
