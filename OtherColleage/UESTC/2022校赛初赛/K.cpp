#include<bits/stdc++.h>

namespace IO{

inline char gc(){
	static const int Rlen=1<<22|1;static char buf[Rlen],*p1,*p2;
	return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,Rlen,stdin),p1==p2)?EOF:*p1++;
}template<typename T>T get_integer(){
	char c;bool f=false;while(!isdigit(c=gc()))f=c=='-';T x=c^48;
	while(isdigit(c=gc()))x=((x+(x<<2))<<1)+(c^48);
	return f?-x:x;
}inline int gi(){return get_integer<int>();}

}using namespace IO;

using pii=std::pair<int,int>;
using std::cin;
using std::cerr;
using std::cout;

const int N=1e5+7;

std::vector<pii> G[N];

int n,m;bool flag=true;
int dis[N],vs[N];

void dfs(int u){
	vs[u]=true;
	for(auto [v,w]:G[u]){
		if(vs[v]){
			flag=flag&&(dis[v]^dis[u]^w)==0;
		}else{
			dis[v]=dis[u]^w;
			dfs(v);
		}
	}
}

void Work(){
	n=gi();m=gi();
	for(int i=1;i<=n;++i)
		G[i].clear(),vs[i]=false;
	for(int i=1;i<=m;++i){
		int u=gi(),v=gi(),w=gi();
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}flag=true;dfs(1);
	cout<<(flag?"Yes":"No")<<"\n";
}

void Main(){
	int T;T=gi();
	while(T--)
		Work();
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}