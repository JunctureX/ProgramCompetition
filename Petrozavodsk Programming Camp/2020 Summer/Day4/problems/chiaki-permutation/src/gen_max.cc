#include "testlib.h"
#include <cassert>

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int n = std::atoi(argv[1]);
  std::vector<int> ns;
  printf("%d\n", 1);
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("0");
  }
  puts("");
  return 0;
}
