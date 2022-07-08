#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

const int N=51;

int n,m;

struct mat{
	int a[N][N];
	mat(){memset(a,0x3f,sizeof a);}
	int* operator[](int o){
		return a[o];
	}
	const int* operator[](int o)const{
		return a[o];
	}
};

mat operator*(const mat &A,const mat &B){
	mat C;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n;++k)
				C[i][k]=min(C[i][k],A[i][j]+B[j][k]);
	return C;
}

const int M=1e2+7;

mat G;
mat F[M],f[M];


void Work(){
	cin>>n>>m;
	G=mat();
	for(int i=1;i<=n;++i)
		G[i][i]=0;
	F[0]=f[0]=G;
	for(int i=1;i<=n;++i)
		G[i][i]=0x3f3f3f3f;
	for(int i=1;i<=m;++i){
		int u,v,w;
		cin>>u>>v>>w;
		G[u][v]=min(G[u][v],w);
	}
	for(int i=1;i<=100;++i)
		f[i]=f[i-1]*G;
	mat temp=f[100];
	for(int i=1;i<=100;++i)
		F[i]=F[i-1]*temp;
	for(int i=0;i<=100;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n;++k)
				temp[j][k]=min(temp[j][k],f[i][j][k]);
	for(int i=0;i<=100;++i)
		f[i]=f[i]*temp;
	int Q;cin>>Q;
	while(Q--){
		int s,t,k;
		cin>>s>>t>>k;
		int lk=k/100,rk=k%100;
		int ans=1e9;
		for(int u=1;u<=n;++u){
			ans=min(ans,F[lk][s][u]+f[rk][u][t]);
		}
		if(ans>2e8)
			cout<<-1<<"\n";
		else 
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
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}