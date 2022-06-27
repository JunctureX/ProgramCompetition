#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::swap;

void Main(){
	int a[3];
	cin>>a[0]>>a[1]>>a[2];
	std::sort(a,a+3);
	int A=a[0],B=a[1];
	ll ans=0;
	for(int x=3;x<=A;++x){
		ans+=(x-1)/2*6;
	}
	for(int x=A+1;x<=B;++x){
		int l=x-A,r=min(A,(x-1)/2);
		if(r>=l)ans+=(r-l+1)*2;
	}cout<<ans*8<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif	
}signed main(){File();Main();return 0;}