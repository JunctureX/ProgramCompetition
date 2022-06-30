#include "testlib.h"
#include <cstdio>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int n = std::atoi(argv[1]);
  int T = (1 << n) * ((1 << n) + 1) / 2;
  printf("%d\n", T);
  for (int i = 0; i < (1 << n); ++i) {
    for (int j = i; j < (1 << n); ++j) {
      printf("%d\n", n);
      for (int k = i; k <= j; ++k) putchar('a' + __builtin_popcount(k) % 2);
      puts("");
    }
  }
  return 0;
}
