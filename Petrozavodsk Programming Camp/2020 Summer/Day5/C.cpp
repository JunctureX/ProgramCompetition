#include <bits/stdc++.h>

using ll=long long;
using pii=std::pair<int,int>;
using pip=std::pair<int,pii>;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;
#define fi first
#define se second

const int M=2e5+7;

int X[M+M],Xt;

struct Seg{

#define md ((l+r)>>1)
#define lc (u+1)
#define rc (u+((md-l+1)<<1))
#define Lc lc,l,md
#define Rc rc,md+1,r
#define Rt 1,0,Xt

static const int N=M<<2|7;

struct seg1{

ll mx[N];

seg1(){memset(mx,-0x3f,sizeof mx);}
void ins(int u,int l,int r,int p,ll vl){
	mx[u]=max(mx[u],vl);if(l==r)return;
	p<=md?ins(Lc,p,vl):ins(Rc,p,vl);
}

ll qry(int u,int l,int r,int qr){
	if(r<=qr)return mx[u];
	if(qr<=md)return qry(Lc,qr);
	return max(qry(Lc,qr),qry(Rc,qr));
}

}T1;

void ins1(int p,ll vl){
	T1.ins(Rt,p,vl);
}ll qry1(int p){
	return T1.qry(Rt,p);
}

struct seg2{

ll mx[N];

seg2(){memset(mx,-0x3f,sizeof mx);}
void ins(int u,int l,int r,int ql,int qr,ll vl){
	if(ql<=l&&r<=qr){
		mx[u]=max(mx[u],vl);
		return;
	}
	if(ql<=md)ins(Lc,ql,qr,vl);
	if(md<qr)ins(Rc,ql,qr,vl);
}

ll qry(int u,int l,int r,int p){
	if(l==r)return mx[u];
	return max(mx[u],p<=md?qry(Lc,p):qry(Rc,p));
}



}T2,T3;

void ins2(int l,int r,ll v){
	T2.ins(Rt,l,r,v);
}ll qry2(int p){
	return T2.qry(Rt,p);
}

void ins3(int l,int r,ll v){
	T3.ins(Rt,l,r,v);
}ll qry3(int p){
	return T3.qry(Rt,p);
}

}T[3];

struct seg{int l,r,c;};
std::vector<seg> vec;

ll ans=0;
int n,m;ll x,y;

void Main(){
	cin>>n>>m>>x>>y;
	for(int i=1;i<=m;++i){
		int c,l,r;cin>>c>>l>>r;--c,++r;
		vec.push_back({l,r,c});
		X[++Xt]=l,X[++Xt]=r;
	}std::sort(X+1,X+Xt+1);
	Xt=std::unique(X+1,X+Xt+1)-X-1;
	std::sort(vec.begin(),vec.end(),
		[](const seg &a,const seg &b){return a.r<b.r;});
	for(int i=0;i<1;++i)
		T[i].ins1(0,0);
	for(auto [l,r,c]:vec){
		int L=std::lower_bound(X,X+Xt,l)-X;
		int R=std::lower_bound(X,X+Xt,r)-X;
	//	cerr<<"l : "<<l<<" r : "<<r<<" c : "<<c<<"\n";
		int c1=(c+1)%3,c2=(c+2)%3;
	//	cerr<<"L : "<<L<<" R : "<<R<<"\n";
		ll res1=(r-l)*x+max({T[c1].qry1(L),T[c2].qry1(L),T[c].qry1(L)});
		ll res2=r*x+T[c].qry2(L);
		ll res3=r*x+l*(x+y)+max(T[c1].qry3(L),T[c2].qry3(L));
	//	cerr<<"qry : "<<l<<" "<<max(T[c1].qry3(l),T[c2].qry3(l))<<"\n";
	//	cerr<<res1<<" "<<res2<<" "<<res3<<"\n";
		ll res=max(res1,res2);res=max(res,res3);
	//	cerr<<"ins1 : "<<r<<" "<<res<<"\n";
		T[c].ins1(R,res);
	//	cerr<<"ins2 : "<<l<<" "<<r<<" "<<res-r*x<<"\n";
		T[c].ins2(L,R,res-r*x);
	//	cerr<<"ins3 : "<<l<<" "<<r<<" "<<res-r*(2*x+y)<<"\n";
		T[c].ins3(L,R,res-r*(2*x+y));
		ans=max(ans,res);
	}cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}