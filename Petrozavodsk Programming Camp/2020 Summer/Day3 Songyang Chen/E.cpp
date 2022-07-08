#include <bits/stdc++.h>

#define int ll
using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

const int N=1e4+7;
const ll LINF=0x3f3f3f3f3f3f3f3f;

int S,T,tot;
struct edge{int v,r,c;ll w;};
typedef std::vector<edge>::iterator iter;
std::vector<edge>G[N];
iter cur[N];
void adde(int u,int v,int c,ll w){
	G[u].push_back({v,G[v].size(),c,w});
	G[v].push_back({u,G[u].size()-1,0,-w});
}

ll dis[N];bool vs[N];
bool SPFA(){
	memset(dis+1,0x3f,sizeof(ll)*tot);
	memset(vs+1,0,sizeof(bool)*tot);
	std::deque<int> Q(1,S);dis[S]=0;
	while(!Q.empty()){
		int u=Q.front();Q.pop_front();
		vs[u]=false;cur[u]=G[u].begin();
		for(auto [v,r,c,w]:G[u])
			if(c&&dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!vs[v]){
					vs[v]=true;
					(!Q.empty()&&dis[v]<dis[Q.front()])?
						Q.push_front(v):
						Q.push_back(v);
				}
			}
	}
	return dis[T]<LINF;
}

int dfs(int u,int flow){
	if(u==T)return flow;
	vs[u]=true;int ans=0;
	for(iter &e=cur[u];e!=G[u].end();++e){
		auto& [v,r,c,w]=*e;
		if(c&&!vs[v]&&dis[v]==dis[u]+w){
			int dlt=dfs(v,min(flow-ans,c));
			if(!dlt){vs[v]=true;continue;}
			c-=dlt;G[v][r].c+=dlt;
			if((ans+=dlt)==flow)break;
		}
	}vs[u]=false;return ans;
}

std::unordered_map<int,int> id;
int gid(int x){
	if(id.find(x)!=id.end())
		return id[x];
	id[x]=++tot;
	adde(tot,T,1,0);
	return tot;
}

void clear(){
	for(int i=1;i<=tot;++i)
		G[i].clear();
	tot=0;id.clear();
	
}

int a[N],b[N],c[N];
void Work(){
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a[i]>>b[i]>>c[i];
	}
	S=n+1,T=n+2,tot=n+2;
	for(int i=1;i<=n;++i)
		adde(S,i,1,0);
	for(int i=1;i<=n;++i){
		int x=-b[i]/2/a[i];
		x=max((int)1,min(x,m));
		for(int j=max((int)1,x-n);j<=min(m,x+n);++j)
			adde(i,gid(j),1,(ll)a[i]*j*j+(ll)b[i]*j+c[i]);
	}int flow=0;ll cost=0;
	while(SPFA()){
		int dlt=dfs(S,1e9);
		for(int i=1;i<=dlt;++i){
			++flow;cost+=dis[T];
			cout<<cost<<" ";
		}
	}cout<<"\n";
	clear();
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