#include "testlib.h"
#include <cassert>
#include <vector>
#include <algorithm>

using i64 = long long;

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  auto min_n = std::atoll(argv[1]);
  auto max_n = std::atoll(argv[2]);
  auto min_p = std::atoi(argv[3]);
  auto max_p = std::atoi(argv[4]);
  std::vector<int> ps, mark(1000000);
  std::vector<int> can;
  for (int i = 2; i < 1000000; ++i) if (!mark[i]) {
    ps.push_back(i);
    if (min_p <= i && i <= max_p) can.push_back(i);
    for (int j = i; j < 1000000; j += i) mark[j] = 1;
  }
  if (can.empty()) can.push_back(ps.back());
  auto n = rnd.next(min_n, max_n);
  auto l = rnd.next(i64(0), n);
  auto r = rnd.next(l, n);
  auto p = can[rnd.next(can.size())];
  printf("%lld %lld %lld %d\n", n, l, r, p);
  return 0;
}
