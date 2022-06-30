#include "testlib.h"
#include <cassert>
#include <algorithm>

void gen_rand(int n, int w) {
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(1, n));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(-w, w));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
}

void gen_all_pos(int n, int w) {
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(1, n));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(1, w));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
}

void gen_all_zero(int n) {
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(1, n));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(0, 0));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
}

void gen_all_neg(int n, int w) {
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(1, n));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
  for (int i = 0; i < n; ++i) {
    printf("%d", rnd.next(-w, -1));
    if (i == n - 1) puts("");
    else putchar(' ');
  }
}

void gen_many_pos_in_single_color(int n, int w) {
  int pos = rnd.next(n / 2, n / 2 + n / 8), rest_pos = rnd.next(0, n / 4);
  std::vector<int> c(n), v(n);
  for (int i = 0; i < pos; ++i) c[i] = 1, v[i] = rnd.next(1, w);
  for (int i = pos; i < pos + rest_pos; ++i) c[i] = rnd.next(2, n / 2), v[i] = rnd.next(1, w);
  for (int i = pos + rest_pos; i < n; ++i) c[i] = rnd.next(1, n / 2), v[i] = rnd.next(-w, -1);
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    printf("%d", c[i]);
    if (i == n - 1) puts("");
    else putchar(' ');
  }
  for (int i = 0; i < n; ++i) {
    printf("%d", v[i]);
    if (i == n - 1) puts("");
    else putchar(' ');
  }
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  auto min_n = std::atoi(argv[1]);
  auto max_n = std::atoi(argv[2]);
  auto max_w = std::atoi(argv[3]);
  auto type = std::atoi(argv[4]);
  std::vector<int> ns;
  int N = 200000;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(max_n, N));
    ns.push_back(n);
    N -= n;
  }
  printf("%d\n", (int)ns.size());
  for (auto &n: ns) {
    if (type == 0) gen_rand(n, max_w);
    else if (type == 1) gen_all_pos(n, max_w);
    else if (type == 2) gen_all_zero(n);
    else if (type == 3) gen_all_neg(n, max_w);
    else if (type == 4) gen_many_pos_in_single_color(n, max_w);
  }
  return 0;
}
