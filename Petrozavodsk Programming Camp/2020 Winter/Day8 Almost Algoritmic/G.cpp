#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::cerr;
using std::max;

const int N=1e5+7;

void Main(){
	int n;cin>>n;int ans=0;
	for(int i=1;i<=n;++i){
		int a;cin>>a;
		ans=max(ans,a-i+1);
	}
	cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}