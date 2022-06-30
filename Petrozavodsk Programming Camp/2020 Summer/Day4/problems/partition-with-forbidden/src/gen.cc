#include "testlib.h"
#include <cassert>
#include <algorithm>

// Random sample $k$ elements from $n$ elements with equal probability.
// Time Complexity: $O(k \log k)$
template<typename Int>
std::vector<Int> random_subset(Int n, int k) {
  ensuref(n >= k, "random_subset failed: n >= k");
  std::set<Int> set;
  for (Int i = n - k; i < n; ++ i) {
    Int p = rnd.next(static_cast<Int>(0), i);
    if (set.count(p)) {
      set.insert(i);
    } else {
      set.insert(p);
    }
  }
  std::vector<Int> result;
  for (auto elem: set) {
    result.push_back(elem);
  }
  return result;
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  auto min_n = std::atoi(argv[1]);
  auto max_n = std::atoi(argv[2]);
  auto min_m = std::atoi(argv[3]);
  auto max_m = std::atoi(argv[4]);
  std::vector<int> ns;
  int N = 500;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, N));
    ns.push_back(n);
    N -= n;
  }
  if (N) ns.push_back(N);
  printf("%d\n", (int)ns.size());
  for (auto &n: ns) {
    int m = rnd.next(std::max(n, min_m), max_m);
    printf("%d %d\n", n, m);
    auto a = random_subset(m, n);
    shuffle(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
      if (i) putchar(' ');
      printf("%d", a[i] + 1);
    }
    puts("");
  }
  return 0;
}
