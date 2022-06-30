#include "testlib.h"
#include <cassert>
#include <algorithm>
#include <vector>

using int64 = long long;

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  auto min_n = atoi(argv[1]);
  auto max_n = atoi(argv[2]);
  auto min_w = atoll(argv[3]);
  auto max_w = atoll(argv[4]);
  int N = 5000;
  std::vector<int> ns;
  while (N >= min_n) {
    auto n = rnd.next(min_n, std::min(N, max_n));
    ns.push_back(n);
    N -= n;
  }
  int T = ns.size();
  printf("%d\n", T);
  for (auto &n: ns) {
    auto x = rnd.next(min_w, max_w);
    printf("%d %lld\n", n, x);
    int64 s = 1;
    while (s < n) s *= 2;
    s = (int64(1) << 59) / s;
    for (int i = 0; i < n; ++i) {
      auto l = rnd.next(s);
      auto r = rnd.next(s);
      if (l > r) std::swap(l, r);
      printf("%lld %lld\n", s * i + l, s * i + r);
    }
  }
  return 0;
}
