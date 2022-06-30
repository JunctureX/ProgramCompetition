#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10, mod = 1e9 + 7;

std::vector<int> edges[N], add[N], next_sub[N];
std::pair<int, int> sub[N * 2];
int size[N], dsu[N];
int n, m;

void dfs(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
    size[u] += size[v];
    sub[m++] = {size[v], u};
    mx = std::max(mx, size[v]);
  }
  if (p != -1) sub[m++] = {n - size[u], u};
  mx = std::max(mx, n - size[u]);
  add[mx].push_back(u);
  next_sub[u].reserve(edges[u].size());
}

namespace fen {
  int64 a[N], b[N], c[N];
  int n;
  void init(int _n) {
    n = _n;
    for (int i = 0; i <= n; ++i) {
      a[i] = b[i] = c[i] = 0;
    }
  }
  void add(int64 *u, int x, int64 v) {
    for (; x <= n; x += ~x & x + 1) u[x] += v;
  }
  int64 get(int64 *u, int x, int64 r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += u[x];
    return r;
  }
  void add(int x, int64 v) {
    add(a, 1, v); add(b, 1, v); add(c, 1, v);
    add(a, x + 1, -v);
    add(b, x + 1, -v * (x + 1));
    add(c, x + 1, -v * (x + 1) * (x + 1));
  }
  int64 get(int x) {
    int64 s0 = get(a, x), s1 = get(b, x), s2 = get(c, x);
    return (s0 * x * (x + 1) + s1 - s2) / 2;
  }
}

int root(int x) {
  if (x != dsu[x]) dsu[x] = root(dsu[x]);
  return dsu[x];
}

void merge(int u, int v) {
  u = root(u); v = root(v);
  fen::add(size[u], -1); fen::add(size[v], -1);
  dsu[u] = v; size[v] += size[u];
  fen::add(size[v], 1);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 0; i < n; ++i) next_sub[i].clear();
    for (int i = 0; i <= n; ++i) add[i].clear();
    for (int i = 1, p; i < n; ++i) {
      scanf("%d", &p); --p;
      edges[p].push_back(i);
      edges[i].push_back(p);
    }
    m = 0;
    dfs(0);
    std::sort(sub, sub + m, std::greater<std::pair<int, int>>());
    for (int i = m - 1; i >= 0; --i) {
      next_sub[sub[i].second].push_back(sub[i].first);
    }
    for (int i = 0; i < n; ++i) dsu[i] = -1;
    fen::init(n);
    int64 ret_lt = 0, ret_eq = 0;
    int cnt = 0, max_b = 0;
    for (int a = n, i = 0; a >= 1; --a) {
      for (auto &u: add[a]) {
        dsu[u] = u; size[u] = 1; ++cnt;
        fen::add(1, 1);
        for (auto &v: edges[u]) if (dsu[v] != -1) {
          merge(u, v);
        }
      }
      while (i < m && sub[i].first >= a) {
        int u = sub[i].second;
        next_sub[u].pop_back();
        int used = edges[u].size() - next_sub[u].size();
        if (used == 2 && !next_sub[u].empty()) {
          max_b = std::max(max_b, next_sub[u].back());
        } else if (used > 2) {
          max_b = std::max(max_b, a);
        }
        ++i;
      }
      if (cnt == n) {
        int bound = std::min(a, max_b);
        if (bound >= 1) {
          if (bound == a) {
            ret_eq += (int64)a * a % mod;
            ret_lt += (int64)(bound - 1) * bound / 2 % mod * a % mod;
          } else {
            ret_lt += (int64)(bound + 1) * bound / 2 % mod * a % mod;;
          }
        }
        if (bound + 1 <= a) {
          ret_eq += (int64)2 * a % mod * a % mod;
          ret_lt += (int64)(a - 1 - bound) * (a + bound) % mod * a % mod;
        }
      } else {
        int b = std::min(n - a, a);
        if (b == a) {
          ret_lt += fen::get(a - 1) % mod * a % mod;
          ret_eq += fen::get(fen::a, a) % mod * a % mod * a % mod;
        } else {
          ret_lt += fen::get(b) % mod * a % mod;
        }
      }
    }
    printf("%lld\n", (ret_lt * 2 + ret_eq) % mod);
  }
  return 0;
}
