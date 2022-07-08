#include<bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::max;

const int N=1e5+7;
int a[N];
int k,n;
ll ans;

void Work(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	std::sort(a+1,a+n+1);
	std::reverse(a+1,a+n+1);
	ans=*std::max_element(a+1,a+k+1);
	ll sum=0;
	for(int i=k+1;i<=n;++i)
		sum+=a[i];
	cout<<max(ans,sum)<<"\n";
}

void Main(){
	int T;cin>>T;
	while(T--)
		Work();
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}