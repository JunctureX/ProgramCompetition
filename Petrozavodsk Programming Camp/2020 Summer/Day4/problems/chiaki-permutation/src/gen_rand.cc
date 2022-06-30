#include "testlib.h"
#include <cassert>

std::vector<int> solve(int n) {
  if (n == 1) return {1};
  auto p = solve(n / 2);
  auto q = solve(n - n / 2);
  for (auto &&x : p) x *= 2;
  for (auto &&x : q) x = x * 2 - 1;
  if (rnd.next(2)) std::swap(p, q);
  for (auto &&x: q) p.push_back(x);
  return p;
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int n = std::atoi(argv[1]);
  int min_z = std::atoi(argv[2]);
  int max_z = std::atoi(argv[3]);
  std::vector<int> ns;
  int N = 50;
  while (N >= n) {
    N -= n;
    ns.push_back(n);
  }
  int T = ns.size();
  printf("%d\n", T);
  for (int cas = 0; cas < T; ++cas) {
    printf("%d\n", n);
    auto p = solve(n);
    int z = rnd.next(min_z, max_z);
    for (int i = 0; i < z; ++i) {
      p[rnd.next(n)] = 0;
    }
    for (int i = 0; i < n; ++i) {
      if (i) putchar(' ');
      printf("%d", p[i]);
    }
    puts("");
  }
  return 0;
}
