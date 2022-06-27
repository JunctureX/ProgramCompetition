#include <bits/stdc++.h>

using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::swap;

const int N=1e5+7;
std::vector<int> G[N];

int n,Q;

struct atom{
	int mn,lf,rf;
	bool empty;int len;
	atom(int _mn,int _lf,int _rf,bool _e,int _l)
		:mn(_mn),lf(_lf),rf(_rf),empty(_e),len(_l){}
	atom(){
		mn=1e9,lf=0,rf=0;
		empty=true;len=0;
	}
};

atom operator+(const atom &a,const atom &b){
	if(a.empty&&b.empty){
		return (atom){(int)1e9,0,0,true,a.len+b.len+1};
	}if(a.empty){
		return (atom){b.mn,a.len+1+b.lf,b.rf,false,0};
	}if(b.empty){
		return (atom){a.mn,a.lf,a.rf+b.len+1,false,0};
	}return (atom){min(min(a.mn,b.mn),a.rf+b.lf+1),a.lf,b.rf,false,0};
}

namespace PST{

const int N=::N*40;

int lc[N],rc[N],nw;
atom sm[N];
#define md ((l+r)>>1)
#define Lc lc[u],l,md
#define Rc rc[u],md+1,r

atom emptycell(int l,int r){
	atom tmp=atom();
	tmp.len=r-l;
	return tmp;
}

atom getatom(int u,int l,int r){
	if(u)return sm[u];
	return emptycell(l,r);
}

void pushup(int u,int l,int r){
	sm[u]=getatom(Lc)+getatom(Rc);
}

void ins(int &u,int l,int r,int p){
	if(!u)u=++nw;
	if(l==r){
		sm[u]=atom();
		sm[u].empty=false;
		return;
	}p<=md?ins(Lc,p):ins(Rc,p);
	pushup(u,l,r);
}

void del(int &u,int l,int r,int p){
	if(l==r){
		sm[u]=atom();return;
	}p<=md?del(Lc,p):del(Rc,p);
	pushup(u,l,r);
}

atom qry(int u,int l,int r,int ql,int qr){
//	cerr<<"u : "<<ql<<" "<<qr<<"\n";
	if(ql<=l&&r<=qr){
		if(!u)return emptycell(l,r);
		return sm[u];
	}if(qr<=md)return qry(Lc,ql,qr);
	if(md<ql)return qry(Rc,ql,qr);
	return qry(Lc,ql,qr)+qry(Rc,ql,qr);
}

}

int fa[N],d[N],top[N];
int in[N],nd[N],dfc;
int hs[N],sz[N];

void dfs1(int u,int p){
	fa[u]=p,d[u]=d[p]+1;
	for(auto v:G[u])if(v!=p){
		dfs1(v,u);sz[u]+=sz[v];
		if(sz[hs[u]]<sz[v])hs[u]=v;
	}++sz[u];
}

void dfs2(int u,int tp){
	top[u]=tp;
	nd[in[u]=++dfc]=u;
	if(hs[u]){
		dfs2(hs[u],tp);
	}else return;
	for(auto v:G[u])if(v!=hs[u]&&v!=fa[u]){
		dfs2(v,v);
	}
}

int col[N],rt[N];

atom rev(atom t){
	swap(t.lf,t.rf);
	return t;
}

int Query(int u,int v,int co){
//	cerr<<"Q : "<<u<<" "<<v<<"\n";
	atom t1,t2;
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])
			swap(u,v),swap(t1,t2);
//		cerr<<u<<" "<<v<<"\n";
//		cerr<<in[top[u]]<<" "<<in[u]<<"\n";
		t1=PST::qry(rt[co],1,n,in[top[u]],in[u])+t1;
		
		u=fa[top[u]];
	}
//	cerr<<"u : "<<u<<" v : "<<v<<"\n";
	if(d[u]>d[v])
		swap(u,v),swap(t1,t2);
	t2=PST::qry(rt[co],1,n,in[u],in[v])+t2;
	t1=rev(t1)+t2;
	int ans=t1.mn;
	
	
	if(ans>n)
		return -1;
	else return ans;
}

void Main(){
	cin>>n>>Q;
	for(int i=1;i<=n;++i)
		cin>>col[i];
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
//	cerr<<"???\n";
	dfs1(1,0);dfs2(1,1);
	assert(dfc==n);
	for(int i=1;i<=n;++i){
		PST::ins(rt[col[i]],1,n,in[i]);
	}
//	cerr<<"???\n";
	while(Q--){
		char c;cin>>c;
//		cerr<<"c : "<<c<<"\n";
		if(c=='Q'){
			int u,v,co;
			cin>>u>>v>>co;
			cout<<Query(u,v,co)<<"\n";
		}else {
			int u,co;cin>>u>>co;
			PST::del(rt[col[u]],1,n,in[u]);
			col[u]=co;
			PST::ins(rt[col[u]],1,n,in[u]);
		}
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif	
}signed main(){File();Main();return 0;}