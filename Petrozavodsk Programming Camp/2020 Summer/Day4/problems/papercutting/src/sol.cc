#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using uint64 = unsigned long long;
using pii = std::pair<int, int>;

const uint64 mod = 100000000000000019ull, seed = 97;
const int N = 1e6 + 10;
char buf[N];

std::vector<int> manacher(int n, uint64 s[]) {
  std::vector<int> d(n);
  int l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = (i > r ? 0 : std::min(d[l + r - i + 1], r - i + 1)) + 1;
    while (i + k - 1 < n && i - k >= 0 && s[i + k - 1] == s[i - k]) ++k;
    d[i] = --k;
    if (i + k - 1 > r) {
      l = i - k;
      r = i + k - 1;
    }
  }
  return d;
}

std::vector<pii> solve(const std::vector<int>& rad) {
  std::vector<pii> result;
  int n = rad.size();
  std::vector<int> f(n, 0), g(n, 0);
  f[0] = g[n - 1] = 1;
  for (int i = 1, last = 0; i < n; ++i) {
    if (i - rad[i] <= last) {
      f[i] = 1;
      last = i;
    }
  }
  for (int i = n - 2, last = n - 1; i >= 0; --i) {
    if (i + rad[i + 1] >= last) {
      g[i] = 1;
      last = i;
    }
  }
  for (int i = 0, j = 0; i < n; ++i) if (f[i]) {
    while (j < i || (j < n && !g[j])) ++j;
    if (j < n && g[j]) result.emplace_back(i, j);
  }
  return result;
}

const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

struct rect_t {
  int r1, r2;
  int c1, c2;
};

rect_t bfs(int r, int c, const std::vector<std::string>& s, std::vector<std::vector<bool>>& mark) {
  int n = s.size();
  int m = s[0].size();
  std::vector<pii> queue;
  queue.emplace_back(r, c);
  mark[r][c] = 1;
  rect_t result = (rect_t){r, r, c, c};
  for (size_t i = 0; i < queue.size(); ++i) {
    int r = queue[i].first;
    int c = queue[i].second;
    result.r1 = std::min(result.r1, r);
    result.r2 = std::max(result.r2, r);
    result.c1 = std::min(result.c1, c);
    result.c2 = std::max(result.c2, c);
    for (int k = 0; k < 4; ++k) {
      int rr = r + dr[k], cc = c + dc[k];
      if (rr < 0 || rr >= n || cc < 0 || cc >= m) continue;
      if (mark[rr][cc] || s[rr][cc] != '0') continue;
      queue.emplace_back(rr, cc);
      mark[rr][cc] = 1;
    }
  }
  return result;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::string> s(n);
    std::vector<std::vector<int>> sum(n);
    std::vector<std::vector<bool>> mark(n);
    for (int i = 0; i < n; ++i) {
      sum[i].resize(m, 0);
      mark[i].resize(m, 0);
      scanf("%s", buf);
      s[i] = buf;
      for (int j = 0; j < m; ++j) {
        sum[i][j] = s[i][j] == '0';
        if (i) sum[i][j] += sum[i - 1][j];
        if (j) sum[i][j] += sum[i][j - 1];
        if (i && j) sum[i][j] -= sum[i - 1][j - 1];
      }
    }
    std::vector<std::vector<pii>> add(n), del(n + 1);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (!mark[i][j] && s[i][j] == '0') {
          auto rect = bfs(i, j, s, mark);
          add[rect.r1].emplace_back(rect.c1, rect.c2);
          del[rect.r2 + 1].emplace_back(rect.c1, rect.c2);
        }
      }
    }
    std::vector<uint64> hash(n);
    for (int i = 0; i < n; ++i) {
      hash[i] = 0;
      for (int j = 0; j < m; ++j) {
        hash[i] = (hash[i] * seed + s[i][j]) % mod;
      }
    }
    auto rad = manacher(n, hash.data());
    auto r = solve(rad);

    hash.resize(m);
    for (int j = 0; j < m; ++j) {
      hash[j] = 0;
      for (int i = 0; i < n; ++i) {
        hash[j] = (hash[j] * seed + s[i][j]) % mod;
      }
    }
    rad = manacher(m, hash.data());
    auto c = solve(rad);

    int ret = -1;
    int r1 = 0, r2 = 0;
    std::vector<int> bit1(m), bit2(m);

    auto inc = [&](std::vector<int>& bit, int x, int v) {
      for (; x < m; x += ~x & x + 1) bit[x] += v;
    };
    auto get = [&](std::vector<int>& bit, int x, int r = 0) {
      for (; x >= 0; x -= ~x & x + 1) r += bit[x];
      return r;
    };

    for (auto &er : r) {
      while (r2 <= er.second) {
        for (auto &iv : add[r2]) {
          inc(bit1, iv.first, 1);
          inc(bit2, iv.second, 1);
        }
        ++r2;
      }
      while (r1 < er.first) {
        for (auto &iv : del[r1]) {
          inc(bit1, iv.first, -1);
          inc(bit2, iv.second, -1);
        }
        ++r1;
      }
      for (auto &ec : c) {
        int count = get(bit1, ec.second) - get(bit2, ec.first - 1);
        if (ret == -1 || ret > count) ret = count;
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
