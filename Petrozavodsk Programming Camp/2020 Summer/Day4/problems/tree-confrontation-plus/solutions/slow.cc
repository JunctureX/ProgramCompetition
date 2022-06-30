#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using int64 = long long;

const int N = 2e5 + 10, mod = 1e9 + 7;

std::vector<int> edges[N];
int u[N], v[N], size[N];
int dsu[N * 2], pos[N * 2];
int n, a, b;

int id(int i, int x, int y) {
  if (u[i] == x && v[i] == y) return i * 2;
  else return i * 2 + 1;
}

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void merge(int a, int b) {
  a = get(a), b = get(b);
  if (a != b) dsu[a] = b;
}

void dfs(int x, int p = -1) {
  size[x] = 1;
  for (auto &e: edges[x]) {
    int y = u[e] + v[e] - x;
    if (y == p) continue;
    dfs(y, x);
    if (size[y] >= b && n - size[y] >= a) dsu[id(e, x, y)] = id(e, x, y);
    else dsu[id(e, x, y)] = -1;
    if (size[y] >= a && n - size[y] >= b) dsu[id(e, y, x)] = id(e, y, x);
    else dsu[id(e, y, x)] = -1;
    size[x] += size[y];
  }
}

int solve(int _a, int _b) {
  a = _a, b = _b;
  dfs(0);
  for (int i = 0; i <= n; ++i) pos[i] = -1;

  auto gao = [](std::vector<int> &va, std::vector<int> &vb) {
    for (size_t i = 0; i < va.size(); ++i) pos[va[i]] = i;
    int prefix = -1, suffix = va.size();
    for (auto &e: vb) {
      if (pos[e ^ 1] != -1) {
        if (pos[e ^ 1] != 0) merge(e, va[0]);
        if (pos[e ^ 1] != va.size() - 1) merge(e, va.back());
        prefix = std::max<int>(prefix, pos[e ^ 1] - 1);
        suffix = std::min<int>(suffix, pos[e ^ 1] + 1);
      } else {
        if (!va.empty()) merge(e, va[0]);
        prefix = std::max<int>(prefix, va.size() - 1);
        suffix = std::min<int>(suffix, 0);
      }
    }
    for (int i = 1; i < prefix; ++i) merge(va[i - 1], va[i]);
    for (int i = suffix; i + 1 < (int)va.size(); ++i) merge(va[i], va[i + 1]);
    for (size_t i = 0; i < va.size(); ++i) pos[va[i]] = -1;
  };

  for (int x = 0; x < n; ++x) {
    std::vector<int> va, vb;
    for (auto &e: edges[x]) {
      int y = u[e] + v[e] - x;
      int ib = id(e, x, y), ia = id(e, y, x);
      if (dsu[ib] != -1) vb.emplace_back(ib);
      if (dsu[ia] != -1) va.emplace_back(ia);
    }
    gao(va, vb);
    gao(vb, va);
  }
  int ret = 0;
  for (int i = 0; i < n * 2 - 2; ++i) if (dsu[i] != -1) {
    ret += get(i) == i;
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 0, p; i + 1 < n; ++i) {
      scanf("%d", &p); --p;
      u[i] = i + 1; v[i] = p;
      edges[u[i]].push_back(i);
      edges[v[i]].push_back(i);
    }
    int64 ret = 0;
    for (int a = 1; a <= n; ++a) {
      for (int b = 1; a + b <= n; ++b) {
        //printf("a=%d b=%d w=%d\n", a, b, solve(a, b));
        ret += (int64)a * b * solve(a, b) % mod;
      }
      ret %= mod;
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}
