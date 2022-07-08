#include<bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

const int N=1e6+7;

void Work(){
	int n,d;cin>>n>>d;
	std::vector<ll> vec(n);
	for(auto &t:vec)
		cin>>t;
	ll res=0;
	std::priority_queue<ll> Q;
	std::sort(vec.begin(),vec.end());
	for(int i=0;i<n;++i){
		vec[i]-=(ll)i*d;
		if(vec[i]<0){
			res+=-vec[i];
			vec[i]=0;
		}
		Q.push(vec[i]);
		if(Q.top()>vec[i]){
			res+=Q.top()-vec[i];
			Q.pop();
			Q.push(vec[i]);
		}
	}cout<<res<<"\n";
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
}signed main(){File();Main();return 0;}