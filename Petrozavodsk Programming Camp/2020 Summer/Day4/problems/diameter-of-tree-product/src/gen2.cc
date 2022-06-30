#include "testlib.h"
#include <cassert>
#include <vector>
#include <functional>

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

std::vector<int> gen_rand(int n, int m) {
  m = std::min(m, n);
  assert(1 <= m && m <= n);
  std::vector<int> parent(n, -1);
  for (int i = 1; i < n; ++i) {
    parent[i] = rnd.next(std::max(0, i - m), i - 1);
  }
  return parent;
}

std::vector<int> gen_binary(int n) {
  std::vector<int> parent(n, -1);
  std::vector<int> candidate = {0}, degree(n, 0);
  for (int i = 1; i < n; ++ i) {
    while (1) {
      int x = rnd.next(0, (int)candidate.size() - 1);
      if (degree[candidate[x]] != 2) {
        degree[candidate[x]] ++;
        int u = candidate[x], v = i;
        parent[v] = u;
        candidate.push_back(v);
        break;
      }
    }
  }
  return parent;
}

std::vector<int> gen_skew(int n, int m) {
  assert(0 <= m && m <= n);
  m = std::max(1, m);
  std::vector<int> parent(n, -1);
  for (int i = 1; i < m; ++i) {
    parent[i] = i - 1;
  }
  for (int i = m; i < n; ++i) {
    parent[i] = rnd.next(0, m - 1);
  }
  return parent;
}

std::vector<int> gen_line(int n) {
  std::vector<int> parent(n, -1);
  for (int i = 1; i < n; ++i) {
    parent[i] = i - 1;
  }
  return parent;
}

std::vector<int> gen_kary(int n, int k) {
  std::vector<int> parent(n, -1);
  for (int i = 1; i < n; ++i) {
    if (k == 1) parent[i] = i - 1;
    else parent[i] = i / k;
  }
  return parent;
}

std::vector<int> gen_star(int n) {
  std::vector<int> parent(n, -1);
  for (int i = 1; i < n; ++i) {
    parent[i] = 0;
  }
  return parent;
}

std::vector<int> gen_wheel(int n, int m) {
  std::vector<int> parent(n, -1);
  for (int i = 1; i < n; ++i) {
    if (i <= m) parent[i] = 0;
    else parent[i] = i - m;
  }
  return parent;
}

std::vector<std::pair<int, int>> combine(int n) {
  int part = rnd.next(20, 30);
  auto ns = distribute(n, part);
  int s = 0;
  std::vector<std::pair<int, int>> edges;
  for (auto &&n: ns) {
    int type = rnd.next(7);
    std::vector<int> parent;
    if (type == 0) parent = gen_rand(n, rnd.next(2, 5));
    else if (type == 1) parent = gen_binary(n);
    else if (type == 2) parent = gen_skew(n, rnd.next(n / 4, n / 2));
    else if (type == 3) parent = gen_line(n);
    else if (type == 4) parent = gen_kary(n, rnd.next(1, std::min(n, 10)));
    else if (type == 5) parent = gen_star(n);
    else parent = gen_wheel(n, rnd.next((int)cbrt(n), (int)sqrt(n)));
    std::vector<int> label(n);
    for (int i = 0; i < n; ++i) label[i] = i + 1 + s;
    shuffle(label.begin(), label.end());
    if (s) {
      int x = rnd.next(s) + 1;
      int y = rnd.next(n) + 1 + s;
      edges.emplace_back(x, y);
    }
    for (int i = 1; i < n; ++i) {
      int u = parent[i], v = i;
      edges.emplace_back(label[u], label[v]);
    }
    s += n;
  }
  return edges;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  auto N = 1000000;
  auto T = std::atoi(argv[1]);
  auto min_n = std::atoi(argv[2]);
  auto max_n = std::atoi(argv[3]);
  assert(min_n >= 2 && min_n <= N);
  assert(max_n >= min_n);
  std::vector<int> ns;
  while (N >= min_n) {
    int n = rnd.next(min_n, std::min(N, max_n));
    ns.push_back(n);
    N -= n;
  }
  assert((int)ns.size() >= T);
  printf("%d\n", T);
  auto ms = distribute(ns.size(), T);
  for (size_t i = 0, offset = 0; i < ms.size(); ++i) {
    printf("%d\n", ms[i]);
    for (size_t j = 0; j < ms[i]; ++j) {
      assert(offset < ns.size());
      int n = ns[offset++];
      std::vector<int> parent(n);
      int type1 = rnd.next(8);
      if (type1 == 0) parent = gen_rand(n, rnd.next(10, 50));
      else if (type1 == 1) parent = gen_binary(n);
      else if (type1 == 2) parent = gen_skew(n, rnd.next(n / 4, n / 2));
      else if (type1 == 3) parent = gen_line(n);
      else if (type1 == 4) parent = gen_kary(n, rnd.next(2, std::min(n, 10)));
      else if (type1 == 5) parent = gen_star(n);
      else parent = gen_wheel(n, rnd.next((int)cbrt(n), (int)sqrt(n)));
      std::vector<std::pair<int, int>> edges;
      std::vector<int> label(n);
      for (int i = 0; i < n; ++i) label[i] = i + 1;
      if (type1 == 7) edges = combine(n);
      else {
        shuffle(label.begin(), label.end());
        for (int i = 1; i < n; ++i) {
          int u = parent[i], v = i;
          edges.emplace_back(label[u], label[v]);
        }
      }
      std::vector<std::vector<int>> ee(n);
      for (auto &&e: edges) {
        ee[e.first - 1].push_back(e.second - 1);
        ee[e.second - 1].push_back(e.first - 1);
      }
      parent = trans(ee);
      printf("%d", n);
      for (auto &&x: parent) printf(" %d", x + 1);
      puts("");
    }
  }
  return 0;
}
