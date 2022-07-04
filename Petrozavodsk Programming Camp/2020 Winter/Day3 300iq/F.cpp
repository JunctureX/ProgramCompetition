#include<bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;

const int N=3e5+7;

int a,b,n;
std::priority_queue<int> Q;

void Main(){
	cin>>n>>a>>b;ll nw=1,ans=0;
	for(int i=1;i<=n;++i){
		int h;cin>>h;
	//	cerr<<"h : "<<h<<"\n";
		int A=(h-1)%b/a+1;
		int B=(h-1)/b+1;
		nw+=B-A-1;Q.push(A+1);
	//	cerr<<A<<" "<<B<<"\n";
		++ans;if(nw<0)nw+=Q.top(),Q.pop(),--ans;
	}cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}