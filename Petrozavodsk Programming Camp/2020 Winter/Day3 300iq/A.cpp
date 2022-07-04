#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;
using std::swap;

const int mod=998244353,gr=3;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline int po(int a,int b){
	int r=1;for(;b;b>>=1,Mul(a,a))
		if(b&1)Mul(r,a);
	return r;
}inline void ex_gcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return;}ex_gcd(b,a%b,y,x);y-=a/b*x;
}inline int Inv(int a){
	int x,y;ex_gcd(mod,a,y,x);
	return x+(x>>31&mod);
}

namespace NTT{

const int bit=20;
const int SIZE=1<<bit|7;

int r[SIZE],*w[bit+1];

void init_omega(){
	for(int i=1;i<=bit;++i)
		w[i]=new int[1<<(i-1)];
	int wn=po(gr,(mod-1)>>bit);
	w[bit][0]=1;
	for(int i=1;i<(1<<(bit-1));++i)
		w[bit][i]=mul(w[bit][i-1],wn);
	for(int i=bit-1;i;--i)
		for(int j=0;j<(1<<(i-1));++j)
			w[i][j]=w[i+1][j<<1];
}

int inv[SIZE],fac[SIZE],ifc[SIZE];
void init_fac(){
	fac[0]=inv[0]=ifc[0]=1;
	fac[1]=inv[1]=ifc[1]=1;
	for(int i=2;i<SIZE;++i){
		fac[i]=mul(fac[i-1],i);
		inv[i]=mul(mod-mod/i,inv[mod%i]);
		ifc[i]=mul(ifc[i-1],inv[i]);
	}
}

int len,inv_len;
void init_len(int deg){
	int l=1;while(l<deg)l<<=1;
	len=l;inv_len=Inv(l);
	for(int i=1;i<l;++i)
		r[i]=r[i>>1]>>1|((i&1)?l>>1:0);
}void DFT(int *A){
	for(int i=1;i<len;++i)
		if(i<r[i])swap(A[i],A[r[i]]);
	for(int i=1,d=1;i<len;i<<=1,d++)
		for(int j=0;j<len;j+=i<<1)
			for(int k=0;k<i;++k){
				int &t1=A[j+k],&t2=A[i+j+k];
				int t=mul(t2,w[d][k]);
				t2=dec(t1,t);Inc(t1,t);
			}
}void IDFT(int *A){
	DFT(A);std::reverse(A+1,A+len);
	for(int i=0;i<len;++i)
		Mul(A[i],inv_len);
}

}

