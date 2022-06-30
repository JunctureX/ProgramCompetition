#include <cstdio>

const int N = 2000 + 10;

int s[N][N];

int main() {
  int n, l, r, mod;
  scanf("%d%d%d%d", &n, &l, &r, &mod);
  s[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    s[i][0] = 0;
    for (int j = 1; j <= i; ++j) {
      s[i][j] = ((i - 1) * s[i - 1][j] + s[i - 1][j - 1]) % mod;
    }
  }
  //for (int i = 0; i <= n; ++i) printf("%d ", s[n][i]);
  //puts("");
  int sum = 0;
  for (int i = l; i <= r; ++i) sum += s[n][i], sum %= mod;
  printf("%d\n", sum);
  return 0;
}
