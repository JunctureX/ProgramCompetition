#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;

const int N=5e2+7;
const int M=1.25e5+7;

bool f[M],g[M],F[M];

void Main(){
	int n,k;
	cin>>n>>k;
	f[0]=1;
	for(int i=1;i<=n;++i){
		F[0]=f[0];
		for(int j=1;j<=k;++j)
			F[j]=F[j-1]^f[j];
		for(int t=k;t>=0;--t){
			g[t]=F[t];
			if(t-n+i-1>=0)
				g[t]^=F[t-n+i-1];
		}
		for(int j=0;j<=k;++j)
			f[j]=g[j];
	//	cerr<<"i : "<<i<<" : ";
	//	for(int j=0;j<=k;++j)
	//		cerr<<f[j]<<" ";
	//	cerr<<"\n";
	}
	cout<<f[k]<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}