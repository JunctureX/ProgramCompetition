#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 3e5 + 10, mod = 1e9 + 7;

int64 p[N], dp[N];
int g[1000];

void prepare() {
  for (int i = 0; i < 900; ++ i) {
    int k = (i & 1) ? -i / 2 - 1 : i / 2 + 1;
    g[i] = k * (3 * k - 1) / 2;
  }
  p[0] = 1;
  for (int n = 1, m = 0; n < N; ++ n) {
    while (g[m] <= n) ++m;
    for (int i = 0; i < m; ++i) {
      if ((i >> 1) & 1) p[n] -= p[n - g[i]];
      else p[n] += p[n - g[i]];
    }
    p[n] = (p[n] % mod + mod) % mod;
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    std::sort(a.begin(), a.end());
    for (int i = 0; i <= sum && i <= m; ++i) dp[i] = 0;
    dp[0] = 1; sum = 0;
    for (int i = 0; i < n; ++i) {
      sum = std::min(sum + a[i], m);
      for (int j = sum; j >= a[i]; --j) {
        dp[j] -= dp[j - a[i]];
        if (dp[j] < 0) dp[j] += mod;
      }
    }
    int64 ret = 0;
    for (int i = 0; i <= m && i <= sum; ++i) if (dp[i]) {
      ret += p[m - i] * dp[i] % mod;
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}
