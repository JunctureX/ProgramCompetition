#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef pair<ull, ll> PUL;

const int MAXN = 1e6 + 10;
const int MM = 1e9 + 7;

ll ans;
int n;
int vis[128], a[128];

//map<ull, ll> mp[100];
vector<PUL> mp[100];

void solve(int casi){
    //printf("Case #%d:", casi);
    scanf("%d", &n);
    ull NN = (1ull << n) - 1;
    int m = 0;
    ll M = 1;
    for (int i = 0; i <= n; i++)
        vis[i] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        vis[a[i]] = i;
        mp[i].clear();
        if (a[i] == 0) m++;
    }
    for (int i = 1; i <= m; i++) {
        M *= i;
        M %= MM;
    }
    if (a[1] == 0) {
        for (int i = 1; i <= n; i++)
            if (!vis[i]) {
                mp[1].emplace_back(1ull << (i - 1), 1ll);
            }
    }
    else {
        mp[1].emplace_back(1ull << (a[1] - 1), 1ll);
    }
    for (int i = 2; i <= n; i++) {
        if (a[i] == 0) {
            for (auto &x : mp[i - 1]) {
                ull msk = x.first;
                ull z = msk;
                z = ((z & 0xaaaaaaaaaaaaaaaaull) >>  1) | ((z & 0x5555555555555555ull) <<  1);
                z = ((z & 0xccccccccccccccccull) >>  2) | ((z & 0x3333333333333333ull) <<  2);
                z = ((z & 0xf0f0f0f0f0f0f0f0ull) >>  4) | ((z & 0x0f0f0f0f0f0f0f0full) <<  4);
                z = ((z & 0xff00ff00ff00ff00ull) >>  8) | ((z & 0x00ff00ff00ff00ffull) <<  8);
                z = ((z & 0xffff0000ffff0000ull) >> 16) | ((z & 0x0000ffff0000ffffull) << 16);
                z = ((z & 0xffffffff00000000ull) >> 32) | ((z & 0x00000000ffffffffull) << 32);
                for (int y = 0; y < 32 && y < n; y++) {
                    if (!((msk >> y) & 1)) {
                        if ((((z >> (63 - 2 * y)) & NN) | msk) == msk) {
                            mp[i].emplace_back((msk | (1ull << y)), x.second);
                        } 
                    }
                }
                for (int y = 32; y < n; y++) {
                    if (!((msk >> y) & 1)) {
                        if ((((z << (2 * y - 63)) & NN) | msk) == msk) {
                            mp[i].emplace_back((msk | (1ull << y)), x.second);
                        }
                    }
                }
            }
        }
        else {
            for (auto &x : mp[i - 1]) {
                ull msk = x.first;
                int y = a[i] - 1;
                if (!((msk >> y) & 1)) {
                    ull z = msk;
                    z = ((z & 0xaaaaaaaaaaaaaaaaull) >>  1) | ((z & 0x5555555555555555ull) <<  1);
                    z = ((z & 0xccccccccccccccccull) >>  2) | ((z & 0x3333333333333333ull) <<  2);
                    z = ((z & 0xf0f0f0f0f0f0f0f0ull) >>  4) | ((z & 0x0f0f0f0f0f0f0f0full) <<  4);
                    z = ((z & 0xff00ff00ff00ff00ull) >>  8) | ((z & 0x00ff00ff00ff00ffull) <<  8);
                    z = ((z & 0xffff0000ffff0000ull) >> 16) | ((z & 0x0000ffff0000ffffull) << 16);
                    z = ((z & 0xffffffff00000000ull) >> 32) | ((z & 0x00000000ffffffffull) << 32);
                    z = (y <= 31) ? (z >> (63 - 2 * y)) : (z << (2 * y - 63));
                    z &= NN;
                    if ((z | msk) == msk) {
                        mp[i].emplace_back((msk | (1ull << y)), x.second);
                    } 
                }
            }
        }
        sort(mp[i].begin(), mp[i].end());
        auto& f = mp[i];
        int j = 0, k = 0;
        for (; k < f.size(); ) {
            int now = f[k].second;
            while (k + 1 < f.size() && f[k].first == f[k + 1].first) {
                k++;
                now += f[k].second;
                if (now >= MM) now -= MM;
            }
            f[j].first = f[k].first;
            f[j].second = now;
            j++;
            k++;
        }
        f.resize(j);
        // cout << "========== " << i << endl;
        // for (auto &x : mp[i]) {
        //     x.second %= MM;
        //     cout << x.first << "," << x.second << "   ";
        // }
        // cout << endl;
        // cout << i << ' ' << mp[i].size() << endl;
    }
    ll ans = 0;
    for (auto &x : mp[n]) {
        ans += x.second;
    }
    ans %= MM;
    ans = M - ans;
    ans = (ans % MM + MM) % MM;
    printf("%lld\n", ans);
}

int main(){
    int T = 1;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        solve(i);
    return 0;
}
