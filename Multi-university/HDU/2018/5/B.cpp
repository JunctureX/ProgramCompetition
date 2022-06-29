#include <bits/stdc++.h>

using db=double;
using std::cin;
using std::cout;
using std::cerr;
using std::max;
using std::min;
using std::swap;

int st[10],n,k,m,mx,mn;

void dfs(int p,int cur,int tim){
	if(p==m){
		mn=min(mn,cur);
		mx=max(mx,cur);
		return;
	}
	dfs(p+1,cur*10+st[p],tim);
	if(tim==k)return;
	for(int i=p+1;i<m;++i){
		if(p==0&&st[i]==0)continue;
		swap(st[p],st[i]);
		dfs(p+1,cur*10+st[p],tim+1);
		swap(st[p],st[i]);
	}
}

void Work(){
	cin>>n>>k;
	m=0;mx=n,mn=n;
	while(n)
		st[m++]=n%10,n/=10;
	std::reverse(st,st+m);
	dfs(0,0,0);
	cout<<mn<<" "<<mx<<"\n";
}

void Main(){
	int T;cin>>T;
	while(T--)
		Work();
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
	cout<<std::fixed<<std::setprecision(10);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}