#include<bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;

const int mod=998244353;
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline int po(int a,int b){
	int r=1;for(;b;b>>=1,Mul(a,a))
		if(b&1)Mul(r,a);
	return r;
}

const int N=2e5+7;

int n,m;bool flag;
bool vs[N];
int col[N];
std::vector<int> G[N];

void dfs(int u,int c){
	vs[u]=true;col[u]=c;
	for(auto v:G[u])
		if(vs[v])flag&=(col[u]^col[v]);
		else dfs(v,c^1);
}

void Work(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		G[i].clear();
		col[i]=0;
		vs[i]=false;
	}for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int rk=n;
	for(int i=1;i<=n;++i){
		if(!vs[i]){
			flag=true;
			dfs(i,0);
			rk-=flag;
		}
	}
	cout<<po(5,m-rk)<<"\n";
}

void Main(){
	int T;cin>>T;
	cerr<<"T: "<<T<<"?\n";
	while(T--)
		Work();	
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}