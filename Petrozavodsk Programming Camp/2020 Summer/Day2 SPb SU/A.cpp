#include <bits/stdc++.h>

using ll=long long;
using db=double;
using pii=std::pair<int,int>;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

const int N=850+7;
const db coef=10;

int n;
int C[N+N][N];
int ans[N],dp[N][N];

void work(int C[][N],int k){
	for(int i=0;i<=k;++i)
		memset(dp[i],0x3f,sizeof(int)*(n+1));
	dp[0][0]=0;
	for(int i=0;i<=k;++i){
		for(int j=0;j<n;++j)
			if(dp[i][j]<1e9){
				for(int t=j+1;t<=n;++t){
					dp[i+1][t]=min(dp[i+1][t],dp[i][j]+C[j+1][t-j]);
				}
			}
	}
	for(int i=0;i<=k;++i)
		ans[i]=min(ans[i],dp[i][n]);
}

void Main(){
	cin>>n;
//	n=850;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cin>>C[i][j];
		//	C[i][j]=rand();
			C[i+n][j]=C[i][j];
		}
	}
	std::vector<int> vec(n);
	for(int i=0;i<n;++i)
		vec[i]=i;
	memset(ans,0x3f,sizeof ans);
	int sum=0;
	for(int k=n;k>=1;--k){
		//cerr<<"k : "<<k<<"\n";
		int tim=coef*n*(1./k);
		std::random_shuffle(vec.begin(),vec.end());
	//	cerr<<"tim : "<<tim<<"\n";
		for(int t=0;t<min(tim-sum,n);++t){
	//		cerr<<"t : "<<t<<"\n";
			int st=vec[t];
			work(C+st,k);
		}
		sum=tim;
	}
	for(int i=1;i<=n;++i){
		cout<<ans[i]<<" ";
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	srand(20010417);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}