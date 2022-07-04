#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

const int mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline int po(int a,int b){
	int r=1;for(;b;b>>=1,Mul(a,a))
		if(b&1)Mul(r,a);
	return r;
}

const int N=6e5+7;

int n,m;int ans=1;
std::vector<int> G[N],T[N];

int low[N],dfn[N],dfc;
int st[N],tp,bct;

void tarjan(int u,int p){
	low[u]=dfn[u]=++dfc;st[++tp]=u;
	for(auto v:G[u])if(v!=p){
		if(dfn[v]){
			low[u]=min(low[u],dfn[v]);
		}else {
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				++bct;
				do{
					T[bct].push_back(st[tp]);
					T[st[tp]].push_back(bct);
				}while(st[tp--]!=v);
				T[bct].push_back(u);
				T[u].push_back(bct);
			}
		}
	}
}

int dp[N];

void dfs(int u,int p){
	dp[u]=1;
	for(auto v:T[u])if(v!=p){
		dfs(v,u);
		Mul(dp[u],(u<=n)+dp[v]);
	}if(u<=n)Inc(ans,dp[u]);
}

void Main(){
	cin>>n>>m;bct=n;
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}tarjan(1,0);dfs(1,0);
	cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}