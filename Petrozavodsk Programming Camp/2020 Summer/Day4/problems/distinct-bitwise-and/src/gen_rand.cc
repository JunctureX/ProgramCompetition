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
    printf("%d %lld\n", n, rnd.next(min_w, max_w));
    std::vector<int64> vs(n * 2);
    for (int i = 0; i < n * 2; ++i) vs[i] = rnd.next(min_w, max_w);
    std::sort(vs.begin(), vs.end());
    for (int i = 0; i < n; ++i) {
      auto l = vs[i * 2];
      auto r = vs[i * 2 + 1];
      printf("%lld %lld\n", l, r);
    }
  }
  return 0;
}
