#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;

const int mod=998244353;
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline int po(int a,int b){
	int r=1;for(;b;b>>=1,Mul(a,a))
		if(b&1)Mul(r,a);
	return r;
}

void Main(){
	int n,m;cin>>n>>m;
	cout<<mul(po(n,m-1),po(m,n-1));
}

inline void File(){
//	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}