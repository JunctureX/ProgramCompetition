#include "testlib.h"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int min_n = std::atoi(argv[1]);
  int max_n = std::atoi(argv[2]);
  int min_m = std::atoi(argv[3]);
  int max_m = std::atoi(argv[4]);
  std::vector<int> ns;
  int N = 5000;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, N));
    N -= n;
    ns.push_back(n);
  }
  assert(ns.size() * max_m <= 1000000);
  int T = ns.size();
  std::cout << T << std::endl;
  for (auto &n: ns) {
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = rnd.next(3);
    int m = rnd.next(min_m, max_m);
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; ++i) {
      int l = rnd.next(1, n);
      int r = rnd.next(1, n);
      if (l > r) std::swap(l, r);
      int x = rnd.next(1, 3);
      printf("%d %d %d\n", l, r, x);
    }
  }
  return 0;
}
