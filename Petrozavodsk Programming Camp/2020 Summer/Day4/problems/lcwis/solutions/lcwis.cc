#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

const int MAXN = 1e6 + 10;
const int MM = 1e9 + 7;

const int DEBUG = 0;

struct Seq{
    int n;
    int d[MAXN];
    int Z[MAXN], T[MAXN], f0, f2;
    int O[MAXN];
    void Init() {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &d[i]); d[i]--;
        }
        f0 = 0, f2 = 0;
        O[0] = 0;
        Z[0] = 0;
        T[0] = n;
        for (int i = 1; i <= n; i++) {
            if (d[i] == 0) Z[++f0] = i;
            O[i] = O[i - 1] + (d[i] == 1);
        }
        for (int i = n; i >= 1; i--)
            if (d[i] == 2) T[++f2] = i;
        Z[f0 + 1] = n + 1;
        T[f2 + 1] = 0;

        if (DEBUG) {   
            for (int i = 1; i <= n; i++) cout << d[i] << ' '; cout << endl;
            for (int i = 1; i <= f0; i++) cout << Z[i] << ' '; cout << endl;
            for (int i = 1; i <= f2; i++) cout << T[i] << ' '; cout << endl;   
        }

        assert(f0 + f2 + O[n] == n);
    }
} A, B;

struct node {
    int score;
    int sur;
    int prev;
    int next;
} Q[MAXN * 10];
int sz, tag_p, tag_n;
int scr_p, scr_n;
vector<node> sur_zero;

int ans, f0, f2;

int score(int k, int p, int q) {
    return k + min(A.O[p] - A.O[A.Z[k]], B.O[q] - B.O[B.Z[k]]);
}

int surplus(int k, int p, int q) {
    return (A.O[p] - A.O[A.Z[k]]) - (B.O[q] - B.O[B.Z[k]]);
}

void Add(int scr, int sur) {
    if (DEBUG) cout << "============================== " << scr << ' ' << sur << "      ::      " << scr_p << ' ' << scr_n << ' ' << tag_p << ' ' << tag_n << endl;
    // for (int x = 0; x != 1; x = Q[x].next) 
    //     cout << "(" << Q[x].score << ',' << Q[x].sur << "), "; cout << "(" << Q[1].score << ',' << Q[1].sur << "), "; cout << endl;
    // for (int x = 2; x != 3; x = Q[x].next) 
    //     cout << "(" << Q[x].score << ',' << Q[x].sur << "), "; cout << "(" << Q[3].score << ',' << Q[3].sur << "), "; cout << endl;
    if (sur == 0) {
        if (sur_zero.empty()) {
            sur_zero.push_back((node){scr, sur, 0, 0});
        }
        else {
            if (scr > sur_zero[0].score) {
                sur_zero.clear();
                sur_zero.push_back((node){scr, sur, 0, 0});
            }
        }
        return ;
    }
    if (sur > 0) {
        scr -= scr_p;
        sur -= tag_p;
        int now = 0;
        while (Q[now].sur < sur) {
            now = Q[now].next;
        }
        if (DEBUG) cout << "POS :: " << now << ' ' << Q[now].sur << ' ' << sur << endl;
        if (Q[now].sur == sur) {
            if (Q[now].score > scr) ;
            else {
                Q[now].score = scr;
                int pre = Q[now].prev;
                while (Q[pre].score <= Q[now].score) {
                    Q[Q[pre].prev].next = now;
                    Q[now].prev = Q[pre].prev;
                    pre = Q[now].prev;
                }
            }
        }
        else {
            if (scr > Q[now].score) {
                int pre = Q[now].prev;
                int y = sz;
                sz++;
                Q[pre].next = y;
                Q[y].next = now;
                Q[now].prev = y;
                Q[y].prev = pre;
                Q[y].score = scr, Q[y].sur = sur;
                now = y;
                while (Q[pre].score <= Q[now].score) {
                    Q[Q[pre].prev].next = now;
                    Q[now].prev = Q[pre].prev;
                    pre = Q[now].prev;
                }
            }
        }
        return ;
    }
    if (sur < 0) {
        scr -= scr_n;
        sur -= tag_n;
        int now = 2;
        while (Q[now].sur > sur) {
            now = Q[now].next;
        }
        if (Q[now].sur == sur) {
            if (Q[now].score > scr) ;
            else {
                Q[now].score = scr;
                int pre = Q[now].prev;
                while (Q[pre].score <= Q[now].score) {
                    Q[Q[pre].prev].next = now;
                    Q[now].prev = Q[pre].prev;
                    pre = Q[now].prev;
                }
            }
        }
        else {
            if (scr > Q[now].score) {
                int pre = Q[now].prev;
                int y = sz;
                sz++;
                Q[pre].next = y;
                Q[y].next = now;
                Q[now].prev = y;
                Q[y].prev = pre;
                Q[y].score = scr, Q[y].sur = sur;
                now = y;
                while (Q[pre].score <= Q[now].score) {
                    Q[Q[pre].prev].next = now;
                    Q[now].prev = Q[pre].prev;
                    pre = Q[now].prev;
                }
            }
        }
        return ;
    }
    // for (int x = 0; x != 1; x = Q[x].next) 
    //     cout << "(" << Q[x].score << ',' << Q[x].sur << "), "; cout << endl;
    // for (int x = 2; x != 3; x = Q[x].next) 
    //     cout << "(" << Q[x].score << ',' << Q[x].sur << "), "; cout << endl;
    // cout << "============================== " << scr << ' ' << sur << "      ::      " << scr_p << ' ' << scr_n << ' ' << tag_p << ' ' << tag_n << endl;
}

