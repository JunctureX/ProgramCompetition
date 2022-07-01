#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;

const int N=7e3+7;

struct edge{
	int v,c,r;
	edge(int _v,int _c,int _r):v(_v),c(_c),r(_r){}
};
std::vector<edge> G[N];
typedef std::vector<edge>::iterator iter;
iter cur[N];

void adde(int u,int v,int vl){
	if(!vl)return;
//	cerr<<"adde : "<<u<<" "<<v<<" "<<vl<<"\n";
	G[u].emplace_back(v,vl,G[v].size());
	G[v].emplace_back(u,0,G[u].size()-1);
}

bool finished;
int S,T,tot;
int lev[N],gap[N];
void BFS(){
	memset(lev,-1,sizeof(int)*(tot+1));
	memset(gap,0,sizeof(int)*(tot+1));
	lev[T]=gap[1]=1;std::queue<int> Q;
	Q.push(T);
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		cur[u]=G[u].begin();
		for(auto [v,c,r]:G[u])if(!~lev[v]){
			Q.push(v);++gap[lev[v]=lev[u]+1];
		}
	}
	finished=lev[S]==-1;
}

int dfs(int u,int flow){
	if(u==T)return flow;
	int ans=0;for(iter &e=cur[u];e!=G[u].end();++e){
		if(e->c&&lev[e->v]+1==lev[u]){
			int dlt=dfs(e->v,min(flow-ans,e->c));
			e->c-=dlt;G[e->v][e->r].c+=dlt;
			if((ans+=dlt)==flow)return ans;
		}
	}
	if(!--gap[lev[u]++])finished=true;
	++gap[lev[u]];cur[u]=G[u].begin();
	return ans;
}

int Flow(){
	int res=0;BFS();
	while(!finished)
		res+=dfs(S,1e9);
	return res;
}

const int M=50;

int n,m,a,b,c;

int bc[M][M],br[M][M];
int wc[M][M],wr[M][M];

void Main(){
	 cin>>n>>m>>a>>b>>c;
	 S=1,T=tot=2;
	 for(int i=1;i<=n;++i){
	 	for(int j=1;j<=m;++j){
	 		bc[i][j]=++tot;
	 		br[i][j]=++tot;
	 		wc[i][j]=++tot;
	 		wr[i][j]=++tot;
	 		adde(bc[i][j],T,a);
	 		adde(S,br[i][j],a);
	 		adde(S,wc[i][j],a);
	 		adde(wr[i][j],T,a);
	 	}
	 }
	 for(int i=1;i<=n;++i){
	 	for(int j=1;j<=m;++j){
	 		if(j<m){
	 			adde(bc[i][j],bc[i][j+1],b);
	 		//	adde(bc[i][j+1],bc[i][j],b);
	 			adde(wc[i][j+1],wc[i][j],b);
	 			//adde(wc[i][j],wc[i][j+1],b);
	 		}else {
			 	adde(bc[i][j],T,b);
			 	adde(S,wc[i][j],b);
			}
	 		if(i<n){
	 			adde(br[i+1][j],br[i][j],b);
	 			//adde(br[i][j],br[i+1][j],b);
	 			adde(wr[i][j],wr[i+1][j],b);
	 			//adde(wr[i+1][j],wr[i][j],b);
	 		}else {
	 			adde(S,br[i][j],b);
	 			adde(wr[i][j],T,b);
			 }
	 	}
	 }
	 for(int i=1;i<=n;++i){
	 	static char s[M];
	 	cin>>(s+1);
	 	for(int j=1;j<=m;++j){
	 		if(s[j]=='#'){
//	 			cerr<<"black\n";
	 			adde(br[i][j],bc[i][j],c);
	 			adde(S,wc[i][j],1e9);
	 			adde(wr[i][j],T,1e9);
	 		}else {
//	 			cerr<<"white\n";
	 			adde(bc[i][j],wr[i][j],c);
	 			adde(wc[i][j],br[i][j],c);
	 			adde(bc[i][j],br[i][j],1e9);
	 		}
	 	}
	 }
	 cout<<Flow()<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}