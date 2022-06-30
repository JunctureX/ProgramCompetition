#include "testlib.h"
#include <algorithm>
#include <functional>
#include <cassert>

std::vector<int> distribute(int n, int T) {
  std::vector<int> cuts, result;
  cuts.push_back(0);
  for (auto i = 0; i < T - 1; ++ i) {
    cuts.push_back(rnd.next(0, n - T));
  }
  cuts.push_back(n - T);
  std::sort(cuts.begin(), cuts.end());
  for (auto i = 1; i <= T; ++ i) {
    result.push_back(cuts.at(i) - cuts.at(i - 1) + 1);
  }
  return result;
}

std::vector<int> trans(const std::vector<std::vector<int>>& edges) {
  int n = edges.size();
  std::vector<int> parent(n);
  std::function<void(int, int)> dfs = [&] (int u, int p) {
    parent[u] = p;
    for (auto &&v: edges[u]) if (v != p) {
      dfs(v, u);
    }
  };

  dfs(rnd.next(n), -1);
  return parent;
}

void gen(const std::vector<int>& a, int n) {
  std::vector<int> deg(n, 1);
  for (auto &&x: a) ++deg[x];
  std::set<std::pair<int, int>> s;
  for (int i = 0; i < n; ++i) s.emplace(deg[i], i);
  std::vector<std::vector<int>> edges(n);
  for (auto &u: a) {
    int v = s.begin()->second;
    assert(deg[v] == 1);
    s.erase({deg[u], u});
    s.erase({deg[v], v});
    --deg[u], --deg[v];
    if (deg[u] != 0) s.emplace(deg[u], u);
    if (deg[v] != 0) s.emplace(deg[v], v);
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  int u = -1, v = -1;
  for (int i = 0; i < n; ++i) if (deg[i] == 1) {
    if (u == -1) u = i;
    else v = i;
  }
  edges[u].push_back(v);
  edges[v].push_back(u);
  auto parent = trans(edges);
  printf("%d", n);
  for (auto &x: parent) printf(" %d", x + 1);
  puts("");
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int T = std::atoi(argv[1]);
  int min_n = std::atoi(argv[2]);
  int max_n = std::atoi(argv[3]);
  int N = 1000000;
  std::vector<int> ns;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(N, max_n));
    N -= n;
    ns.push_back(n);
  }
  assert((int)ns.size() >= T);
  printf("%d\n", T);
  auto ms = distribute(ns.size(), T);
  for (size_t i = 0, offset = 0; i < ms.size(); ++i) {
    printf("%d\n", ms[i]);
    for (size_t j = 0; j < ms[i]; ++j) {
      int n = ns[offset++];
      if (n == 1) puts("1 0");
      else {
        std::vector<int> a(n - 2);
        for (int k = 0; k < n - 2; ++k) {
          a[k] = rnd.next(n);
        }
        gen(a, n);
      }
    }
  }
  return 0;
}
