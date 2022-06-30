#include<bits/stdc++.h>

using int64 = long long;
using uint64 = unsigned long long;
using float80 = long double;
using namespace std;
const int MM = 1e9 + 7;

// mod should be not greater than 2^62 (about 4e18)
// return a * b % mod when mod is less than 2^31
inline uint64 mul_mod(uint64 a, uint64 b, uint64 mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  uint64 k = (uint64)((long double)a * b / mod);
  uint64 res = a * b - k * mod;
  if ((int64)res < 0) res += mod;
  return res;
}

inline int64 add_mod(int64 x, int64 y, int64 mod) {
  return (x + y) % mod;
}

inline int64 sub_mod(int64 x, int64 y, int64 mod) {
  return (x - y + mod) % mod;
}

int64 pow_mod(int64 a, int64 n, int64 m) {
  int64 res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

// ax + by = gcd(a, b), |x| + |y| is minimum
void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

// return x, where ax = 1 (mod mod)
int64 mod_inv(int64 a, int64 mod) {
  if (gcd(a, mod) != 1) return -1;
  int64 b = mod, s = 1, t = 0;
  while (b) {
    int64 q = a / b;
    std::swap(a -= q * b, b);
    std::swap(s -= q * t, t);
  }
  return s < 0 ? s + mod : s;
}

uint64 crt2(uint64 r1, uint64 mod1, uint64 r2, uint64 mod2) {
  uint64 inv = mod_inv(mod1, mod2);
  return mul_mod(r2 + mod2 - r1,  inv, mod2) * mod1 + r1;
}

//ax + by = c,x >= 0, x is minimum
//xx = x + t * b, yy = y - t * a
bool linear_equation(int64 a, int64 b, int64 c, int64 &x, int64 &y) {
  int64 g;
  exgcd(a,b,g,x,y);
  if (c % g) return false;
  b /= g, a /= g, c /= g;
  x = (x % b * (c % b) % b + b) % b;
  y = (c - a * x) / b;
  return true;
}

int64 euler_phi(int64 n) {
  int64 ret = n;
  for (int64 i = 2; i * i <= n; ++i) if (n % i == 0) {
    ret = ret / i * (i - 1);
    while (n % i == 0) n /= i;
  }
  if (n > 1) ret = ret / n * (n - 1);
  return ret;
}

namespace fft {
  const int N = 1 << 21, M = 31768;
  struct Complex {
    double x , y;
    Complex () {x = y = 0;}
    Complex (double _x , double _y) {x = _x , y = _y;}
    Complex operator + (const Complex& r) const {
      return Complex(x + r.x , y + r.y);
    }
    Complex operator - (const Complex& r) const {
      return Complex(x - r.x , y - r.y);
    }
    Complex operator * (const double k) const {
      return Complex(x * k, y * k);
    }
    Complex operator / (const double k) const {
      return Complex(x / k, y / k);
    }
    Complex operator * (const Complex& r) const {
      return Complex(x * r.x - y * r.y , x * r.y + y * r.x);
    }
    int operator = (const int a) {
      *this = Complex(a , 0);
      return a;
    }
    Complex conj() const {
      return Complex(x, -y);
    }
  };
  const double pi = acos(-1.0);
  Complex w[N];
  int rev[N];
  void init(int L) {
    int n = 1 << L;
    for (int i = 0 ; i < n ; ++ i) {
      double ang = 2 * pi * i / n;
      w[i] = Complex(cos(ang) , sin(ang));
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
  }
  void trans(Complex P[], int n, int oper) {
    for (int i = 0 ; i < n ; i ++) {
      if (i < rev[i]) {
        std::swap(P[i], P[rev[i]]);
      }
    }
    for (int d = 0; (1 << d) < n; d++) {
      int m = 1 << d, m2 = m * 2 , rm = n / m2;
      for (int i = 0; i < n; i += m2) {
        for (int j = 0; j < m; j++) {
          Complex &P1 = P[i + j + m], &P2 = P[i + j];
          Complex t = w[rm * j] * P1;
          P1 = P2 - t;
          P2 = P2 + t;
        }
      }
    }
    if (oper == -1) {
      for (int i = 0; i < n; ++i) {
        P[i] = P[i] / n;
      }
    }
  }
  Complex A[N] , B[N] , C1[N] , C2[N];
  std::vector<int64> conv(const std::vector<int> &a, const std::vector<int> &b) {
    int n = a.size(), m = b.size(), L = 0, s = 1;
    while (s <= n + m - 2) s <<= 1, ++L;
    init(L);
    for (int i = 0; i < s; ++i) {
      A[i] = i < n ? Complex(a[i], 0) : Complex();
      B[i] = i < m ? Complex(b[i], 0) : Complex();
    }
    trans(A, s, 1);
    trans(B, s, 1);
    for (int i = 0; i < s; ++i) {
      A[i] = A[i] * B[i];
    }
    for (int i = 0; i < s; ++i) {
      w[i] = w[i].conj();
    }
    trans(A, s, -1);
    std::vector<int64> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
      res[i] = (int64)(A[i].x + 0.5);
    }
    return res;
  }
  std::vector<int64> fast_conv(const std::vector<int> &a, const std::vector<int> &b) {
    int n = a.size(), m = b.size(), L = 0, s = 1;
    for (; s <= n + m - 2; s <<= 1, ++L);
    s >>= 1, --L;
    init(L);
    for (int i = 0; i < s; ++i) {
      A[i].x = (i << 1) < n ? a[i << 1] : 0;
      B[i].x = (i << 1) < m ? b[i << 1] : 0;
      A[i].y = (i << 1 | 1) < n ? a[i << 1 | 1] : 0;
      B[i].y = (i << 1 | 1) < m ? b[i << 1 | 1] : 0;
    }
    trans(A, s, 1); trans(B, s, 1);
    for (int i = 0; i < s; ++i) {
      int j = (s - i) & (s - 1);
      C1[i] = (Complex(4, 0) * (A[j] * B[j]).conj() - (A[j].conj() - A[i]) * (B[j].conj() - B[i]) * (w[i] + Complex(1, 0))) * Complex(0, 0.25);
    }
    std::reverse(w + 1, w + s);
    trans(C1, s, -1);
    std::vector<int64> res(n + m);
    for (int i = 0; i <= (n + m - 1) / 2; ++i) {
      res[i << 1] = int64(C1[i].y + 0.5);
      res[i << 1 | 1] = int64(C1[i].x + 0.5);
    }
    res.resize(n + m - 1);
    return res;
  }
  // arbitrary modulo convolution
  int conv(int a[], int b[], int n, int m, int mod, int res[], int umi=-1) {
    int s = 1, L = 0;
    while (s <= n + m - 2) s <<= 1, ++L;
    init(L);
    for (int i = 0; i < s; ++i) {
      A[i] = i < n ? Complex(a[i] / M, a[i] % M) : Complex();
      B[i] = i < m ? Complex(b[i] / M, b[i] % M) : Complex();
    }
    trans(A, s, 1); trans(B, s, 1);
    for (int i = 0; i < s; ++i) {
      int j = i ? s - i : i;
      Complex a1 = (A[i] + A[j].conj()) * Complex(0.5, 0);
      Complex a2 = (A[i] - A[j].conj()) * Complex(0, -0.5);
      Complex b1 = (B[i] + B[j].conj()) * Complex(0.5, 0);
      Complex b2 = (B[i] - B[j].conj()) * Complex(0, -0.5);
      Complex c11 = a1 * b1 , c12 = a1 * b2;
      Complex c21 = a2 * b1 , c22 = a2 * b2;
      C1[j] = c11 + c12 * Complex(0, 1);
      C2[j] = c21 + c22 * Complex(0, 1);
    }
    trans(C1, s, -1); trans(C2, s, -1);
    if (umi != -1) {
        int i = min(umi, n + m - 2);
        int x = int64(C1[i].x + 0.5) % mod;
        int y1 = int64(C1[i].y + 0.5) % mod;
        int y2 = int64(C2[i].x + 0.5) % mod;
        int z = int64(C2[i].y + 0.5) % mod;
        return ((int64)x * M * M + (int64)(y1 + y2) * M + z) % mod; 
    }
    for (int i = 0 ; i < n + m - 1; ++i) {
      int x = int64(C1[i].x + 0.5) % mod;
      int y1 = int64(C1[i].y + 0.5) % mod;
      int y2 = int64(C2[i].x + 0.5) % mod;
      int z = int64(C2[i].y + 0.5) % mod;
      res[i] = ((int64)x * M * M + (int64)(y1 + y2) * M + z) % mod;
    }
    return 0;
  }
}

using fft::N;

namespace Poly {// aint64 n should be power of 2
  int tmp1[N], tmp2[N], tmp3[N], mod;
  // res = 1 / poly
  void inv(int poly[], int res[], int n) {
    int deg = n - 1;
    std::vector<int> degs;
    while (deg > 0) {
      degs.push_back(deg);
      deg >>= 1;
    }
    std::reverse(degs.begin(), degs.end());
    res[0] = pow_mod(poly[0], mod - 2, mod);
    deg = 1;
    for (int t: degs) {
      fft::conv(poly, res, t + 1, deg, mod, tmp1);
      fft::conv(res, tmp1 + deg, t + 1 - deg, t + 1 - deg, mod, tmp1);
      for (int i = 0; i < t + 1 - deg; ++i) {
        res[i + deg] = mod - tmp1[i];
      }
      deg = t + 1;
    }
  }
}

int A0[N], B0[N], C0[N];
int64 P[N], dp[N];
int g[1000];

void prepare(int N) {
    for (int i = 0; i < 900; ++ i) {
        int k = (i & 1) ? -i / 2 - 1 : i / 2 + 1;
        g[i] = k * (3 * k - 1) / 2;
    }
    P[0] = 1;
    for (int n = 1, m = 0; n < N; ++ n) {
        while (g[m] <= n) ++m;
        for (int i = 0; i < m; ++i) {
            if ((i >> 1) & 1) P[n] -= P[n - g[i]];
            else P[n] += P[n - g[i]];
        }
        P[n] = (P[n] % MM + MM) % MM;
    }
}

void upd(int64 &x, int64 y) {
    x += y;
    if (x >= MM) x -= MM;
}

void solve(int casi){
    int _n, _m;
    scanf("%d%d", &_n, &_m);
    for (int i = 1; i <= _m; i++) dp[i] = 0;
    dp[0] = 1;
    for (int i = 1; i <= _n; i++) {
        int x;
        scanf("%d", &x);
        for (int j = x; j <= _m; j++) {
            upd(dp[j], dp[j - x]);
        }
    }
    int m = _m + 1;
    int n = m * 2 - 1;
    int p = 1;
    while (p < m << 1) p <<= 1;
    for (int i = 0; i < m; i++) A0[i] = dp[i];
    for (int i = m; i < p; i++) A0[i] = 0;
    Poly::inv(A0, B0, m);
    for (int i = m; i < p; i++) B0[i] = 0;
    for (int i = 0; i < m; i++) A0[i] = P[i];
    for (int i = m; i < p; i++) A0[i] = 0;
    printf("%d\n", fft::conv(A0, B0, p, p, MM, C0, m - 1));
}

int main(){
    int T = 1;
    scanf("%d", &T);
    prepare(300010);
    Poly::mod = MM;
    for (int i = 1; i <= T; i++)
        solve(i);
    return 0;
}