namespace TDC{

const int N=3e5+7;

int n,x;

std::vector<int> G[N];

namespace ST{

const int N=TDC::N<<1|7;
int st[20][N],Log[N];
int nd[N],d[N],ps[N],dfc;

void dfs(int u,int p){
	d[u]=d[p]+1;st[0][ps[u]=++dfc]=u;
	for(auto v:G[u])if(v!=p)dfs(v,u),st[0][++dfc]=u;
}int mnp(int u,int v){
	return d[u]<d[v]?u:v;
}void build(){
	dfs(1,0);
	for(int i=2;i<=dfc;++i)
		Log[i]=Log[i-1]+!(i&(i-1));
	for(int i=1;i<=Log[dfc];++i)
		for(int j=1;j+(1<<i)-1<=dfc;++j)
			st[i][j]=mnp(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}int LCA(int u,int v){
	int l=ps[u],r=ps[v];
	if(l>r)swap(l,r);
//	cerr<<"l : "<<l<<" r : "<<r<<"\n";
	int t=Log[r-l+1];//cerr<<"t : "<<t<<"\n";
	return mnp(st[t][l],st[t][r-(1<<t)+1]);
}int Dis(int u,int v){
	//cerr<<"Dis "<<u<<" "<<v<<"\n";
	//cerr<<"LCA : "<<LCA(u,v)<<"\n";
	//cerr<<"dis : "<<d[u]+d[v]-2*d[LCA(u,v)]<<"\n";
	return d[u]+d[v]-2*d[LCA(u,v)];
}

}
using ST::LCA;
using ST::Dis;

struct Fenwick{
	std::vector<int> vec;int n;
	Fenwick(){n=0;}
	void init(int _n){n=_n+1;vec.resize(n+1);}
	void add(int p,int v){
		for(++p;p<=n;p+=p&-p)
			vec[p]+=v;
	}int qry(int p){
		int r=0;for(p=min(p+1,n);p>0;p&=p-1)
			r+=vec[p];
		return r;
	}
};

int rt,mxG,tot,Gr;
int sz[N],anc[N];
bool ban[N];
Fenwick Ans[N],Ansp[N];

void get_sz(int u,int p){
	sz[u]=1;for(auto v:G[u])
		if(v!=p&&!ban[v])
			get_sz(v,u),sz[u]+=sz[v];
}

void find_gr(int u,int p){
	int mx=tot-sz[u];
	for(auto v:G[u])
		if(v!=p&&!ban[v])
			find_gr(v,u),mx=max(mx,sz[v]);
	if(mx<mxG)mxG=mx,Gr=u;
}

int get_d(int u,int p){
	int d=0;for(auto v:G[u])
		if(!ban[v]&&v!=p)
			d=max(d,get_d(v,u)+1);
	return d;
}

int build(int u){
	get_sz(u,0);
	tot=mxG=sz[u],Gr=u;
	find_gr(u,0);u=Gr;
	ban[u]=true;int mxd=0;
	for(auto v:G[u])if(!ban[v]){
		int d=get_d(v,u)+1;
		mxd=max(mxd,d);
		int t=build(v);
	//	cerr<<"link : "<<t<<" "<<u<<"\n";
		anc[t]=u,Ansp[t].init(d);
	}Ans[u].init(mxd);
//	cerr<<"gen rt : "<<u<<"\n";
	return u;
}

void Ins(int u){
//	cerr<<"Ins : "<<u<<"\n";
	int p=u;
	while(p){
//		cerr<<"ins : "<<p<<" "<<Dis(p,u)<<"\n";
		Ans[p].add(Dis(p,u),1);
		if(anc[p]){
			Ansp[p].add(Dis(anc[p],u),1);
//			cerr<<"insp : "<<p<<" "<<Dis(anc[p],u)<<"\n";
		}
		p=anc[p];
	}
}

int Qry(int u,int x){
	int p=u,ans=0;
//	cerr<<"u : "<<u<<" x : "<<x<<"\n";
	while(p){
//		cerr<<"qry : "<<p<<" "<<x-Dis(u,p)<<" "<<Ans[p].qry(x-Dis(u,p))<<"\n";
		ans+=Ans[p].qry(x-Dis(u,p));
		if(anc[p]){
			ans-=Ansp[p].qry(x-Dis(anc[p],u));
//			cerr<<"qryp : "<<p<<" "<<x-Dis(u,anc[p])<<" "<<Ansp[p].qry(x-Dis(anc[p],u))<<"\n";
		}
		p=anc[p];
	}
//	cerr<<"Qry : "<<u<<" "<<ans<<"\n";
	return ans;
}

int C[N];

void work(){
	ST::build();rt=build(1);
	memset(ban,false,sizeof ban);
	std::queue<int> Q;Q.push(1);
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		ban[u]=true;
		C[Qry(u,x)]++;Ins(u);
		for(auto v:G[u])
			if(!ban[v])Q.push(v);
	}
}

}

using namespace NTT;
using namespace TDC;

int A[SIZE],B[SIZE];

void Main(){
	cin>>n>>x;
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}TDC::work();
	init_omega();init_fac();
	init_len(n+n);
	for(int i=0;i<=n;++i)
		A[i]=mul(C[i],fac[i]);
	std::reverse(A,A+n+1);
	//for(int i=0;i<=n;++i){
	//	cerr<<A[i]<<" ";
	//}cerr<<"\n";
	for(int i=0;i<=n;++i)
		B[i]=ifc[i];
	DFT(A),DFT(B);
	for(int i=0;i<len;++i)
		Mul(A[i],B[i]);
	IDFT(A);
	for(int k=0;k<n;++k)
		cout<<mul(A[n-k],ifc[k])<<" ";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}