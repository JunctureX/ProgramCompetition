#include <bits/stdc++.h>

using ll=long long;
using pii=std::pair<int,int>;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;
#define fi first
#define se second

const int N=1e6+7;

struct Seg{

static const int N=::N<<3|7;
int mx[N],n;

#define md ((l+r)>>1)
#define lc (u<<1)
#define rc (lc|1)
#define Lc lc,l,md
#define Rc rc,md+1,r

void init(int _n){
	n=_n;build(1,1,n);
}

void build(int u,int l,int r){
	mx[u]=-1e9;if(l==r)return;
	build(Lc);build(Rc);
}

void Ins(int p,int vl,int u,int l,int r){
	mx[u]=max(mx[u],vl);if(l==r)return;
	p<=md?Ins(p,vl,Lc):Ins(p,vl,Rc);
}

void Ins(int p,int vl){
//	cerr<<"Ins\n";
	Ins(p,vl,1,1,n);
//	cerr<<"Ins ok\n";
}

int qry(int qr,int u,int l,int r){
	if(r<=qr)return mx[u];
	if(qr<=md)return qry(qr,Lc);
	return max(qry(qr,Lc),qry(qr,Rc));
}

int qry(int qr){
	return qry(qr,1,1,n);
}

}T1,T2;

int n,m;
int a[N],b[N];
int sa[N],sb[N];
pii px[N],pz[N];

void Work(){
	cin>>n>>m;
//	cerr<<"n : "<<n<<" m : "<<m<<"\n";
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=m;++i)
		cin>>b[i];
	for(int i=1;i<=n;++i)
		sa[i]=sa[i-1]+(a[i]==2);
	for(int i=1;i<=m;++i)
		sb[i]=sb[i-1]+(b[i]==2);
	sa[n+1]=sa[n],sb[m+1]=sb[m];
	int Z=0;
	for(int &z=Z,ia=n+1,ib=m+1;;++z){
		pz[z]={ia--,ib--};
		while(ia&&a[ia]!=3)--ia;
		while(ib&&b[ib]!=3)--ib;
		if(ia<=0||ib<=0)break;
	}
	int X=0;
	for(int &x=X,ia=0,ib=0;;++x){
		px[x]={ia++,ib++};
		while(ia<=n&&a[ia]!=1)++ia;
		while(ib<=m&&b[ib]!=1)++ib;
		if(ia>n||ib>m)break;
	}int ans=0;
//	cerr<<"point deter\n";
	T1.init(n+m);T2.init(n+m);
//	cerr<<"???\n";
	for(int x=X,z=0;x>=0;--x){
		while(z<=Z&&pz[z].fi>px[x].fi&&pz[z].se>px[x].se){
			T1.Ins(sa[pz[z].fi]-sb[pz[z].se]+m,sa[pz[z].fi]+z);
			T2.Ins(sb[pz[z].se]-sa[pz[z].fi]+n,sb[pz[z].se]+z);
			++z;
		}
		ans=max(ans,T1.qry(sa[px[x].fi]-sb[px[x].se]+m)+x-sa[px[x].fi]);
		ans=max(ans,T2.qry(sb[px[x].se]-sa[px[x].fi]+n)+x-sb[px[x].se]);
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
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}