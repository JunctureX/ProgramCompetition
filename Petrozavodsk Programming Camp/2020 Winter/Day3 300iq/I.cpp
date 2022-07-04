#include<bits/stdc++.h>
#define int ll
using ll=long long;
using std::cin;
using std::cout;
using std::cerr;

const int mod=998244353;

const int N=65;
int pw[N],vs[N];

void Main(){
	int n,k;cin>>n>>k;int sum=0;
	for(int i=pw[0]=1;i<=62;++i)
		pw[i]=(pw[i-1]+pw[i-1])%mod;
	int ans=0;
	for(int i=1;i<=n;++i){
		int a;cin>>a;int p=sum,t=0;
		while(a){
			if(a&1){
				if(!vs[t])vs[t]=true,++sum;
			}a>>=1,++t;
		}
		ans=(ans+(ll)i*(pw[k-p]-pw[k-sum]+mod)%mod)%mod;
	}cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}