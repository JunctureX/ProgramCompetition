#include<bits/stdc++.h>

using ll=long long;
using pii=std::pair<int,int>;
using std::cin;
using std::cerr;
using std::cout;

const int mod=998244353,i2=(mod+1)/2;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Inc(int &a,int b){a+=b-mod,a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b,a+=a>>31&mod;}
inline void Mul(int &a,int b){a=mul(a,b);} 
inline int po(int a,int b){int r=1;for(;b;b>>=1,Mul(a,a))if(b&1)Mul(r,a);return r;}
inline void ex_gcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return;}ex_gcd(b,a%b,y,x);y-=a/b*x;
}inline int Inv(int a){static int x,y;ex_gcd(mod,a,y,x);return x+(x>>31&mod);}

const int bit=18,SIZE=1<<bit|7;

int r[SIZE],*w[bit+1],Len[SIZE];

void init_omega(){
	for(int i=1;i<=bit;++i)
		w[i]=new int[1<<(i-1)];
	int wn=po(3,(mod-1)>>bit);w[bit][0]=1;
	for(int i=1;i<(1<<(bit-1));++i)
		w[bit][i]=mul(w[bit][i-1],wn);
	for(int i=bit-1;i;--i)
		for(int j=0;j<(1<<(i-1));++j)
			w[i][j]=w[i+1][j<<1];
	for(int i=Len[0]=1;i<SIZE;++i)
		Len[i]=Len[i-1]<<(Len[i-1]<i);
}

int inv[SIZE],fac[SIZE],_fac[SIZE];
void init_fac(){
	fac[0]=fac[1]=1;
	inv[0]=inv[1]=1;
	_fac[0]=_fac[1]=1;
	for(int i=2;i<SIZE;++i){
		fac[i]=mul(fac[i-1],i);
		inv[i]=mul(inv[mod%i],mod-mod/i);
		_fac[i]=mul(_fac[i-1],inv[i]);
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
		if(i<r[i])std::swap(A[i],A[r[i]]);
	for(int i=1,d=1;i<len;i<<=1,++d)
		for(int j=0;j<len;j+=i<<1)
		if(i<8){
			for(int k=0;k<i;++k){
				int &t1=A[j+k],&t2=A[i+j+k];
				int t=mul(t2,w[d][k]);
				t2=dec(t1,t),Inc(t1,t);
			}
		}else {
#define work(p)	\
{				\
	int &t1=A[j+k+p],&t2=A[i+j+k+p];	\
	int t=mul(t2,w[d][k+p]);			\
	t2=dec(t1,t),Inc(t1,t);				\
}
			for(int k=0;k<i;k+=8){
				work(0);work(1);work(2);work(3);
				work(4);work(5);work(6);work(7);
			}
		}
}void IDFT(int *A){
	DFT(A);std::reverse(A+1,A+len);
	for(int i=0;i<len;++i)Mul(A[i],inv_len);
}

typedef std::vector<int> Poly;

inline void DFT(Poly &A){DFT(&A[0]);}
inline void IDFT(Poly &A){IDFT(&A[0]);}

Poly operator+(Poly a,const Poly &b){
	if(a.size()<b.size())a.resize(b.size());
	for(size_t i=0;i<b.size();++i)
		Inc(a[i],b[i]);return a;
}Poly operator-(Poly a,const Poly &b){
	if(a.size()<b.size())a.resize(b.size());
	for(size_t i=0;i<b.size();++i)
		Dec(a[i],b[i]);return a;
}Poly operator*(Poly a,Poly b){
	if(!a.size()||!b.size())
		return Poly();
	int deg=a.size()+b.size()-1;
	init_len(deg);
	a.resize(len),DFT(a);
	b.resize(len),DFT(b);
	for(int i=0;i<len;++i)
		Mul(a[i],b[i]);
	IDFT(a);return Poly(a.begin(),a.begin()+deg);
}Poly Deriv(Poly a){
	if(!a.size())return a;
	for(size_t i=1;i<a.size();++i)
		a[i-1]=mul(a[i],i);
	a.pop_back();return a; 
}Poly Integ(Poly a){
	if(!a.size())return a;
	a.push_back(0);
	for(size_t i=a.size()-1;i;--i)
		a[i]=mul(a[i-1],inv[i]);
	a[0]=0;return a;
}Poly Inv(const Poly &a,int lim){
	int n=a.size();Poly c,b(1,Inv(a[0]));
	for(int l=4;(l>>2)<lim;l<<=1){
		init_len(l);c.resize(l>>1);
		for(int i=0;i<(l>>1);++i)
			c[i]=i<n?a[i]:0;
		c.resize(l),DFT(c);
		b.resize(l),DFT(b);
		for(int i=0;i<l;++i)
			Mul(b[i],dec(2,mul(b[i],c[i])));
		IDFT(b);b.resize(l>>1);
	}return Poly(b.begin(),b.end()+lim);
}Poly Ln(Poly a,int lim){
	a=Deriv(a)*Inv(a,lim);
	a.resize(lim+1);return Integ(a);
}Poly Exp(const Poly &a,int lim){
	int n=a.size();Poly c,b(1,1);
	for(int i=2;(i>>1)<lim;i<<=1){
		c=Ln(b,i);Dec(c[0],1);
		for(int j=0;j<i;++j)
			c[j]=dec(j<n?a[j]:0,c[j]);
		b=b*c;b.resize(i);
	}return Poly(b.begin(),b.begin()+lim);
}
inline Poly operator/(Poly a,Poly b){
	if(a.size()<b.size())return Poly(1,0);
	int deg=a.size()-b.size()+1;
	std::reverse(a.begin(),a.end());
	std::reverse(b.begin(),b.end());
	b=Inv(b,deg);a=a*b;a.resize(deg);
	std::reverse(a.begin(),a.end());
	return a;
}

inline Poly operator%(const Poly &a,const Poly &b){
	if(a.size()<b.size())return a;
	Poly c=a-(a/b)*b;
	c.resize(b.size()-1);
	return c;
}

const int PP=2e5+5;

Poly f[PP<<2|1];

inline void build(int k,int l,int r,const Poly &v){
	if(l==r){f[k].resize(2);f[k][0]=dec(0,v[l]),f[k][1]=1;return ;}
	int mid=l+r>>1;build(k<<1,l,mid,v);build(k<<1|1,mid+1,r,v);
	f[k]=f[k<<1]*f[k<<1|1];
}

inline void solve(int k,int l,int r,const Poly &a,Poly &y){
	if(l==r){y[l]=a[0];return ;}int mid=l+r>>1;
	solve(k<<1,l,mid,a%f[k<<1],y);
	solve(k<<1|1,mid+1,r,a%f[k<<1|1],y);
}

inline void multi_point_evaluation(const Poly &A,const Poly &x,Poly &y){
	build(1,0,x.size()-1,x);y.resize(x.size());
	solve(1,0,x.size()-1,A%f[1],y);
}

const int N=1e5+7;

std::vector<int> x,y;
Poly solve(int l,int r){
	if(l==r)return (Poly){x[l],1};
	int md=(l+r)>>1;
	return solve(l,md)*solve(md+1,r);
}

void Main(){
	init_omega();
	int n;cin>>n;
	x.resize(n);
	for(auto &i:x)cin>>i;
	Poly t=solve(0,n-1);
	multi_point_evaluation(t,x,y);
	int ans=1;for(auto i:y)Mul(ans,i);
	cout<<ans<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}