#include <cstdio>
#include <vector>
#include <map>
#include <unordered_map>

using int64 = long long;
using uint64 = unsigned long long;

const int mod = 1e9 + 7;

std::unordered_map<uint64, int64> count;
std::vector<int> p;
int n;

int64 dfs(uint64 s, uint64 candidate) {
  int d = __builtin_popcountll(s);
  if (d == n) return 1;
  auto it = count.find(s);
  if (it != count.end()) {
    return it->second;
  }
  uint64 ns = s;
  ns = ((ns & 0xaaaaaaaaaaaaaaaaull) >>  1) | ((ns & 0x5555555555555555ull) <<  1);
  ns = ((ns & 0xccccccccccccccccull) >>  2) | ((ns & 0x3333333333333333ull) <<  2);
  ns = ((ns & 0xf0f0f0f0f0f0f0f0ull) >>  4) | ((ns & 0x0f0f0f0f0f0f0f0full) <<  4);
  ns = ((ns & 0xff00ff00ff00ff00ull) >>  8) | ((ns & 0x00ff00ff00ff00ffull) <<  8);
  ns = ((ns & 0xffff0000ffff0000ull) >> 16) | ((ns & 0x0000ffff0000ffffull) << 16);
  ns = ((ns & 0xffffffff00000000ull) >> 32) | ((ns & 0x00000000ffffffffull) << 32);
  int64 ret = 0;
  if (p[d] == -1) {
    for (uint64 mask = candidate; mask; ) {
      int i = __builtin_ctzll(mask);
      bool found = false;
      uint64 z = (i <= 31) ? (ns >> (63 - 2 * i)) : (ns << (2 * i - 63));
      z &= (uint64(1) << n) - 1;
      if ((z | s) == s) {
        s ^= uint64(1) << i;
        candidate ^= uint64(1) << i;
        ret += dfs(s, candidate);
        s ^= uint64(1) << i;
        candidate ^= uint64(1) << i;
      }
      mask ^= uint64(1) << i;
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
