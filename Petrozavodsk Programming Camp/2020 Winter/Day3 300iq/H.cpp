#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;
using std::swap;

const int mod=998244353,gr=3;
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
}inline void ex_gcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return;}ex_gcd(b,a%b,y,x);y-=a/b*x;
}inline int Inv(int a){
	int x,y;ex_gcd(mod,a,y,x);
	return x+(x>>31&mod);
}

const int N=5e3+7;

int n,ans;
int C[N][N];
int a[N],F[N],G[N];

void Main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	std::sort(a+1,a+n+1);
	a[n+1]=a[n];
	C[0][0]=1;
	for(int i=1;i<=n;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=add(C[i-1][j],C[i-1][j-1]);
	}
	for(int i=0;i<=a[1];++i)
		F[i]=C[a[1]][i];
	for(int i=1;i<=n;++i){
		Inc(ans,F[1]);int dif=a[i+1]-a[i];
		for(int j=0;j<a[i];++j)
			G[j]=mul(2,mul(F[j+1],C[j+1][2]));
		G[a[i]]=0;
		for(int j=0;j<=a[i];++j)
			Inc(G[j],F[j]);
		memset(F,0,sizeof(int)*(a[i+1]+1));
		for(int j=0;j<=a[i];++j)
			for(int k=0;k<=dif;++k)
				Inc(F[j+k],mul(G[j],C[dif][k]));
	}for(int i=1;i<=n;++i)Dec(ans,a[i]);
	cout<<mul(ans,Inv(2));
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}