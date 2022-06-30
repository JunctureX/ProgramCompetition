#include "testlib.h"
#include <cassert>

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
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i + 1;
    shuffle(p.begin(), p.end());
    shuffle(p.begin(), p.end());
    shuffle(p.begin(), p.end());
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
