#include <bits/stdc++.h>
using namespace std;
#define cs const
#define pb push_back
typedef long long ll; 
typedef __int128 lll; 
typedef pair <int, int> pi; 

mt19937 rnd(time(0));

// cs int N = 1e3 + 5; 
int p, w; ll L; 
int gx, gy; 
int add(int x, int y) {
    return x + y >= p ? x + y - p : x + y; 
}
int mul(int x, int y) {
    return 1ll * x * y % p; 
}
ll mult(ll x, ll y) {
    return (lll)x * y % L;
}
struct cp {
    int p, q; // p + q w 
    cp(int _p = 0, int _q = 0) { p = _p, q = _q; }
    bool operator < (cs cp &a) cs { return p < a.p || (p == a.p && q < a.q); }
};
cp operator * (cs cp & a, cs cp &b) {
    return cp(add(mul(a.p, b.p), mul(w, mul(a.q, b.q))), add(mul(a.p, b.q), mul(a.q, b.p)));
}
cp ksm(cp a, ll b) {
    cp c(1, 0);
    for(; b; b >>= 1, a = a * a)
        if(b & 1) c = c * a; 
    return c; 
}

map <int, int> P; 
void Fac(int x) {
    for(int i = 2; i * i <= x; i++) {
        while(x % i == 0) P[i] ++, x /= i;
    }
    if(x > 1) P[x] ++; 
}

ll X, Y;
void exgcd(ll a, ll b) {
    if(!b) return X = 1, Y = 0, void();
    exgcd(b, a % b); ll x = Y, y = X - a / b * Y; X = x, Y = y; 
}
ll calc_inv(ll a, ll b) {
    a = a % b, exgcd(a, b); 
    return (X % b + b) % b; 
}
map <cp, int> mp; 
ll calc(ll a, ll b) {
    ll ans = 0; 
    for(auto r : P) {
        ll w = 1; 
        for(int i = 0; i < r.second; i++) w *= r.first; 
        // g ^ x (L / w) = a ^ (L / w) 
        cp z = ksm(cp(a, b), L / w);
        cp G = ksm(cp(gx, gy), L / w);
        // assert(ksm(z, w).p == 1 && ksm(z, w).q == 0);

        int B = sqrt(w) + 1; 
        mp.clear();
        cp cur(1, 0);
        for(int i = 0; i < B; i++) {
            mp[cur] = i; 
            cur = cur * G; 
        }
        cp f = z;
        ll xi = 0; 
        for(int i = 0; ; i++) {
            if(mp.count(f)) {// f * G ^ {Bi} = G ^ x 
                // cout << "BSGS : " << i << ' ' << B << ' ' << mp[f] << ' ' << w << endl;
                xi = (w + mp[f] - 1ll * i * B) % w;
                break;
            }
            f = f * cur; 
        }
        // crt : \sum xi * (Mi ^ -1) * Mi 
        ll inv = calc_inv(L / w, w);
        ans += mult(xi * inv % L, L / w);
        ans = ans % L; 
    }
    return ans; 
}

/*
lll x, y; 
void exgcd(lll a, lll b){
	if(!b) return x = 1, y = 0, void();
	exgcd(b, a % b); 
	lll _x = y, _y = x - a / b * y; x = _x, y = _y; 
}
*/



int main() {
    #ifdef FSYo
    freopen("1.in", "r", stdin);
    #endif

    int T; 
    cin >> T;
    while(T--) {
        int a, b; ll k; 
        scanf("%d%d%d%d%lld", &p, &a, &b, &w, &k);
        
        if(a == 0 && b == 0) {
            cout << 1 << ' ' << 0 << ' ' << 0 << '\n';
            continue; 
        }
        
        P.clear();
        // (p - 1) (p + 1) 
        Fac(p - 1); 
        Fac(p + 1);
        L = 1ll * (p - 1) * (p + 1);
        int x = rnd() % (p - 1) + 1;
        for(int y = 1; ; y++) {
            cp z(x, y);
            // cout << "check : " << x << ' ' << y << endl;
            bool ok = 1; 
            for(auto r : P) {
                int p = r.first; 
                cp t = ksm(z, L / p);
                if(t.p == 1 && t.q == 0) {
                    ok = 0; 
                    break;
                }
            }
            if(ok) {
                gx = x, gy = y; 
                break;
            }
        }
        //cout << "root : " << gx << ' ' << gy << endl; 
        // (a, b) 的指标
        ll Z = calc(a, b);
        // cout << "epsilon : " << Z << endl; 

        // cp r = ksm(cp(gx, gy), Z);
        // assert(r.p == a && r.q == b);


        // Z + t L = r K 
        ll ff = __gcd(k, L);
        if(Z % ff) {
            puts("0");
            continue; 
        }
        exgcd(L, k);
        Y = (Y % L + L) % L; 
        Y = mult(Y, Z / ff);
        cp ans = ksm(cp(gx, gy), Y);
        // cp ck = ksm(ans, k);
        // assert(ck.p == a && ck.q == b);
        cout << ff << ' ' << ans.p << ' ' << ans.q << '\n'; 
    }
    return 0; 
}