#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cerr;
using std::cout;
using std::max;
using std::min;
using std::swap;

const int mod=998244353,gr=3,i2=mod-mod/2;
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

const int bit=22;
const int SIZE=1<<bit|7;

int r[SIZE],*w[bit+1];

void init_omega(){
	for(int i=1;i<=bit;++i)
		w[i]=new int[1<<(i-1)];
//	cerr<<"space ok\n";
	int wn=po(gr,(mod-1)>>bit);
	w[bit][0]=1;
	for(int i=1;i<(1<<(bit-1));++i)
		w[bit][i]=mul(w[bit][i-1],wn);
	for(int i=bit-1;i;--i)
		for(int j=0;j<(1<<(i-1));++j)
			w[i][j]=w[i+1][j<<1];
//	cerr<<"init ok\n";
}

int len,inv_len;
void init_len(int deg){
	int l=1;while(l<=deg)l<<=1;
	len=l,inv_len=Inv(l);
	for(int i=1;i<l;++i)
		r[i]=r[i>>1]>>1|((i&1)?l>>1:0);
}void DFT(int *A){
	for(int i=1;i<len;++i)
		if(i<r[i])swap(A[i],A[r[i]]);
	for(int i=1,d=1;i<len;i<<=1,++d)
		for(int j=0;j<len;j+=i<<1)
			for(int k=0;k<i;++k){
				int &t1=A[j+k],&t2=A[i+j+k];
				int t=mul(t2,w[d][k]);
				t2=dec(t1,t);Inc(t1,t);
			}
}void IDFT(int *A){
	DFT(A);std::reverse(A+1,A+len);
	for(int i=0;i<len;++i)
		Mul(A[i],inv_len);
}

int n,k;
int A[SIZE],B[SIZE],F[SIZE];

void solve(int l,int r){
	if(l==r){
		F[l]+=(l==1);
		return;
	}
	int m=(l+r)>>1;
	solve(l,m);
	if(l==1){
		memcpy(A,F,sizeof(int)*(m+1));
		init_len(m+m+1);DFT(A);
		for(int i=0;i<len;++i)
			Mul(A[i],A[i]);
		IDFT(A);
		for(int i=1;i<=m;++i)
			Inc(A[i+i],mul(F[i],F[i]));
		for(int i=m+1;i<=r;++i)
			Inc(F[i],mul(A[i],i2));
		memset(A,0,sizeof(int)*len);
		for(int i=1;i<=m;++i){
			int jl=max(m+1-i,i+1);
			int jr=min({i+k,m,r-i});
			for(int j=jl;j<=jr;++j)
				Inc(F[i+j],mul(F[i],F[j]));
		}
	}else {
		memcpy(A,F+l,sizeof(int)*(m-l+1));
		memcpy(B,F,sizeof(int)*(r-l+1));
		init_len(m+r-l-l+1);DFT(A);DFT(B);
		for(int i=0;i<len;++i)
			Mul(A[i],B[i]);
		IDFT(A);
		for(int i=m+1;i<=r;++i)
			Inc(F[i],A[i-l]);
		memset(A,0,sizeof(int)*len);
		memset(B,0,sizeof(int)*len);
		for(int i=max(0,l-k);i<=r-l;++i){
			int jl=max(l,m-i+1);
			int jr=min({r-i,m,i+k});
			for(int j=jl;j<=jr;++j)
				Inc(F[i+j],mul(F[i],F[j]));
		}
	}
	solve(m+1,r);
}

void Main(){
	init_omega();
	cin>>n>>k;
	//cerr<<"n : "<<n<<" "<<k<<"\n";
	solve(1,n);
	cout<<F[n]<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}