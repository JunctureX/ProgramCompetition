#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 3e5 + 10, mod = 1e9 + 7;

int dp[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<bool> mark(m + 1);
    for (int i = 0, x; i < n; ++i) {
      scanf("%d", &x);
      mark[x] = true;
    }
    for (int i = 0; i <= m; ++i) dp[i] = 0;
    dp[0] = 1;
    for (int i = 1; i <= m; ++i) if (!mark[i]) {
      for (int j = i; j <= m; ++j) {
        dp[j] += dp[j - i];
        if (dp[j] >= mod) dp[j] -= mod;
      }
    }
    printf("%d\n", dp[m]);
  }
  return 0;
}
