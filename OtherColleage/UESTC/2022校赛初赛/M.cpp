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

const int N=2e5+7;

int n,a[N],b[N],nn;
int nx[N],el[N],rt[N];
struct node{int a,b,c;}ans[N];

namespace SGT{

const int N=::N*20+7;
int lc[N],rc[N],sz[N],nw;

#define md ((l+r)>>1)
#define Lc lc[u],l,md
#define Rc rc[u],md+1,r

void ins(int &u,int l,int r,int p){
	if(!u)u=++nw;++sz[u];
	if(l==r)return;
	p<=md?ins(Lc,p):ins(Rc,p);
}
void merge(int &u,int v){
	if(!u||!v){u|=v;return;}
	sz[u]+=sz[v];
	merge(lc[u],lc[v]);
	merge(rc[u],rc[v]);
}
int qry(int u,int l,int r,int ql,int qr){
	if(!u||(ql<=l&&r<=qr))return sz[u];
	if(qr<=md)return qry(Lc,ql,qr);
	if(md<ql)return qry(Rc,ql,qr);
	return qry(Lc,ql,qr)+qry(Rc,ql,qr);
}

}
using namespace SGT;

void dfs(int u){
	for(int v=el[u];v;v=nx[v]){
		dfs(v);merge(rt[u],rt[v]);
	}
	if(a[u]>1)
		ans[u].a=qry(rt[u],1,nn,1,a[u]-1);
	ans[u].b=qry(rt[u],1,nn,a[u],a[u]);
	if(a[u]<nn)
		ans[u].c=qry(rt[u],1,nn,a[u]+1,nn);
	ins(rt[u],1,nn,a[u]);
}

void Main(){
	n=gi();
	for(int i=2;i<=n;++i){
		int f=gi();
		nx[i]=el[f];
		el[f]=i;
	}for(int i=1;i<=n;++i){
		a[i]=b[i]=gi();
	}std::sort(b+1,b+n+1);
	nn=std::unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;++i){
		a[i]=std::lower_bound(b+1,b+nn+1,a[i])-b;
	}dfs(1);
	for(int i=1;i<=n;++i){
		cout<<ans[i].a<<" "<<ans[i].b<<" "<<ans[i].c<<"\n";
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}