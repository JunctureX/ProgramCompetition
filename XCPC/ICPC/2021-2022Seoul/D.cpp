#include <bits/stdc++.h>

using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::bitset;

const int N=1e3+7;

int n,m;
int g[N][N];
std::vector<int> G[N];

bool flag;
int c[2],vs[N];
int col[N];
std::bitset<1024> S;

void dfs(int u,int C){
	++c[C];col[u]=C;vs[u]=true;
	for(auto v:G[u]){
		if(vs[v]){
			
			if(col[v]!=col[u]^1){
		//		cerr<<"u : "<<u<<" v : "<<v<<" conflict\n";
				flag=false;
				return;
			}
		}else {
			dfs(v,C^1);
		}
	}
}

void Main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		g[u][v]=g[v][u]=true;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			if(i!=j&&!g[i][j]){
		//		cerr<<i<<" "<<j<<"\n";
				G[i].push_back(j);
			}
	}
	S[0]=1;
	for(int i=1;i<=n;++i){
		if(!vs[i]){
			c[0]=c[1]=0;
			flag=true;
			dfs(i,0);
		//	cerr<<"fds : "<<i<<"\n";
			if(!flag){
				puts("-1");
				return;
			}
			S=(S<<c[0])|(S<<c[1]);
		}
	}
	int ans=n;
	for(int i=0;i<=n;++i)
		if(S[i])
			ans=min(ans,abs(n-i-i));
	cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif	
}signed main(){File();Main();return 0;}