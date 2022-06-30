#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;

const int mod=1e9+7;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}
inline void Mul(int &a,int b){a=mul(a,b);}

const int N=5e2+7;
const int M=3e5+7;

int n,m;
int a[N],dp[M],F[M];

void Work(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	memset(dp,0,sizeof(int)*(m+1));
	dp[0]=1;
	for(int i=1,cur=0;i<=n;++i){
		cur=min(cur+a[i],m);
		for(int j=cur;j>=a[i];--j)
			Dec(dp[j],dp[j-a[i]]);
	}int ans=0;
	for(int i=0;i<=m;++i)
		Inc(ans,mul(dp[i],F[m-i]));
	cout<<ans<<"\n";
}

int G[M],g;

void Main(){
	for(int i=1;(3*i-1)*i/2<M;++i){
		G[g++]=i*(3*i-1)/2;
		G[g++]=i*(3*i+1)/2;
	}
	F[0]=1;
	for(int i=1;i<M;++i){
		for(int j=0;j<g&&G[j]<=i;++j)
			(j&2)?Dec(F[i],F[i-G[j]]):Inc(F[i],F[i-G[j]]);
	}
//	cout<<"F : ";
//	for(int n=1;n<=10;++n)
//		cout<<F[n]<<" ";
//	cout<<"\n";
	int T;cin>>T;while(T--)Work();
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}