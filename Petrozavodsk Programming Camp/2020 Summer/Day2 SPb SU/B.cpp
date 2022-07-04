#include <bits/stdc++.h>

#define int ll
using ll=long long;
using db=double;
using pii=std::pair<int,int>;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;
using std::swap;

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
}inline void ex_gcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return;}ex_gcd(b,a%b,y,x);y-=a/b*x;
}inline int Inv(int a){
	int x,y;ex_gcd(mod,a,y,x);
	return x+(x>>31&mod);
}

const int bit=15,SIZE=1<<bit|7;

int r[SIZE],*w[bit+1];

void init_omega(){
	for(int i=1;i<=bit;++i)
		w[i]=new int[1<<(i-1)];
	int wn=po(3,(mod-1)>>bit);w[bit][0]=1;
	for(int i=1;i<(1<<(bit-1));++i)
		w[bit][i]=mul(w[bit][i-1],wn);
	for(int i=bit-1;i;--i){
		for(int j=0;j<(1<<(i-1));++j){
			w[i][j]=w[i+1][j<<1];
		}
	}
}

int len,inv_len;
void init_len(int deg){
	int l=1;while(l<deg)l<<=1;
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

typedef std::vector<int> Poly;

inline void DFT(Poly &A){DFT(&A[0]);}
inline void IDFT(Poly &A){IDFT(&A[0]);}

Poly operator*(Poly a,Poly b){
	if(!a.size()||!b.size())
		return Poly();
	int deg=a.size()+b.size()-1;
	init_len(deg);
	a.resize(len);DFT(a);
	b.resize(len);DFT(b);
	for(int i=0;i<len;++i)
		Mul(a[i],b[i]);
	IDFT(a);a.resize(deg);
	return a;
}

const int N=1e5+7;

int rem,n;
char s[N];
int F[N];

void mul_poly(Poly &a,Poly b){
	a=a*b;
	for(int i=a.size()-1;i>=n;--i)
		Inc(a[i-n],a[i]);
	a.resize(n);
}

void Main(){
	init_omega();
	cin>>n>>rem;
	cin>>s;int m=strlen(s);
	ll div=0,Tr=0;
	for(int i=0;i<m;++i){
		int c=s[i]-'0';
		Tr=Tr*10+c;
		div=div*10+Tr/n;
		div=div%(mod-1)+(!!div)*(mod-1);
		Tr%=n;
	}F[0]=1;
	for(int i=0;i<n;++i){
		for(int j=n;j>=0;--j)
			Inc(F[j+i],F[j]);
		for(int j=n+i;j>=n;--j)
			Inc(F[j-n],F[j]),F[j]=0;
	}
	Poly f(F,F+n),g={1};g.resize(n);
	while(div){
		if(div&1)mul_poly(g,f);
		div>>=1,mul_poly(f,f);
	}
	for(int i=0;i<n;++i)
		F[i]=g[i];
	for(int i=n;i<n+n;++i)
		F[i]=0;
	for(int i=0;i<Tr;++i){
		for(int j=n;j>=0;--j)
			Inc(F[j+i],F[j]);
		for(int j=n+i;j>=n;--j)
			Inc(F[j-n],F[j]),F[j]=0;
	}cout<<F[rem]<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	srand(20010417);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}