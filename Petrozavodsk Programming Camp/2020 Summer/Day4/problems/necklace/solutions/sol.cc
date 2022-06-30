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
    int n, m = 0;
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
    std::sort(pos.begin(), pos.end(), std::greater<int>());
    if (n <= 2 || pos[0] == n || pos[0] == n - 1) {
      puts("-1");
      continue;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> small_pq;
    std::priority_queue<int> large_pq;
    std::vector<int> idx(n), candidates;
    for (int i = 0; i < n; ++i) {
      if (!group[i].empty()) candidates.push_back(i);
    }
    i64 best = 0, sum = 0;
    for (int x = 1; x <= pos[0]; ++x) {
      for (size_t i = 0; i < candidates.size(); ) {
        int col = candidates[i], &e = idx[col];
        large_pq.push(v[group[col][e++]]);
        if (e == (int)group[col].size()) {
          std::swap(candidates[i], candidates.back());
          candidates.pop_back();
        } else {
          ++i;
        }
      }
      while (!small_pq.empty() && !large_pq.empty() && small_pq.top() < large_pq.top()) {
        int x = small_pq.top(); small_pq.pop();
        int y = large_pq.top(); large_pq.pop();
        small_pq.push(y); large_pq.push(x);
        sum = sum - x + y;
      }
      size_t bound = x * 2 + (x == 1);
      while (!large_pq.empty() && (small_pq.size() < bound || large_pq.top() >= 0)) {
        small_pq.push(large_pq.top());
        sum += large_pq.top();
        large_pq.pop();
      }
      if (small_pq.size() >= bound && (m == 0 || sum > best)) {
        m = x; best = sum;
      }
    }

    std::vector<int> sol;
    { // find a solution
      std::vector<std::pair<int, int>> vs;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m && j < (int)group[i].size(); ++j) {
          vs.emplace_back(v[group[i][j]], group[i][j]);
        }
      }
      std::sort(vs.begin(), vs.end());
      size_t bound = m * 2 + (m == 1);
      while (!vs.empty() && (sol.size() < bound || vs.back().first >= 0)) {
        sol.push_back(vs.back().second);
        vs.pop_back();
      }
    }
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
  return 0;
}
