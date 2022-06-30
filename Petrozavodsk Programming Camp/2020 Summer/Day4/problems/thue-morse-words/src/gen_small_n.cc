#include "testlib.h"
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

std::vector<int> distribute(int n, int T) {
  std::vector<int> cuts, result;
  cuts.push_back(0);
  for (auto i = 0; i < T - 1; ++ i) {
    cuts.push_back(rnd.next(0, n - T));
  }
  cuts.push_back(n - T);
  std::sort(cuts.begin(), cuts.end());
  for (auto i = 1; i <= T; ++ i) {
    result.push_back(cuts.at(i) - cuts.at(i - 1) + 1);
  }
  return result;
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int n = std::atoi(argv[1]);
  int min_m = std::atoi(argv[2]);
  int max_m = std::atoi(argv[3]);
  std::vector<int> ms;
  int M = 1000000;
  while (M >= min_m) {
    int m = rnd.next(min_m, std::min(M, max_m));
    ms.push_back(m);
    M -= m;
  }
  if (M) ms.push_back(M);
  printf("%d\n", (int)ms.size());
  for (auto &m: ms) {
    printf("%d\n", n);
    int64 l = rnd.next(0ll, (1ll << n) - m);
    int64 r = l + m;
    for (int64 i = l; i < r; ++i) putchar('a' + __builtin_popcountll(i) % 2);
    puts("");
  }
  return 0;
}
