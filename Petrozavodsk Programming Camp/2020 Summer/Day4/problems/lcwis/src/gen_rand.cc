#include "testlib.h"
#include <cassert>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int min_n = std::atoi(argv[1]);
  int max_n = std::atoi(argv[2]);
  std::vector<int> ns, ms;
  int N = 1000000;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(N, max_n));
    int m = rnd.next(min_n, std::min(N, max_n));
    N -= std::max(n, m);
    ns.push_back(n);
    ms.push_back(m);
  }
  int T = ns.size();
  printf("%d\n", T);
  for (int cas = 0; cas < T; ++cas) {
    int n = ns[cas], m = ms[cas];
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i) {
      if (i) putchar(' ');
      putchar('1' + rnd.next(3));
    }
    puts("");
    for (int i = 0; i < m; ++i) {
      if (i) putchar(' ');
      putchar('1' + rnd.next(3));
    }
    puts("");
  }
  return 0;
}
