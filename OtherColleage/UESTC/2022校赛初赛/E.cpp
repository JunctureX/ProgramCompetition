#include<bits/stdc++.h>

namespace IO{

inline char gc(){
	static const int Rlen=1<<22|1;static char buf[Rlen],*p1,*p2;
	return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,Rlen,stdin),p1==p2)?EOF:*p1++;
}template<typename T>T get_integer(){
	char c;bool f=false;while(!isdigit(c=gc()))f=c=='-';T x=c^48;
	while(isdigit(c=gc()))x=((x+(x<<2))<<1)+(c^48);
	return f?-x:x;
}inline int gi(){return get_integer<int>();}

inline int ga(){
	char c;
	while(!isalpha(c=gc()));
	return c;
}

}using namespace IO;

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


void Main(){
	int T=gi();
	while(T--){
		int n=gi();
		int s=0;
		for(int i=1;i<=8;++i)
			Inc(s,gi());
		cout<<mul(s,mul(i2,n-1))<<"\n";
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}