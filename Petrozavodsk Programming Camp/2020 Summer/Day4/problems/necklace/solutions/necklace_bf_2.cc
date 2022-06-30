#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, int> PLI;

const int MAXN = 1e6 + 10;
const int MM = 1e9 + 7;
const ll INF = 1ll << 60;
const int B = 256;

int n;
int c[MAXN], v[MAXN], kke[MAXN], ccn[MAXN];
vector<PII> C[MAXN];
set<int> valid, tv;

struct Magic {
    map<int, int> mp;
    int m, mm;
    ll sm[MAXN];
    set<PII> st[MAXN];
    int sz = 0;
    void clear() {
        mp.clear();
        for (int i = 1; i <= n; i++) {
            if (v[i] < 0) {
                mp[-v[i]] = 1;
            }
        }
        m = 0;
        sz = 0;
        for (auto &x : mp) x.second = m++;
        mm = (m - 1) / B;
        for (int i = 0; i <= mm; i++) sm[i] = 0, st[i].clear();
    }
    void insert(int x) {
        int y = mp[x] / B;
        st[y].insert(PII(x, ++sz));
        sm[y] += x;
    }
    int size() {
        return sz;
    }
    ll presum(int x) {
        // cout << "======== " << x << ' ' << sz << ' ' << endl;
        // for (auto &z : st[0]) cout << z.first << ',' << z.second << ' '; cout << endl;
        if (x <= 0) return 0;
        x = min(x, sz);
        int i = 0;
        ll res = 0;
        while (i <= mm) {
            if (x <= st[i].size()) {
                for (auto &y : st[i]) {
                    x--;
                    res += y.first;
                    if (x == 0) break;
                }
                break;
            }
            else {
                res += sm[i];
                x -= st[i].size();
            }
            i++;
        }
        return res;
    }
} koi;

void solve(int casi){
    scanf("%d", &n);
    valid.clear();
    // while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        C[i].clear();
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
        valid.insert(c[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        C[c[i]].emplace_back(-v[i], i);
    }
    for (int i = 1; i <= n; i++) {
        sort(C[i].begin(), C[i].end());
    }
    ll ans = -INF;
    int ansk;
    int pos_cnt = 0;
    ll pos_sum = 0;
    koi.clear();
    // cerr << "valid " << valid.size() << endl;
    for (int mx = 1; !valid.empty(); mx++) {
        tv.clear();
        for (auto &x : valid) {
            int y = C[x][mx - 1].second;
            // cout << "!!" << y << ' ' << v[y] << endl;
            if (v[y] >= 0) {
                pos_sum += v[y];
                pos_cnt++;
            }
            else {
                koi.insert(-v[y]);
            }
            if (C[x].size() > mx) {
                tv.insert(x);
            }
        }
        tv.swap(valid);
        int desire = 2 * mx + (mx == 1);
        // cout << "??? " << mx << ' ' << desire << ' '<< pos_cnt << ' ' << koi.size() << ' ' << pos_sum << ' ' << koi.presum(desire - pos_cnt) << endl;
        if (pos_cnt + koi.size() >= desire) {
            ll SM = pos_sum - koi.presum(desire - pos_cnt);
            if (SM > ans) {
                ans = SM;
                ansk = mx;
            }
        }
    }
    if (ans == -INF) {
        puts("-1");
        return ;
    }

    pos_cnt = 0;
    vector<PLI> pos;
    vector<PII> neg;
    valid.clear();
    for (int i = 1; i <= n; i++) {
        valid.insert(c[i]);
    }
    for (int mx = 1; mx <= ansk; mx++) {
        tv.clear();
        for (auto &x : valid) {
            int y = C[x][mx - 1].second;
            if (v[y] >= 0) {
                pos.emplace_back(c[y]+0ll, y);
                pos_cnt++;
            }
            else {
                neg.emplace_back(-v[y], y);
            }
            if (C[x].size() > mx) {
                tv.insert(x);
            }
        }
        tv.swap(valid);
    }
    int desire = ansk * 2 + (ansk == 1);
    // cout << ans << ' ' << ansk << ' ' << desire << ' ' << pos_cnt << endl;
    if (pos_cnt < desire) {
        desire = desire - pos_cnt;
        sort(neg.begin(), neg.end());
        // for (auto &x : neg) cout << x.first << ' ' << x.second << endl;
        for (int i = 0; i < desire; i++) {
            int y = neg[i].second;
            pos.emplace_back(c[y]+0ll, y);
        }
    }
    for (auto &x : pos) ccn[x.first] = 0;
    for (auto &x : pos) ccn[x.first]++;
    for (auto &x : pos) x.first += ccn[x.first] * -1000000000ll;
    sort(pos.begin(), pos.end());
    int o = pos.size();
    printf("%d\n", o);
    for (int i = 0; i < o; i++) kke[i] = -1;
    for (int i = 0, j = 0; i < pos.size(); i++) {
        kke[j] = pos[i].second;
        j = (j + 2) % o;
        if (kke[j] != -1) j++;
    }
    for (int i = 0; i < o; i++) {
        printf("%d%c", kke[i], " \n"[i + 1 == o]);
    }
}

int main(){
    int T = 1;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        solve(i);
    return 0;
}
