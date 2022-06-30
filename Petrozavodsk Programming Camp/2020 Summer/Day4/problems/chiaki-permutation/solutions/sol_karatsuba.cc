#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#include <unordered_map>

using int64 = long long;
using uint64 = unsigned long long;

const int mod = 1e9 + 7;

uint64 tb[256][256];
std::map<uint64, int64> count;
std::vector<int> p;
int n;

uint64 conv16(uint64 x, uint64 y) {
  return tb[x & 255][y & 255] | ((tb[x & 255][y >> 8] | tb[x >> 8][y & 255]) << 8) | ((tb[x >> 8][y >> 8]) << 16);
}

uint64 conv32(uint64 x, uint64 y) {
  return conv16(x & 65535, y & 65535) | 
         ((conv16(x & 65535, y >> 16) | conv16(x >> 16, y & 65535)) << 16) | 
         ((conv16(x >> 16, y >> 16)) << 32);
}

int64 dfs(uint64 s, uint64 candidate) {
  int d = __builtin_popcountll(s);
  if (d == n) return 1;
  auto it = count.find(s);
  if (it != count.end()) {
    return it->second;
  }
  int64 ret = 0;
  if (p[d] == -1) {
    uint64 ns = s ^ ((uint64(1) << n) - 1);
    uint64 x1 = s >> 32, y1 = s & 4294967295;
    uint64 x2 = ns >> 32, y2 = ns & 4294967295;
    uint64 a = conv32(x1, x2);
    uint64 b = conv32(x1, y2) | conv32(x2, y1);
    uint64 c = conv32(y1, y2);
    for (int j = 0; j < n; ++j) if (candidate >> j & 1) {
      int i = j * 2;
      bool found = false;
      if (i < 64) found = (c >> i & 1) | (b << 32 >> i & 1);
      else found = (a >> (i - 64) & 1) | (b >> 32 >> (i - 64) & 1);
      i >>= 1;
      if (!found) {
        s ^= uint64(1) << i;
        candidate ^= uint64(1) << i;
        ret += dfs(s, candidate);
        s ^= uint64(1) << i;
        candidate ^= uint64(1) << i;
      }
    }
  } else {
    bool found = false;
    int l = std::max(p[d] * 2 - n + 1, 0);
    int r = std::min(n - 1, p[d] * 2);
    for (int j = l; j <= r && !found; ++j) {
      found |= (s >> j & 1) && (~s >> (p[d] * 2 - j) & 1);
    }
    if (!found) {
      s ^= uint64(1) << p[d];
      ret += dfs(s, candidate);
      s ^= uint64(1) << p[d];
    }
  }
  return count[s] = ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < 256; ++j) {
      for (int k = 0; k < 8; ++k) if (i >> k & 1) {
        tb[i][j] |= j << k;
      }
    }
  }
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    p.resize(n);
    uint64 candidate = (uint64(1) << n) - 1;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &p[i]);
      --p[i];
      if (p[i] == -1) {
        ++cnt;
      } else {
        candidate ^= uint64(1) << p[i];
      }
    }
    count.clear();
    int64 ret = 1;
    for (int i = 1; i <= cnt; ++i) {
      ret = ret * i % mod;
    }
    ret -= dfs(0, candidate);
    ret = (ret % mod + mod) % mod;
    printf("%lld\n", ret);
  }
  return 0;
}
