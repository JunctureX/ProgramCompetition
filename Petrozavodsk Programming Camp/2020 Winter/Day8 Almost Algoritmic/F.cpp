#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::cerr;
using std::max;

void Main(){
	int n,m;
	cin>>n>>m;
	if(m==3*n-6)
		puts("YES");
	else puts("NO");
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}