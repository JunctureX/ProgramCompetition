#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using i64 = long long;
using pii = std::pair<int, int>;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> c(n), v(n);
    for (int i = 0; i < n; ++i) scanf("%d", &c[i]), --c[i];
    for (int i = 0; i < n; ++i) scanf("%d", &v[i]);
    std::vector<int> pos(n);
    std::vector<std::vector<int>> group(n);
    for (int i = 0; i < n; ++i) {
      group[c[i]].push_back(i);
      ++pos[c[i]];
    }
    for (int i = 0; i < n; ++i) {
      std::sort(group[i].begin(), group[i].end(), [&](int x, int y) { return v[x] > v[y]; });
    }

    int m = *std::max_element(pos.begin(), pos.end());

    std::vector<int> sol, tmp;
    i64 best = 0;

    auto solve = [&](int m) {
      std::vector<std::pair<int, int>> vs;
      tmp.clear();
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m && j < (int)group[i].size(); ++j) {
          vs.emplace_back(v[group[i][j]], group[i][j]);
        }
      }
      std::sort(vs.begin(), vs.end());
      size_t bound = m * 2 + (m == 1);
      while (!vs.empty() && (tmp.size() < bound || vs.back().first >= 0)) {
        tmp.push_back(vs.back().second);
        vs.pop_back();
      }
      i64 sum = 0;
      for (auto &x: tmp) sum += v[x];
      if (tmp.size() >= bound && (sol.empty() || sum > best)) {
        best = sum;
        sol = tmp;
      }
    };
    
    for (int x = 1; x <= m; ++x) solve(x);

    if (sol.empty()) puts("-1");
    else {
      m = sol.size();
      printf("%d\n", m);
      std::vector<int> cnt(n);
      for (auto &x: sol) cnt[c[x]]++;
      std::sort(sol.begin(), sol.end(), [&](int x, int y) {
        int cx = c[x], cy = c[y];
        if (cx != cy) return cnt[cx] < cnt[cy] || (cnt[cx] == cnt[cy] && cx < cy);
        else return x < y;
      });
      for (int i = 0, j = m / 2; i < m / 2 && j < m; ++i, ++j) {
        if (i) putchar(' ');
        if (m & 1) printf("%d %d", sol[j] + 1, sol[i] + 1);
        else printf("%d %d", sol[i] + 1, sol[j] + 1);
      }
      if (m & 1) printf(" %d\n", sol.back() + 1);
      else puts("");
    }
  }
  return 0;
}
