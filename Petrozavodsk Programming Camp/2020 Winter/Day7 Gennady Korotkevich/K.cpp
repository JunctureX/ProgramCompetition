#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cerr;
using std::cout;
using std::max;
using std::swap;

const int mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}

const int N=2e3+7;
const int M=1e5+7;

int X[M],Y[M],ans[M];
std::vector<int> vec[N];
int A[N][N],B[N][N];

void Main(){
	int Q;cin>>Q;
	for(int i=1;i<=Q;++i){
		int &x=X[i],&y=Y[i];
		cin>>x>>y;
		if(x<y)swap(x,y);
		vec[(y+x)/(y+1)].push_back(i);
	}
	for(int k=1;k<N;++k){
		if(vec[k].empty())continue;
		int mxx=0,mxy=0;
		for(auto t:vec[k]){
			mxx=max(mxx,X[t]),
			mxy=max(mxy,Y[t]);
		}
	//	cerr<<"k : "<<k<<"\n";
		A[0][0]=B[0][0]=1;
		for(int x=0;x<=mxx;++x)
			for(int y=0;y<=mxy;++y)if(y||x){
				if(y)A[x][y]=dec(x?add(A[x-1][y],B[x-1][y]):0,x>k?B[x-1-k][y]:0);
				else A[x][0]=x<=k;
				if(x)B[x][y]=dec(y?add(B[x][y-1],A[x][y-1]):0,y>k?A[x][y-1-k]:0);
				else B[0][y]=y<=k;
		//		cerr<<"x : "<<x<<" y : "<<y<<" "<<A[x][y]<<" "<<B[x][y]<<"\n";
			}
		for(auto t:vec[k]){
			ans[t]=add(A[X[t]][Y[t]],B[X[t]][Y[t]]);
		}
	}
	for(int i=1;i<=Q;++i)
		cout<<ans[i]<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}