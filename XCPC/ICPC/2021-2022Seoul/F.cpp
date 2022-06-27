#include <bits/stdc++.h>

using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::max;

const int N=1e6+7;
int a[N],b[N],n;
int f[N][2][2],g[N][2][2];

void Main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
		cin>>b[i];
	std::sort(a+1,a+n+1);
	std::sort(b+1,b+n+1);
	for(int i=1;i<=n+1;++i){
		f[i][0][0]=max(abs(a[i]-b[i]),f[i-1][0][0]);
		f[i][0][1]=min(f[i-1][0][0],f[i-1][0][1]);
		f[i][0][1]=max(f[i][0][1],abs(a[i]-b[i+1]));
		if(i>=2){
			f[i][1][0]=min(f[i-1][1][0],f[i-2][0][0]);
			f[i][1][0]=max(f[i][1][0],abs(a[i]-b[i-1]));
			f[i][1][1]=min(f[i-1][1][1],f[i-2][0][0]);
			f[i][1][1]=min(f[i][1][1],f[i-1][1][0]);
			f[i][1][1]=min(f[i][1][1],f[i-2][0][1]);
			f[i][1][1]=max(f[i][1][1],abs(a[i]-b[i]));
		}
	}
//	cerr<<f[n+1][1][1]<<"\n";
	for(int i=n;i>=0;--i){
		g[i][0][0]=max(abs(a[i]-b[i]),g[i+1][0][0]);
		g[i][0][1]=min(g[i+1][0][0],g[i+1][0][1]);
		g[i][0][1]=max(g[i][0][1],abs(a[i]-b[i-1]));
		if(i<=n-1){
			g[i][1][0]=min(g[i+1][1][0],g[i+2][0][0]);
			g[i][1][0]=max(g[i][1][0],abs(a[i]-b[i+1]));
			g[i][1][1]=min(g[i+1][1][1],g[i+2][0][0]);
			g[i][1][1]=min(g[i][1][1],g[i+1][1][0]);
			g[i][1][1]=min(g[i][1][1],g[i+2][0][1]);
			g[i][1][1]=max(g[i][1][1],abs(a[i]-b[i]));
		}
	}
//	cerr<<g[0][1][1]<<"\n";
	int res=f[n+1][1][1];
	for(int p=1;p<=n;++p){
		if(max(f[p-1][0][0],g[p+1][0][0])==res)
			{cout<<a[p]<<"\n";return;}
		if(max(f[p-1][0][1],g[p+1][0][0])==res)
			{cout<<a[p]<<"\n";return;}
		if(max(f[p-1][0][0],g[p+1][0][1])==res)
			{cout<<a[p]<<"\n";return;}
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}