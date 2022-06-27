#include <bits/stdc++.h>

using std::cin;
using std::cerr;
using std::cout;
using std::min;

int n,k;
const int N=1e4+7;

int a[N];
bool b[N];

void Main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	int ans=1e9;
	for(int l=1,r,kct;l<=n;++l){
		memset(b,0,sizeof b);
		for(r=l,kct=0;r<=n;++r){
			if(!b[a[r]]){
				++kct;
				b[a[r]]=true;
			}
			if(kct==k)break;
		}
		if(kct<k)continue;
		kct=0;
		memset(b,0,sizeof b);
		for(int i=1;i<l;++i)
			kct+=!b[a[i]],b[a[i]]=true;
		for(int i=r+1;i<=n;++i)
			kct+=!b[a[i]],b[a[i]]=true;
		if(kct<k)continue;
//		cerr<<"l : "<<l<<" r : "<<r<<"\n";
		ans=min(ans,r-l+1);
	}
	if(ans>n)
		cout<<0;
	else 
		cout<<ans;
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif	
}signed main(){File();Main();return 0;}