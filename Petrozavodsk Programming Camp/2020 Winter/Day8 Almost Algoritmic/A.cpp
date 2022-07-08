#include <bits/stdc++.h>

using ll=long long;
using ull=unsigned long long;
using pii=std::pair<int,int>;
#define fi first
#define se second
using std::cout;
using std::cerr;
using std::min;

namespace IO{

inline char gc(){
	static const int Rlen=1<<22|1;static char buf[Rlen],*p1,*p2;
	return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,Rlen,stdin),p1==p2)?EOF:*p1++;
}template<typename T>T get_integer(){
	char c;while(!isdigit(c=gc()));T x=c^48;
	while(isdigit(c=gc()))x=x*10+(c^48);
	return x;
}inline int gi(){return get_integer<int>();}

}using IO::gi;

const int N=2e6+7;

int nl,nr,m;
int L[N],R[N];
int dl[N],dr[N];
int dx[N],dy[N];
int U[N],V[N],reL[N];
std::vector<pii> G[N];
int vs[N],d;

bool BFS(){
	std::queue<int> Q;
	memset(dl,0,(nl+1)<<2);
	memset(dr,0,(nr+1)<<2);
	for(int i=1;i<=nl;++i)
		if(!L[i])Q.push(i),dl[i]=1;
	d=1e9;
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		if(dl[u]>d)break;
		for(auto [v,id]:G[u])
			if(!dr[v]){
				dr[v]=dl[u]+1;
				if(!R[v])d=dr[v];
				else {
					dl[R[v]]=dr[v]+1;
					Q.push(R[v]);
				}
			}
		
	}
	return d<1e9;
}

bool dfs(int u){
	for(auto [v,id]:G[u]){
		if(!vs[v]&&dr[v]==dl[u]+1){
			vs[v]=true;
			if(!R[v]||dfs(R[v])){
				L[R[v]=u]=v;
				reL[u]=id;
				return true;
			}
		}
	}return false;
}

void Main(){
	nl=gi(),nr=gi(),m=gi();
	for(int i=1;i<=m;++i){
		int &u=U[i]=gi();
		int &v=V[i]=gi();
		G[u].push_back({v,i});
	}int ans=0;
	for(int len=0;len<=19&&(BFS(),d<=20);++len){
		memset(vs,0,sizeof(*vs)*(nr+1));
		for(int i=1;i<=nl;++i)
			if(!L[i]&&dfs(i))++ans;
	}cout<<ans<<"\n";
	for(int i=1;i<=nl;++i)
		if(reL[i])cout<<reL[i]<<"\n";
}

inline void File(){
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}