#include <cstdio>
#include <vector>
#include <algorithm>

int lcwis(std::vector<int> &a, std::vector<int> &b) {
  int n = a.size(), m = b.size();
  std::vector<int> sa2(n + 1), sb2(m + 1);
  for (int i = n - 1; i >= 0; --i) {
    sa2[i] = sa2[i + 1] + (a[i] == 2);
  }
  for (int i = m - 1; i >= 0; --i) {
    sb2[i] = sb2[i + 1] + (b[i] == 2);
  }
  std::vector<int> pa1, pa3, pb1, pb3;
  for (int i = 0; i < n; ++i) {
    if (a[i] == 1) pa1.push_back(i);
    if (a[i] == 3) pa3.push_back(i);
  }
  for (int i = 0; i < m; ++i) {
    if (b[i] == 1) pb1.push_back(i);
    if (b[i] == 3) pb3.push_back(i);
  }
  pa3.push_back(n);
  pb3.push_back(m);
  std::reverse(pa3.begin(), pa3.end());
  std::reverse(pb3.begin(), pb3.end());
  int ret = 0;
  for (int j = 0; j < pa3.size() && j < pb3.size(); ++j) {
    ret = std::max(ret, j + std::min(sa2[0] - sa2[pa3[j]], sb2[0] - sb2[pb3[j]]));
  }
  for (int i = 0; i < pa1.size() && i < pb1.size(); ++i) {
    ret = std::max(ret, i + 1 + std::min(sa2[pa1[i]], sb2[pb1[i]]));
    for (int j = 0; j < pa3.size() && j < pb3.size(); ++j) {
      if (pa1[i] < pa3[j] && pb1[i] < pb3[j]) {
        ret = std::max(ret, i + 1 + j);
        ret = std::max(ret, i + 1 + j + std::min(sa2[pa1[i]] - sa2[pa3[j]], sb2[pb1[i]] - sb2[pb3[j]]));
      }
    }
  }
  ret = std::max(ret, std::min<int>(pa1.size(), pb1.size()));
  ret = std::max(ret, std::min<int>(pa3.size(), pb3.size()) - 1);
  ret = std::max(ret, std::min(sa2[0], sb2[0]));
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
    printf("%d\n", lcwis(a, b));
  }
  return 0;
}
