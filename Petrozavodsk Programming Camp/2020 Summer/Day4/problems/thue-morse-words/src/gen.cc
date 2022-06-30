#include "testlib.h"
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int64 min_n = std::atoll(argv[1]);
  int64 max_n = std::atoll(argv[2]);
  int min_m = std::atoi(argv[3]);
  int max_m = std::atoi(argv[4]);
  std::vector<int> ms;
  int M = 1000000;
  while (M >= min_m) {
    int m = rnd.next(min_m, std::min(M, max_m));
    ms.push_back(m);
    M -= m;
  }
  if (M) ms.push_back(M);
  printf("%d\n", (int)ms.size());
  int gen_rand = 0;
  for (auto &m: ms) {
    int64 n = rnd.next(min_n, max_n);
    printf("%lld\n", n);
    int64 l = 0;
    if (n < 62) l = rnd.next(0ll, (1ll << n) - m);
    else rnd.next(0ll, 1000000000000000000ll);
    int64 r = l + m;
    if (gen_rand % 100 == 99) {
      for (int i = 0; i < m; ++i) putchar('a' + rnd.next(0, 1));
      puts("");
    } else {
      for (int64 i = l; i < r; ++i) putchar('a' + __builtin_popcountll(i) % 2);
      puts("");
    }
  }
  return 0;
}
