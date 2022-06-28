#include <bits/stdc++.h>

using ll=long long;
using pii=std::pair<int,int>;
using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::max;

const int N=3e5+7;

ll ans;int n,k;

int a[N],bin[N];
bool bi[N],bj[N];

void solve(int l,int r){
	if(l==r){
		ans+=a[l]-(r-l+1)<=k;
		return;
	}int ml=(l+r)>>1,mr=ml+1;
	solve(l,ml);solve(mr,r);
	//cerr<<"l : "<<l<<" r : "<<r<<" md : "<<ml<<"\n";
	for(int i=mr;i<=r;++i)
		bin[a[i]]=0,bi[a[i]]=false;
	for(int i=l;i<=ml;++i)
		bin[a[i]]=i,bj[a[i]]=false;
	for(int R=mr,l1=l-1,l2=mr,Mx=0;R<=r;++R){
		if(bi[a[R]])break;
		Mx=max(Mx,a[R]);bi[a[R]]=true;
		while(l2>l&&a[l2-1]<Mx&&!bj[a[l2-1]])bj[a[--l2]]=true;
		l1=max(l1,bin[a[R]]);
		int Lr=min(k-Mx+R+1,ml);
		int Ll=max(l1,l2-1);
		//cerr<<"R : "<<R<<" L : "<<Ll<<" "<<Lr<<"\n";
		ans+=max(Lr-Ll,0);
	}
	for(int i=l;i<=ml;++i)
		bin[a[i]]=n+1,bi[a[i]]=false;
	for(int i=r;i>=mr;--i)
		bin[a[i]]=i,bj[a[i]]=false;
	for(int L=ml,r1=r+1,r2=ml,Mx=0;L>=l;--L){
		if(bi[a[L]])break;
		Mx=max(Mx,a[L]);bi[a[L]]=true;
		while(r2<r&&a[r2+1]<Mx&&!bj[a[r2+1]])bj[a[++r2]]=true;
		r1=min(r1,bin[a[L]]);
		int Rl=max(mr,Mx+L-1-k);
		int Rr=min(r1,r2+1);
	//	cerr<<"L : "<<L<<" R : "<<Rl<<" "<<Rr<<"\n";
		ans+=max(Rr-Rl,0);
	}
	for(int i=l;i<=r;++i) bi[a[i]]=bin[a[i]]=0;
}

void Work(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	ans=0;solve(1,n);
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
}
signed main(){File();Main();return 0;}