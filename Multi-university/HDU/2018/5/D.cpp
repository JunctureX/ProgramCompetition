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

int n,Q,ans,nn;
std::vector<int> G[N];
int anc[N];
std::vector<int> Ansp[N],Ans[N];
bool ban[N];int sz[N];
int tot,mxG,Gr;

void dfs_sz(int u,int p){
	sz[u]=1;for(auto v:G[u])
		if(v!=p&&!ban[v])dfs_sz(v,u),sz[u]+=sz[v];
}

void get_Gr(int u,int p){
	int mx=tot-sz[u];
	for(auto v:G[u])
		if(v!=p&&!ban[v])get_Gr(v,u),mx=max(mx,sz[v]);
	if(mxG>mx)mxG=mx,Gr=u;
}

void dfs_get(int u,int p,int d,std::vector<int> &vec){
	if(u<=n){
		while(d>=vec.size())vec.push_back(0);
		vec[d]++;
	}for(auto v:G[u])
		if(v!=p&&!ban[v])
			dfs_get(v,u,d+1,vec);
}

int build(int u){
	dfs_sz(u,0);tot=sz[u],mxG=tot,Gr=u;
	get_Gr(u,0);u=Gr;ban[u]=true;
	Ans[u].clear();Ans[u].push_back(u<=n);
//	cerr<<"build : "<<u<<"\n";
	for(auto v:G[u])if(!ban[v]){
		std::vector<int> tmp;
		tmp.push_back(0);
		dfs_get(v,u,1,tmp);
		if(Ans[u].size()<tmp.size())
			Ans[u].resize(tmp.size());
		for(size_t i=0;i<tmp.size();++i)
			Ans[u][i]+=tmp[i];
		for(size_t i=1;i<tmp.size();++i)
			tmp[i]+=tmp[i-1];
		int t=build(v);
		
		anc[t]=u,Ansp[t]=tmp;
	}for(size_t i=1;i<Ans[u].size();++i)
		Ans[u][i]+=Ans[u][i-1];
	return u;
}

int ps[N],nd[N],dfc,d[N];
int *hs=anc,fa[N];
int top[N];

void dfs1(int u,int p){
	sz[u]=1;fa[u]=p;d[u]=d[p]+1;hs[u]=0;
	for(auto v:G[u])if(v!=p)
		dfs1(v,u),sz[u]+=sz[v],sz[v]>sz[hs[u]]&&(hs[u]=v);
}

void dfs2(int u,int tp){
//	cerr<<"u : "<<u<<" tp : "<<tp<<" fa : "<<fa[u]<<"\n";
	top[u]=tp;nd[ps[u]=++dfc]=u;
	if(hs[u])dfs2(hs[u],tp);
	for(auto v:G[u])if(v!=fa[u]&&v!=hs[u])
		dfs2(v,v);
}

int LCA(int u,int v){
//	cerr<<"LCA: "<<u<<" "<<v<<"\n";
	while(top[u]!=top[v]){
		d[top[u]]<d[top[v]]?(v=fa[top[v]]):(u=fa[top[u]]);
//		cerr<<"u : "<<u<<" "<<fa[top[u]]<<" v : "<<v<<" "<<top[v]<<" "<<fa[top[v]]<<"\n";
	}
	
//	cerr<<"LCA: "<<u<<" "<<v<<"\n";
	return d[u]<d[v]?u:v;
}

int jump(int u,int k){
	while(d[u]-k<d[top[u]])
		k-=d[u]-d[top[u]]+1,u=fa[top[u]];
	return nd[ps[u]-k];
}

int Dis(int u,int v){
	return d[u]+d[v]-d[LCA(u,v)]*2;
}

int qry(std::vector<int> &vec,int k){
	if(k<0||vec.empty())return 0;
	return vec[min((size_t)k,vec.size()-1)];
}

int Qry(int p,int k){
	//cerr<<"Qry : "<<p<<" "<<k<<" ";
	int ans=0,u=p;
	while(p){
		ans+=qry(Ans[p],k-Dis(u,p));
		if(anc[u])
			ans-=qry(Ansp[p],k-Dis(u,anc[p]));
		p=anc[p];
	}
	//cerr<<"ans : "<<ans<<"\n";
	return ans;
}

int Query(int u,int v,int w){
	//cerr<<"Query : "<<u<<" "<<v<<" "<<w<<"\n";
	int D=Dis(u,v);
	if(D>w+w)return Qry(u,w)+Qry(v,w);
	if(d[u]<d[v])swap(u,v);
	int p=jump(u,D/2);
	//cerr<<"p : "<<p<<"\n";
	return Qry(u,w)+Qry(v,w)-Qry(p,w-D/2);
}

void Work(){
	for(int i=1;i<=nn;++i)
		G[i].clear();
	cin>>n>>Q;ans=0;nn=n;
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;++nn;
		G[u].push_back(nn);
		G[v].push_back(nn);
		G[nn].push_back(u);
		G[nn].push_back(v);
	}
	dfc=0;dfs1(1,0);dfs2(1,1);
	memset(ban,0,sizeof(bool)*(nn+1));
	memset(anc,0,sizeof(int)*(nn+1));
	for(int i=1;i<=nn;++i)
		Ans[i].clear(),Ansp[i].clear();
	tot=n,mxG=n,Gr=-1;
	int rt=build(1);
	//cerr<<"ans : " <<ans<<"\n";
//	cerr<<"???\n";
	while(Q--){
		int u,v,w;cin>>u>>v>>w;
		u=(u+ans)%n+1;
		v=(v+ans)%n+1;
		w=(w+ans)%n;w*=2;
//		cerr<<"???\n";
		ans=Query(u,v,w);
//		cerr<<"???\n";
		cout<<ans<<"\n";
	}
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