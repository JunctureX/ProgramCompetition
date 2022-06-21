#include<bits/stdc++.h>

using ll=long long;
using std::string;
using pii=std::pair<int,int>;
using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::max;

const int N=2e5+7;

namespace SGT{

const int N=::N<<4|7;

ll ad[N],mx[N];

#define md ((l+r)>>1)
#define lc (u<<1)
#define rc (lc|1)
#define Lc lc,l,md
#define Rc rc,md+1,r

void pushadd(int u,ll w){
	ad[u]+=w,mx[u]+=w;
}void pushdn(int u){
	pushadd(lc,ad[u]);
	pushadd(rc,ad[u]);
	ad[u]=0;
}void pushup(int u){
	mx[u]=max(mx[lc],mx[rc]);
}

void Add(int u,int l,int r,int ql,int qr,ll w){
	if(ql<=l&&r<=qr)
		return pushadd(u,w);
	pushdn(u);
	if(ql<=md)Add(Lc,ql,qr,w);
	if(md<qr)Add(Rc,ql,qr,w);
	pushup(u);
}

void Mx(int u,int l,int r,int p,ll vl){
	if(l==r){mx[u]=max(mx[u],vl);return;}
	pushdn(u);
	p<=md?Mx(Lc,p,vl):Mx(Rc,p,vl);
	pushup(u);
}

}

#define Rt 1,0,nn+1
int n,nn,x[N];

struct node{int l,r,a,w;}nd[N];
std::vector<node> weak[N],strong[N];
ll ans[N];

void Main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		int l,r,a,w;
		cin>>l>>r>>a>>w;
		++r;
		nd[i]={l,r,a,w};
		x[++nn]=l,x[++nn]=r;
	}
	std::sort(x+1,x+nn+1);
	nn=std::unique(x+1,x+nn+1)-x-1;
	for(int i=1;i<=n;++i){
		nd[i].l=std::lower_bound(x+1,x+nn+1,nd[i].l)-x;
		nd[i].r=std::lower_bound(x+1,x+nn+1,nd[i].r)-x;
		nd[i].a?strong[nd[i].r].push_back(nd[i]):weak[nd[i].l].push_back(nd[i]);
	}
	for(int i=0;i<=nn+1;++i){
		for(auto [l,r,a,w]:strong[i])
			SGT::Add(Rt,0,l,w);
		SGT::Mx(Rt,i,ans[i]);
		ans[i]=SGT::mx[1];
		for(auto [l,r,a,w]:weak[i]){
			ans[r]=max(ans[r],ans[i]+w);
		}
	}
	cout<<SGT::mx[1];
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}