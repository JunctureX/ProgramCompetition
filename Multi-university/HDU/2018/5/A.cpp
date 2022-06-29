#include <bits/stdc++.h>

using db=double;
using ll=long long;
using ull=unsigned long long;
using std::cin;
using std::cout;
using std::cerr;
using std::max;
using std::min;
using std::swap;

const int N=2e5+7;
const int Log=30;

int n,m;
struct edge{int u,v,w;};
std::vector<edge> E;
struct Edge{int v,w;};
std::vector<Edge> G[N];

int dfn[N],dfc,low[N];
int fa[N],bin[N][Log+1],fae[N];
int sz[N];

int gf(int u){
	while(u!=fa[u])
		u=fa[u]=fa[fa[u]];
	return u;
}

void tarjan(int u,int p){
//	cerr<<"tarjan : "<<u<<" "<<p<<"\n";
	dfn[u]=low[u]=++dfc;
	for(auto [v,w]:G[u]){
		if(!dfn[v]){
			fae[v]=w;fa[v]=u;
			tarjan(v,u);
			if(low[v]>dfn[u]){
				E.push_back({u,v,w});
		//		cerr<<"push edge : "<<u<<" "<<v<<"\n";
			}	
			low[u]=min(low[v],low[u]);
		}else if(p!=v){
			low[u]=min(low[u],dfn[v]);
			if(low[v]==dfn[u]){
				std::vector<edge> tmp;
				tmp.push_back({u,v,w});
	//			cerr<<"do loop: ";
				for(int q=v;q!=u;q=fa[q]){
					tmp.push_back({q,fa[q],fae[q]});
//					cerr<<q<<" ";
				}
//				cerr<<v<<"\n";
				for(size_t i=0;i+1<tmp.size();++i)
					if(tmp[i].w<tmp.back().w)
						swap(tmp[i],tmp.back());
				int tw=tmp.back().w;tmp.pop_back();
				for(auto e:tmp){
					e.w+=tw,E.push_back(e);
				}
			}
		}
	}
}

void Work(){
	cin>>n>>m;
	E.clear();
	for(int i=1;i<=n;++i)
		G[i].clear();
	for(int i=1;i<=m;++i){
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	memset(dfn,0,sizeof(int)*(n+1));
	memset(low,0,sizeof(int)*(n+1));
	memset(fa,0,sizeof(int)*(n+1));
	dfc=0;tarjan(1,0);
	for(int i=1;i<=n;++i){
		fa[i]=i,sz[i]=1;
		for(int j=0;j<=Log;j++)
			bin[i][j]=(i>>j)&1;
	}
	std::sort(E.begin(),E.end(),
		[](const edge &a,const edge &b){return a.w>b.w;});
	assert(E.size()==n-1);
	ull ans=0;
	for(auto [u,v,w]:E){
		u=gf(u),v=gf(v);
		assert(u!=v);
		for(int i=0;i<=Log;++i){
			int v1=bin[v][i];
			int v0=sz[v]-bin[v][i];
			int u1=bin[u][i];
			int u0=sz[u]-bin[u][i];
			if((w>>i)&1)
				ans+=((ll)v0*u0+(ll)v1*u1)<<i;
			else 
				ans+=((ll)v0*u1+(ll)v1*u0)<<i;
		}
		fa[v]=u;
		sz[u]+=sz[v];
		for(int i=0;i<=Log;++i)
			bin[u][i]+=bin[v][i];
		
	}
	cout<<ans<<"\n";
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