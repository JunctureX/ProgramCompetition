#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <bitset>

const int N = 1e6 + 1000;

namespace fib {
std::bitset<N> u;

void add(int x) {
  if (x == 0) return;
  if (x == 1) x = 2;
  if (u[x] == 0 && u[x - 1] == 0 && u[x + 1] == 0) {
    u[x] = 1; return;
  }
  if (u[x] == 0 && u[x + 1] == 0) {
    assert(u[x - 1] == 1);
    u[x - 1] = 0;
    add(x + 1);
    return;
  }
  if (u[x] == 0) {
    for (x += 1; u[x]; x += 2) u[x] = 0;
    assert(x - 1 >= 2);
    assert(!u[x] && !u[x - 2]);
    u[x - 1] = 1;
  } else {
    int l = x - 2, r = x;
    assert(!u[0] && !u[1]);
    for (; u[r]; r += 2) u[r] = 0;
    for (; u[l]; l -= 2) u[l] = 0, u[l + 1] = 1;
    assert(r - 1 >= 2);
    assert(!u[r] && !u[r - 2]);
    u[r - 1] = 1;
    add(l);
  }
}

void sub(int x) {
  if (x == 0) return;
  if (x == 1) x = 2;
  if (u[x]) { u[x] = 0; return; }
  int y = u._Find_next(x), z = 0;
  for (; !u[x]; y -= 2) {
    u[y] = 0;
    u[y - 1] = 1;
    if (y - 1 == x) z = y - 2;
    else u[y - 2] = 1;
  }
  u[x] = 0;
  if (z) add(z);
}

int query() {
  int last = 1, ret = 0;
  for (int i = u._Find_first(); i < u.size(); i = u._Find_next(i)) {
    if (i - last - 1 >= 2) ret += (i - last + 1) / 2, last = i - 1;
    else ret += 1, last = i;
  }
  return ret;
}
}

int main() {
  std::vector<int> lucas = {2, 1};
  for (int i = 2; lucas.back() <= 1e9; ++i) {
    lucas.push_back(lucas[i - 1] + lucas[i - 2]);
  }

  auto decom = [&](int n) -> std::vector<int> {
    int i = std::upper_bound(lucas.begin(), lucas.end(), n) - lucas.begin();
    std::vector<int> ret;
    for (i -= 1; i >= 2; --i) if (n >= lucas[i]) {
      ret.push_back(i);
      n -= lucas[i];
      assert(n < lucas[i]);
    }
    if (n == 1) ret.push_back(1);
    if (n == 2) ret.push_back(0);
    return ret;
  };

  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    fib::u.reset();
    for (int i = 0; i < n; ++i) {
      int a, b, sign;
      scanf("%d%d", &a, &b);
      std::vector<int> ret;
      if (a < 0) ret = decom(-a), sign = -1;
      else ret = decom(a), sign = 1;
      std::vector<int> add, sub;
      for (auto k: ret) {
        int x = b + 1 + k, y = b + 1 - k, s = k & 1;
        add.push_back(x);
        if (y < 0) y = -y, s ^= (y + 1) & 1;
        if (s) sub.push_back(y);
        else add.push_back(y);
      }
      if (sign == -1) std::swap(add, sub);
      for (auto &x: add) fib::add(x);
      for (auto &x: sub) fib::sub(x);
      printf("%d\n", fib::query());
    }
  }
  return 0;
}
