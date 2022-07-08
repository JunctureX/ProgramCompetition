#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cerr;
using std::cout;
using std::max;
using std::min;
using std::swap;

const int N=2e5+7;

char a[N],b[N];
int al,bl;

namespace SAM{

const int N=::N<<1|7;

int sn[N][26],fa[N],len[N],mn[N],nw,rt;

void init(int n){
	for(int i=1;i<=n;++i)
		len[i]=i,mn[i]=1e9;
	nw=rt=n+1;mn[rt]=1e9;
}void push_back(int i,int c,bool fl){
	int p=(i-1)?(i-1):rt;
	if(fl)mn[i]=i;
	for(;p&&!sn[p][c];p=fa[p])
		sn[p][c]=i;
	if(!p)fa[i]=rt;
	else if(len[sn[p][c]]==len[p]+1)
		fa[i]=sn[p][c];
	else {
		int nq=++nw,q=sn[p][c];mn[nw]=1e9;
		memcpy(sn[nq],sn[q],sizeof sn[q]);
		len[nq]=len[p]+1;fa[nq]=fa[q],fa[q]=fa[i]=nq;
		for(;p&&sn[p][c]==q;p=fa[p])sn[p][c]=nq;
	}
//	cerr<<"push_back : "<<"u : "<<i<<" "<<fa[i]<<"\n";
}

int bin[N],nd[N];
ll calc(){
	ll ans=0;
	for(int i=1;i<=nw;++i)bin[i]=0;
	for(int i=1;i<=nw;++i)++bin[len[i]];
	for(int i=1;i<=nw;++i)bin[i]+=bin[i-1];
	for(int i=1;i<=nw;++i)
		nd[bin[len[i]]--]=i;
	for(int i=nw;i;--i){
		int u=nd[i];
		mn[fa[u]]=min(mn[u],mn[fa[u]]);
		if(mn[u]-len[u]>=al)continue;
	//	cerr<<"u : "<<u<<" len : "<<len[u]<<" lenp : "<<len[fa[u]]<<"\n";
		int l=mn[u]-len[u]+1;
		int r=mn[u]-len[fa[u]];
		ans+=min(r,al)-l+1;
	}return ans;
}

void clear(){
	for(int i=1;i<=nw;++i)
		memset(sn[i],0,sizeof sn[i]);
	memset(fa,0,sizeof(int)*(nw+1));
	memset(len,0,sizeof(int)*(nw+1));
	memset(mn,0x3f,sizeof(int)*(nw+1));
	nw=rt=1;
}

}

void Work(){
	cin>>(a+1)>>(b+1);
	al=strlen(a+1),bl=strlen(b+1);
	SAM::clear();SAM::init(al+bl);
//	cerr<<"al : "<<al<<" bl : "<<bl<<"\n";
	for(int i=1;i<=al;++i)
		SAM::push_back(i,a[i]-'a',false);
	for(int i=1;i<=bl;++i)
		SAM::push_back(i+al,b[i]-'a',true);
	cout<<SAM::calc()<<"\n";
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