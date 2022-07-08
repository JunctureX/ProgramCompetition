#include <bits/stdc++.h>

using ll=long long;
using ull=unsigned long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::swap;
using std::max;

static const int M1=1e9+7,M2=1e9+9;
inline void ex_gcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return;}ex_gcd(b,a%b,y,x);y-=a/b*x;
}inline int Inv(int a,int mod){
	int x,y;ex_gcd(mod,a,y,x);
	return x+(x>>31&mod);
}

static int get_gr(const int M){
	int phi=M-1;std::vector<int> p;
	for(int i=2;i*i<=phi;++i)
	if(phi%i==0){
		p.push_back(i);
		while(phi%i==0)phi/=i;
	}
	if(phi>1)p.push_back(phi);
	phi=M-1;
	auto power=[&](int a,int b)->int{int r=1;
		for(;b;b>>=1,a=(ll)a*a%M)
			(b&1)&&(r=(ll)r*a%M);
		return r;
	};
	for(int gr=2;;++gr){
		bool flag=true;
		for(int t:p)if(power(gr,phi/t)==1)
		{flag=false;break;}if(flag)return gr;
	}
}
static const int g1=get_gr(M1),g2=get_gr(M2);
class Key{
public:
	int x,y;
	Key(){}Key(int _x,int _y):x((_x%M1+M1)%M1),y((_y%M2+M2)%M2){}
	friend Key operator+(const Key &a,const Key &b){return Key((a.x+b.x)%M1,(a.y+b.y)%M2);}
	friend Key operator-(const Key &a,const Key &b){return Key((a.x-b.x+M1)%M1,(a.y-b.y+M2)%M2);}
	friend Key operator*(const Key &a,const Key &b){return Key((ll)a.x*b.x%M1,(ll)a.y*b.y%M2);}
	friend Key operator*(const Key &a,const int &b){return a*Key(b,b);}
	friend Key operator*(const int &b,const Key &a){return a*Key(b,b);}
	friend Key &operator+=(Key &a,const Key &b){return a=a+b;}
	friend Key &operator-=(Key &a,const Key &b){return a=a-b;}
	friend Key &operator*=(Key &a,const Key &b){return a=a*b;}
	friend bool operator<(const Key &a,const Key &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
	friend bool operator<=(const Key &a,const Key &b){return a.x<b.x||(a.x<=b.x&&a.y<=b.y);}
	friend bool operator==(const Key &a,const Key &b){return a.x==b.x&&a.y==b.y;}
	friend bool operator!=(const Key &a,const Key &b){return a.x!=b.x||a.y!=b.y;}
};
//Key Random(){return Key(gen(M1,g1),gen(M2,g2));} 
const Key key0(0,0),key1(1,1); 
const Key bse=Key(g1,g2);
const Key ibs=Key(Inv(bse.x,M1),Inv(bse.y,M2));

struct Map{
static const int magic=14898597;
ull key[magic];
int st[magic],tp;
int val[magic];
Map(){memset(key,-1,sizeof key);}
int locate(ull k)const{
	int h=k%magic;
	while(key[h]!=~0ull&&key[h]!=k)h=(h+1)%magic;
	return h;
}
int &operator[](ull k){
	int h=locate(k);
	if(key[h]==~0ull){
		key[h]=k;
		st[++tp]=h;
	}return val[h];
}
bool find(ull k)const{
	return key[locate(k)]==k;
}
void clear(){
	while(tp){
		key[st[tp]]=~0ull;
		val[st[tp]]=0;
		--tp;
	}
}
}mp,mp2;

ull hsh(const Key &a){
	return (ull)a.x*M2+a.y;
}

const int N=2e5+7;

Key pw[N],sm[N],ip[N];

int n;
char s[N];
Key a[N];

Key gh(int l,int r){
	return (sm[r]-sm[l-1])*ip[l];
}

Key gh(int l,int r,int p,int a){
	return gh(l,p-1)+a*pw[p-l]+gh(p+1,r)*pw[p-l+1];
}

void Sol_Small(int k){
//	cerr<<"k : "<<k<<"\n";
	mp.clear();ll ans=0;
	mp2.clear();
	for(int i=0;(i+1)*k<=n;++i){
		for(int j=i*k+1;j<=(i+1)*k;++j){
				++mp[hsh(gh(i*k+1,(i+1)*k,j,50))];
			}
		ans-=(ll)mp2[hsh(gh(i*k+1,(i+1)*k))]*(k-1);
		++mp2[hsh(gh(i*k+1,(i+1)*k))];
		for(int j=i*k+1;j<=(i+1)*k;++j){
			ans+=mp[hsh(gh(i*k+1,(i+1)*k,j,50))];
			ans--;
		}
	}
	cout<<ans<<" ";
}

struct SA{

int sa[N],rk[N],ht[N];

void radix_sort(int *x,int *y,int m,int n){
	static int bin[N];
	for(int i=0;i<=m;++i)
		bin[i]=0;
	for(int i=1;i<=n;++i)
		++bin[x[i]];
	for(int i=1;i<=m;++i)
		bin[i]+=bin[i-1];
	for(int i=n;i;--i)
		sa[bin[x[y[i]]]--]=y[i];
}void build_SA(){
	int *x=ht,*y=rk,m=128;
	for(int i=1;i<=n;++i)
		x[i]=s[i],y[i]=i;
	radix_sort(x,y,m,n);
	for(int i=1,ct=0;ct<n;i<<=1){
		ct=0;
		for(int j=n-i+1;j<=n;++j)
			y[++ct]=j;
		for(int j=1;j<=n;++j)
			if(sa[j]>i)y[++ct]=sa[j]-i;
		radix_sort(x,y,m,n);
		swap(x,y);x[sa[1]]=ct=1;
		for(int j=2;j<=n;++j)
			x[sa[j]]=(y[sa[j]]==y[sa[j-1]]&&y[sa[j]+i]==y[sa[j-1]+i])?
				ct:++ct;
		m=ct;
	}for(int i=1;i<=n;++i)rk[sa[i]]=i;
	for(int i=1,k=0,j;i<=n;ht[rk[i++]]=k)
		for(k?--k:0,j=sa[rk[i]-1];s[i+k]==s[j+k];++k);
}

int mn[22][N],Log[N];
inline void init_st(){
	Log[0]=-1;
	for(int i=1;i<=n;++i)
		Log[i]=Log[i>>1]+1,mn[0][i]=ht[i];
	for(int i=1;(1<<i)<=n;++i)
		for(int j=1;j+(1<<i)-1<=n;++j)
			mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
}
inline int lcp(int a,int b){
	a=rk[a],b=rk[b];if(a>b)swap(a,b);
	int t=Log[b-a];if(a==b)return 1e9;
	return std::min(mn[t][a+1],mn[t][b-(1<<t)+1]);
}

void build(){
	build_SA();
	init_st();
}

}ori,rev;

bool check(int a,int b,int l){
	int l1=ori.lcp(a,b);
	a+=l-1,b+=l-1;
	a=n-a+1,b=n-b+1;
	int l2=rev.lcp(a,b);
	return l1+l2>=l-1;
}

void Sol_Big(int k){
//	cerr<<"k : "<<k<<"\n";
	int ans=0;
	for(int i=0;(i+1)*k<=n;++i){
		for(int j=i+1;(j+1)*k<=n;++j){
			ans+=check(i*k+1,j*k+1,k);
		}
	}
	cout<<ans<<" ";
}

void Main(){
	cin>>n>>(s+1);
//	cerr<<"n : "<<n<<"\n";
	for(int i=1;i<=n;++i)
		a[i]=Key(s[i]-'a',s[i]-'a');
	pw[0]=ip[0]=key1;
	assert(bse*ibs==key1);
//	cerr<<"bse : "<<bse.x<<" "<<bse.y<<"\n";
	for(int i=1;i<=n;++i){
		pw[i]=pw[i-1]*bse;
		ip[i]=ip[i-1]*ibs;
	}
	for(int i=1;i<=n;++i){
		sm[i]=sm[i-1]+a[i]*pw[i];
	}//cerr<<"???\n";
	int B=sqrt(n)/5;
	for(int k=1;k<=min(B,n);++k)
		Sol_Small(k);
//	cerr<<"Small end\n";
	ori.build();
	std::reverse(s+1,s+n+1);
	rev.build();
	for(int k=B+1;k<=n;++k)
		Sol_Big(k);
	//cerr<<"Big end\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
}signed main(){File();Main();return 0;}