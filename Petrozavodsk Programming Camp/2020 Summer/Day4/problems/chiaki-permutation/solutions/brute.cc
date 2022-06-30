#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

bool check(int* p, int *q, int n) {
  for (int i = 0; i < n; ++i) {
    if (q[i] && p[i] != q[i]) return false;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      for (int k = j + 1; k < n; ++k) {
        if (p[i] + p[k] == p[j] * 2) return true;
      }
    }
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    int q[n];
    for (int i = 0; i < n; ++i) scanf("%d", &q[i]);
    int p[n];
    for (int i = 0; i < n; ++i) p[i] = i + 1;
    int ret = 0;
    do {
      ret += check(p, q, n);
    } while (std::next_permutation(p, p + n));
    printf("%d\n", ret);
  }
  return 0;
}
