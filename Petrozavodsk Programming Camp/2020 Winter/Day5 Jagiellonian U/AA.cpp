#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;

const int N=1e6+7;

int sm[N],ro[N];
ll la[N];
bool skip[N];

ll pi(ll n){
	if(n<=1)return 0;
	if(n==2)return 1;
	int v=sqrtl(n);
	int s=(v+1)/2;
	memset(skip,0,sizeof(bool)*(v+1));
	for(int i=0;i<s;++i){
		sm[i]=i;
		ro[i]=i<<1|1;
		la[i]=(n/(i<<1|1)-1)/2;
	}
#define half(x) (((x)-1)>>1)
	int pc=0;
	for(int p=3;p<=v;p+=2)
		if(!skip[p]){
			int q=p*p;
			if((ll)q*q>n)break;
			skip[p]=true;
			for(int i=q;i<=v;i+=p+p)
				skip[i]=true;
			int ns=0;
			for(int k=0;k<s;++k){
				int i=ro[k];
				if(skip[i])
					continue;
				ll d=(ll)i*p;
				la[ns]=la[k]-(d<=v?la[sm[d>>1]-pc]:sm[half(n/d)])+pc;
				ro[ns++]=i;
			}
			s=ns;
			for(int i=half(v),j=((v/p)-1)|1;j>=p;j-=2){
				int c=sm[j>>1]-pc;
				for(int e=(j*p)>>1;i>=e;--i)
					sm[i]-=c;
			}
			++pc;
		}
	la[0]+=(ll)(s+2*(pc-1))*(s-1)/2;
	for(int k=1;k<s;++k)
		la[0]-=la[k];
	for(int l=1;l<s;++l){
		int q=ro[l];
		ll m=n/q;
		int e=sm[half(m/q)]-pc;
		if(e<l+1)break;
		ll t=0;
		for(int k=l+1;k<=e;++k)
			t+=sm[half(m/ro[k])];
		la[0]+=t-(ll)(e-l)*(pc+l-1);
	}
	return la[0]+1;
}

void Main(){
	int T;cin>>T;
	ll n;
	while(T--){
		cin>>n;
		cout<<n-(n-1-pi(n)+pi(n/2))/2<<"\n";
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}