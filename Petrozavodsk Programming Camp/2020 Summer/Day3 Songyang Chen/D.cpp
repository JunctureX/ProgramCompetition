#include <bits/stdc++.h>

using ll=long long;
using pii=std::pair<int,int>;
#define fi first
#define se second
using std::cin;
using std::cout;
using std::cerr;

const int mod=1e9+7,g=5;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}
inline void Mul(int &a,int b){a=mul(a,b);}

const int M=2e5+7;

int pw[M],pw_g[M];

namespace PST{

const int N=2e7+7;

int nw;
int hsh[N],hsg[N],sz[N],lc[N],rc[N];

#define md ((l+r)>>1)
#define Lc lc[u],l,md
#define Rc rc[u],md+1,r

void _copy(int &u){
	++nw;
	lc[nw]=lc[u];
	rc[nw]=rc[u];
	sz[nw]=sz[u];
	hsh[nw]=hsh[u];
	hsg[nw]=hsg[u];
	u=nw;
}

void ins(int &u,int l,int r,int p){
	_copy(u);++sz[u];
	Inc(hsh[u],pw[p]);
	Inc(hsg[u],pw_g[p]);
//	cerr<<"u : "<<u<<" "<<hsh[u]<<"\n";
	if(l==r)return;
	p<=md?ins(Lc,p):ins(Rc,p);
}

bool equal(int u,int v){
	return sz[u]==sz[v]&&hsh[u]==hsh[v]&&hsg[u]==hsg[v];
}

bool cmp(int u,int v,int l,int r){
	if(equal(u,v))return false;
	if(l==r)return sz[u]<sz[v];
	if(equal(rc[u],rc[v]))
		return cmp(lc[u],lc[v],l,md);
	return cmp(rc[u],rc[v],md+1,r);
}
#define L(u) pii(lc[u.fi],lc[u.se])
#define R(u) pii(rc[u.fi],rc[u.se])

bool equal(pii u,pii v){
	return sz[u.fi]+sz[u.se]==sz[v.fi]+sz[v.se]&&
		add(hsh[u.fi],hsh[u.se])==add(hsh[v.fi],hsh[v.se])&&
		add(hsg[u.fi],hsg[u.se])==add(hsg[v.fi],hsg[v.se]);
}

bool cmp(pii u,pii v,int l,int r){
	if(equal(u,v))return false;
	if(l==r)return sz[u.fi]+sz[u.se]<sz[v.fi]+sz[v.se];
	if(equal(R(u),R(v)))
		return cmp(L(u),L(v),l,md);
	return cmp(R(u),R(v),md+1,r);
}

int get(pii u){
	return add(hsh[u.fi],hsh[u.se]);
}
int get(int u){
	return hsh[u];
}

void clear(){
	nw=0;
}

}


const int N=4e2+7;

int n,Q,m;
int a[N][N];
int st[N][N],ed[N][N];
pii pr[N][N],sf[N][N];

void Work(){
	cin>>n>>Q;m=n*n;
	pw[0]=pw_g[0]=1;
	for(int i=1;i<=m;++i){
		pw[i]=mul(pw[i-1],m);
		pw_g[i]=mul(pw_g[i-1],g);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			cin>>a[i][j];
//		cerr<<i<<" "<<j<<" : "<<a[i][j]<<"\n";
		}
//	cerr<<"st : "<<"\n";
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
		//	cerr<<i<<" "<<j<<" : "<<PST::get(st[i][j])<<"\n";
			PST::ins(st[i][j],1,m,a[i][j]);
		//	cerr<<"diff : "<<a[i][j]<<" "<<pw[a[i][j]]<<"\n";
	//		cerr<<i<<" "<<j<<" : "<<PST::get(st[i][j])<<"\n";
			if(i<n&&PST::cmp(st[i+1][j],st[i][j],1,m))
				st[i+1][j]=st[i][j];
			if(j<n&&PST::cmp(st[i][j+1],st[i][j],1,m))
				st[i][j+1]=st[i][j];
		}
//	cerr<<"ed : "<<"\n";
	for(int i=n;i>=1;--i)
		for(int j=n;j>=1;--j){
//			cerr<<i<<" "<<j<<" : "<<PST::get(ed[i][j])<<"\n";
			int tmp=ed[i][j];
			PST::ins(tmp,1,m,a[i][j]);
			if(i>1&&PST::cmp(ed[i-1][j],tmp,1,m))
				ed[i-1][j]=tmp;
			if(j>1&&PST::cmp(ed[i][j-1],tmp,1,m))
				ed[i][j-1]=tmp;
		}
	for(int i=1;i<=n;++i){
		pr[i][0]={0,0};
		for(int j=1;j<=n;++j){
			pr[i][j]=PST::cmp(pr[i][j-1],{st[i][j],ed[i][j]},1,m)?
				pii(st[i][j],ed[i][j]):pr[i][j-1];
		}
	}
	for(int i=n;i>=1;--i){
		sf[i][n+1]={0,0};
		for(int j=n;j>=1;--j){
			sf[i][j]=PST::cmp(sf[i][j+1],{st[i][j],ed[i][j]},1,m)?
				pii(st[i][j],ed[i][j]):sf[i][j+1];
		}
	}
	while(Q--){
		int r1,r2,c1,c2;
		cin>>r1>>r2>>c1>>c2;
		if(PST::cmp(sf[r1-1][c2+1],pr[r2+1][c1-1],1,m)){
//			cerr<<"dn side\n";
			cout<<PST::get(pr[r2+1][c1-1])<<"\n";
		}else {
//			cerr<<"up side\n";
			cout<<PST::get(sf[r1-1][c2+1])<<"\n";
		}
	}
	PST::clear();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			pr[i][j]=sf[i][j]=pii(0,0);
			a[i][j]=0;
			st[i][j]=ed[i][j]=0;
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