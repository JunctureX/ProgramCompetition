#include<bits/stdc++.h>
using namespace std;
using int64 = long long;

const int MM = 1e9 + 7;
const int N = 3e5 + 10;

int64 P[N];
int dp[N];
int g[2000];

void prepare(int N) {
    int t = 900;
    for (int i = -t; i <= t; i++)
      g[i + t] = i * (3 * i - 1) / 2;
    P[0] = 1;
    for (int i = 1; i < N; i++) {
        P[i] = 0;
        for (int j = 1; j <= i; j++) {
            if (g[j + t] <= i) {
                if (j & 1) P[i] += P[i - g[j + t]];
                else P[i] -= P[i - g[j + t]];
            }
            else break;
            if (g[t - j] <= i) {
                if (j & 1) P[i] += P[i - g[t - j]];
                else P[i] -= P[i - g[t - j]];
            }
            else break;
        }
        P[i] = (P[i] % MM + MM) % MM;
    }
}

void solve(int casi){
    int _n, _m;
    scanf("%d%d", &_n, &_m);
    for (int i = 0; i <= _m; i++) dp[i] = P[i];
    for (int i = 1; i <= _n; i++) {
        int x;
        scanf("%d", &x);
        for (int j = _m; j >= x; j--) {
            dp[j] = (dp[j] - dp[j - x]);
            if (dp[j] < 0) dp[j] += MM;
        }
    }
    printf("%d\n", dp[_m]);
}

int main(){
    int T = 1;
    scanf("%d", &T);
    prepare(300010);
    for (int i = 1; i <= T; i++)
        solve(i);
    return 0;
}
