#include<bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;

const int mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline int po(int a,int b){
	int r=1;for(;b;b>>=1,Mul(a,a))
		if(b&1)Mul(r,a);
	return r;
}

const int N=80;

int fac[N],ifc[N],inv[N];
int n,ans;
int a[N],ct;

void dfs(int d,int rest){
	if(rest==0){
		int res=fac[n];
		for(int i=1;i<=ct;++i){
			for(int j=a[i],k=i;j>=1;--j){
				while(k<ct&&a[k+1]>=j)++k;
				Mul(res,inv[a[i]-j+1+k-i]);
			}
		}
		Inc(ans,mul(res,res));
		return;
	}
	for(int i=min(d,rest);i>=2;--i){
		a[++ct]=i;
		dfs(i,rest-i);
		--ct;
	}
}

void Main(){
	cin>>n;
	fac[0]=ifc[0]=inv[0]=1;
	fac[1]=ifc[1]=inv[1]=1;
	for(int i=2;i<=n;++i){
		fac[i]=mul(fac[i-1],i);
		inv[i]=mul(mod-mod/i,inv[mod%i]);
		ifc[i]=mul(ifc[i-1],inv[i]);
	}
	dfs(n,n);
	cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}