void solve(int casi){
    //printf("Case #%d:", casi);
    scanf("%d%d", &A.n, &B.n);
    //cout << "??????????????????????????????????????????????????????????????????????" << endl;
    A.Init();
    B.Init();
    f0 = min(A.f0, B.f0);
    f2 = min(A.f2, B.f2);
    A.T[f2 + 1] = B.T[f2 + 1] = 0;
    A.Z[f0 + 1] = A.n + 1;
    B.Z[f0 + 1] = B.n + 1;
    ans = max(f0, f2);
    ans = max(ans, min(A.n - A.f0 - A.f2, B.n - B.f0 - B.f2));
    sz = 4;
    Q[0] = (node){MM, -MM, -1, 1};
    Q[1] = (node){-MM, MM, 0, -1};
    Q[2] = (node){MM, MM, -1, 3};
    Q[3] = (node){-MM, -MM, 2, -1};
    tag_n = tag_p = 0;
    scr_p = scr_n = 0;
    sur_zero.clear();
    for (int j = f2, k = 0; j >= 0; j--) {
        // Update
        for (int i = A.T[j + 1] + 1; i <= A.T[j]; i++)
            if (A.d[i] == 1) {
                tag_n++;
                tag_p++;
                scr_n++;
                if (DEBUG) cout << "A plus :: " << tag_p << ' ' << tag_n << ' ' << sur_zero.size() << endl;
                if (sur_zero.size()) {
                    if (Q[0].next == 1 || sur_zero[0].score > Q[Q[0].next].score + scr_p) {
                        int x = Q[0].next, y = sz;
                        sz++;
                        Q[0].next = y;
                        Q[y].next = x;
                        Q[x].prev = y;
                        Q[y].prev = 0;
                        Q[y].score = sur_zero[0].score - scr_p;
                        Q[y].sur = 1 - tag_p;
                    }
                    sur_zero.clear();
                }
                if (Q[2].next != 3 && Q[Q[2].next].sur + tag_n == 0) {
                    int x = Q[2].next, y = Q[x].next;
                    sur_zero.push_back(Q[Q[2].next]);
                    sur_zero.back().score += scr_n;
                    Q[2].next = y;
                    Q[y].prev = 2;
                }
            }
        for (int i = B.T[j + 1] + 1; i <= B.T[j]; i++)
            if (B.d[i] == 1) {
                tag_n--;
                tag_p--;
                scr_p++;
                if (DEBUG) cout << "B plus :: " << tag_p << ' ' << tag_n << ' ' << sur_zero.size() << endl;
                if (sur_zero.size()) {
                    if (Q[2].next == 3 || sur_zero[0].score > Q[Q[2].next].score + scr_n) {
                        int x = Q[2].next, y = sz;
                        sz++;
                        Q[2].next = y;
                        Q[y].next = x;
                        Q[x].prev = y;
                        Q[y].prev = 2;
                        Q[y].score = sur_zero[0].score - scr_n;
                        Q[y].sur = -1 - tag_n;
                    }
                    sur_zero.clear();
                }
                if (Q[0].next != 1 && Q[Q[0].next].sur + tag_p == 0) {
                    int x = Q[0].next, y = Q[x].next;
                    sur_zero.push_back(Q[Q[0].next]);
                    sur_zero.back().score += scr_p;
                    Q[0].next = y;
                    Q[y].prev = 0;
                }
            }
        // 
        while (k <= f0 && A.Z[k] <= A.T[j] && B.Z[k] <= B.T[j]) {
            double scr = score(k, A.T[j], B.T[j]);
            double sur = surplus(k, A.T[j], B.T[j]);
            // cout << "ADDD  ::  " << k << ' ' << A.T[j] << ' ' << B.T[j] << endl;
            k++;
            Add(scr, sur);
        }
        if (Q[0].next != 1) {
            int x = Q[0].next;
            ans = max(ans, Q[x].score + scr_p + j);
        }
        if (Q[2].next != 3) {
            int x = Q[2].next;
            ans = max(ans, Q[x].score + scr_n + j);
        }
        if (sur_zero.size()) {
            ans = max(ans, sur_zero[0].score + j);
        }
        if (DEBUG) {
            cout << j << ' ' << k << ' ' << ans << ' ' << scr_p << ' ' << scr_n << ' ' << tag_p << ' ' << tag_n << endl;
            for (int x = 0; x != 1; x = Q[x].next) 
                cout << "(" << Q[x].score << ',' << Q[x].sur << "), "; cout << "(" << Q[1].score << ',' << Q[1].sur << "), "; cout << endl;
            if (sur_zero.size()) {
                cout << sur_zero[0].score << endl;
            }
            else {
                cout << endl;
            }
            for (int x = 2; x != 3; x = Q[x].next) 
                cout << "(" << Q[x].score << ',' << Q[x].sur << "), "; cout << "(" << Q[3].score << ',' << Q[3].sur << "), "; cout << endl;

            cout << "++++++   ";
            for (int x = 0; x != 1; x = Q[x].next) 
                cout << "(" << Q[x].score + scr_p << ',' << Q[x].sur + tag_p << "), "; cout << "(" << Q[1].score << ',' << Q[1].sur << "), "; cout << endl;
            cout << "++++++   ";
            vector<PDD> tmp;
            for (int k = 0; A.Z[k] <= A.T[j] && B.Z[k] <= B.T[j]; k++) {
                tmp.push_back(PDD(surplus(k, A.T[j], B.T[j]), score(k, A.T[j], B.T[j])));
            }
            sort(tmp.begin(), tmp.end());
            for (auto &x : tmp) 
                if (x.first >= 0)
                    cout << "(" << x.second << ',' << x.first << "), "; cout << endl;
            cout << ans << endl;
        }
    }
    printf("%d\n", ans);
}

int main(){
    int T = 1;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        solve(i);
    return 0;
}
