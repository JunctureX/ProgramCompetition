#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 5000 + 10;
const int mod = 1e9 + 7;

int low[N][4], upp[N][4];
int64 dp[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j < 4; ++j) {
        low[i][j] = i ? i : 1;
        upp[i][j] = 0;
      }
    }
    for (int i = 0; i < m; ++i) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      low[r][x] = std::min(low[r][x], l);
      upp[r][x] = std::max(upp[r][x], l);
    }
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= n; ++j) {
        dp[i][j] = 0;
      }
    }
    dp[0][0] = 3;
    int64 ret = 0;
    for (int i = 1; i <= n; ++i) {
      int u = i & 1, v = u ^ 1;
      int x_min = upp[i][3], x_max = low[i][2];
      int y_min = upp[i][2], y_max = low[i][1];
      if (i == n) {
        for (int x = x_min; x < x_max; ++x) {
          for (int y = std::max(x ? x + 1 : 0, y_min); y < y_max; ++y) {
            ret += dp[x][y];
          }
        }
      } else {
        for (int x = 0; x < i; ++x) {
          for (int y = x + !!x; y < i; ++y) {
            dp[x][y] %= mod;
            if (x_min <= x && x < x_max && y_min <= y && y < y_max) {
              dp[y][i] += dp[x][y];
              dp[x][i] += dp[x][y];
            } else {
              dp[x][y] = 0;
            }
          }
        }
      }
    }
    printf("%lld\n", ret % mod);
  }
  return 0;
}
