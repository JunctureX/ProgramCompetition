#include <bits/stdc++.h>

using ll=long long;
using ull=unsigned long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

const int N=5e5+7;

const int M=N<<2|7;

int mx[M];
#define lc (u<<1)
#define rc (lc|1)
#define md ((l+r)>>1)
#define Lc lc,l,md
#define Rc rc,md+1,r

void build(int u,int l,int r){
	mx[u]=-1e9;if(l==r)return;
	build(Lc);build(Rc);
}
void ins(int u,int l,int r,int ql,int qr,int t){
	if(ql<=l&&r<=qr){mx[u]=max(mx[u],t);return;}
	if(ql<=md)ins(Lc,ql,qr,t);
	if(md<qr)ins(Rc,ql,qr,t);
}
int qry(int u,int l,int r,int p){
	if(l==r)return mx[u];
	return max(mx[u],p<=md?qry(Lc,p):qry(Rc,p));
}

int n;
int a[N],nx[N],p[N],dp[N];

void Main(){
	cin>>n;
	a[n+1]=nx[n+1]=n+1;
	for(int i=1;i<=n;++i)
		cin>>a[i],p[a[i]]=i;
	for(int i=n;~i;--i){
		nx[i]=i+1;
		while(a[nx[i]]<=a[i])
			nx[i]=nx[nx[i]];
	}build(1,1,n);int ans=0;
	for(int i=0;i<=n;++i){
		int l=nx[p[i]],r=nx[l]-1,x=p[i];
		dp[x]=!x?0:(qry(1,1,n,x)+1);
		if(l<=r)ins(1,1,n,l,r,dp[x]);
		ans=max(ans,dp[x]);
	}cout<<n-ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}