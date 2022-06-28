#include <bits/stdc++.h>

#define int ll
using ll=unsigned long long;
using ull=unsigned long long;
using pii=std::pair<int,int>;
using pil=std::pair<int,ll>;
using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::max;

const int N=2e5+7;

ll W[N];
char s[N];int n;
ull Ans[N];

void merge_base(std::vector<ll> &a,const std::vector<ll> &b){
	std::vector<ll> c;
	static ll lb[60];
	memset(lb,0,sizeof lb);
	auto ins=[&c](ll w){
		ll tw=w;
		bool flag=false;
		for(int i=58;~i;--i)
			if((1ll<<i)&w){
				if(lb[i])
					w^=lb[i];
				else {
					lb[i]=w,flag=true;
					break;
				}
			}
		if(flag)c.push_back(tw);
	};
	size_t ia=0,ib=0;
	while(ia<a.size()&&ib<b.size())
		ins(a[ia]>b[ib]?a[ia++]:b[ib++]);
	while(ia<a.size())ins(a[ia++]);
	while(ib<b.size())ins(b[ib++]);
	a=c;
}

namespace SAM{

const int N=::N<<1|7;
int sn[N][26],fa[N],len[N],sz[N],nw,rt;
int bin[N],nd[N];
int anc[21][N];
std::vector<ll> vec[N];

void clear(){
	memset(sn,0,sizeof sn);
	memset(fa,0,sizeof fa);
	memset(sz,0,sizeof sz);
	memset(len,0,sizeof len);
	memset(nd,0,sizeof nd);
	memset(anc,0,sizeof anc);
	memset(bin,0,sizeof bin);
	memset(Ans,0,sizeof Ans);
	for(int i=1;i<=nw;++i)
		vec[i].clear();
	nw=rt=0;
}

void init(int n){
	for(int i=1;i<=n;++i)
		len[i]=i,sz[i]=1;
	nw=rt=n+1;
}void push_back(int i,int c){
	int p=(i-1)?(i-1):rt;
	for(;p&&!sn[p][c];p=fa[p])
		sn[p][c]=i;
	if(!p)fa[i]=rt;
	else if(len[sn[p][c]]==len[p]+1)
		fa[i]=sn[p][c];
	else {
		int nq=++nw,q=sn[p][c];
		memcpy(sn[nq],sn[q],sizeof sn[q]);
		len[nq]=len[p]+1,fa[nq]=fa[q],fa[q]=fa[i]=nq;
		for(;p&&sn[p][c]==q;p=fa[p])sn[p][c]=nq;
	}
}


void build(){
	for(int i=1;i<=nw;++i)
		++bin[len[i]];
	for(int i=1;i<=nw;++i)
		bin[i]+=bin[i-1];
	for(int i=1;i<=nw;++i)
		nd[bin[len[i]]--]=i;
	for(int i=nw;i;--i){
		sz[fa[nd[i]]]+=sz[nd[i]];
		merge_base(vec[nd[i]],{W[sz[nd[i]]]});
		merge_base(vec[fa[nd[i]]],vec[nd[i]]);		
	//cerr<<"\n";
	//	cerr<<"sz : "<<sz[nd[i]]<<" ;";
	//	cerr<<nd[i]<<" : ";
		for(auto w:vec[nd[i]]){
			Ans[nd[i]]+=w;
	//		cerr<<w<<" ";
		}//cerr<<"\n";
//		cerr<<"u : "<<nd[i]<<"  : "<<Ans[nd[i]]<<"\n";
	}
	for(int i=1;i<=nw;++i)
		anc[0][i]=fa[i];
	for(int i=0;i<20;++i)
		for(int u=1;u<=nw;++u)
			anc[i+1][u]=anc[i][anc[i][u]];
//	for(int i=1;i<=nw;++i)
	//	cerr<<"i : "<<i<<" "<<fa[i]<<"\n";
}

ull Query(int l,int r){
	//cerr<<"r : "<<r<<" l : "<<l<<"\n";
	int p=r,le=r-l+1;
	for(int i=20;~i;--i)
		if(len[anc[i][p]]>=le)
			p=anc[i][p];
	//assert(len[fa[p]]<le&&len[p]>=le);
	//cerr<<"find : "<<p<<"\n";
	return Ans[p];
}

}


void Work(){
	SAM::clear();
	cin>>n>>(s+1);
	for(int i=1;i<=n;++i)
		cin>>W[i];
	SAM::init(n);
	for(int i=1;i<=n;++i)
		SAM::push_back(i,s[i]-'a');
	SAM::build();
	int Q;cin>>Q;
	while(Q--){
		int l,r;cin>>l>>r;
		cout<<SAM::Query(l,r)<<"\n";
	}
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
}
signed main(){File();Main();return 0;}