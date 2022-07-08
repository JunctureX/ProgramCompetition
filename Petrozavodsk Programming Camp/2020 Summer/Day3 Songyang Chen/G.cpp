#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

const int N=2e5+7;

int n,k;

struct edge{int v,a,b;};
std::vector<edge> G[N];
ll f[N][30],x;
ll g[30];int sz[N];

void dfs(int u,int p){
	memset(f[u],0x3f,sizeof f[u]);
	f[u][0]=0;sz[u]=1;
	for(auto [v,a,b]:G[u])if(v!=p){
		dfs(v,u);
		for(int i=sz[v];i>=1;--i)
			f[v][i]=min(f[v][i]+b,f[v][i-1]+a);
		f[v][0]+=b;
		memset(g,0x3f,sizeof g);
		for(int i=0;i<sz[u];++i)
			for(int j=0;j<=sz[v]&&i+j<=k;++j)
				if(f[u][i]+f[v][j]<=x)
					g[i+j]=min(g[i+j],max(f[u][i],f[v][j]));
		sz[u]+=sz[v];
		sz[u]=min(sz[u],k+1);
		for(int i=0;i<sz[u];++i)
			f[u][i]=g[i];
	}
}

bool check(ll x){
//	cerr<<"check : "<<x<<"\n";
	::x=x;dfs(1,0);
	return f[1][k]<=x;
}

void Work(){
	cin>>n>>k;
	for(int i=1;i<n;++i){
		int u,v,a,b;
		cin>>u>>v>>a>>b;
		G[u].push_back({v,a,b});
		G[v].push_back({u,a,b});
	}
	ll l=0,r=1e18,m;
	while(l<r)
		check(m=(l+r)>>1)?r=m:l=m+1;
	cout<<l<<"\n";
	for(int i=1;i<=n;++i)
		G[i].clear();
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