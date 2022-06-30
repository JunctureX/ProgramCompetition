#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;

std::vector<int> edges[N];

std::pair<int, int> path(int n, int root) {
  std::vector<int> queue;
  queue.reserve(n);
  std::vector<int> dis(n, -1);
  queue.push_back(root);
  dis[root] = 0;
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &v : edges[u]) if (dis[v] == -1) {
      queue.push_back(v);
      dis[v] = dis[u] + 1;
    }
  }
  int u = 0;
  for (int i = 0; i < n; ++i) {
    if (dis[i] > dis[u]) u = i;
  }
  return {u, dis[u]};
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::pair<int, int>> s;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      int m, root = 0;
      scanf("%d", &m);
      for (int j = 0; j < m; ++j) {
        edges[j].clear();
      }
      for (int j = 0; j < m; ++j) {
        int p;
        scanf("%d", &p);
        if (p == 0) root = j;
        else {
          edges[p - 1].push_back(j);
          edges[j].push_back(p - 1);
        }
      }
      if (m == 1) continue;
      auto x = path(m, root);
      auto y = path(m, x.first);
      sum += x.second * 2;
      s.emplace_back(x.second * 2, y.second);
    }
    int max = 0, min = 1e9;
    for (auto &&e: s) {
      max = std::max(max, sum - e.first + e.second);
      min = std::min(min, sum - e.first + e.second);
    }
    if (s.empty()) min = max = 0;
    printf("%d %d\n", max, min);
  }
  return 0;
}
