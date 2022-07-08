#include <bits/stdc++.h>

#define int ll
using ll=long long;
using std::cin;
using std::cerr;
using std::cout;

struct pt{
	int x,y;pt(){}pt(int _x,int _y):x(_x),y(_y){}
	friend pt operator+(const pt &a,const pt &b){
		return pt(a.x+b.x,a.y+b.y);
	}friend pt operator-(const pt &a,const pt &b){
		return pt(a.x-b.x,a.y-b.y);
	}friend ll operator*(const pt &a,const pt &b){
		return (ll)a.x*b.y-(ll)b.x*a.y;
	}
};

ll crs(const pt &a,const pt &b,const pt &c){
	return (b-a)*(c-a);
}

const int N=2e5+7;

int n;pt p[N],q[N];

void convex_hull(int m){
	std::sort(q+1,q+m+1,[](const pt &a,const pt &b){
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	});n=0;
	for(int i=1;i<=m;++i){
		while(n>=2&&crs(p[n-1],q[i],p[n])>=0)--n;
		p[++n]=q[i];
	}int k=n;
	for(int i=m;i>=1;--i){
		while(n>k&&crs(p[n-1],q[i],p[n])>=0)--n;
		p[++n]=q[i];
	}if(m>1)--n;
//	cerr<<"convex_hull : ";
//	for(int i=1;i<=n;++i){
//		cerr<<p[i].x<<" "<<p[i].y<<"\n";
//	}
//	cerr<<"------\n";
}

ll calc(ll x,ll y){
	x=abs(x),y=abs(y);
	if(!x||!y)return x+y;
	return std::__gcd(x,y);
}

void Work(){
	cin>>n;int m=n;
	for(int i=1;i<=n;++i)
		cin>>q[i].x>>q[i].y;
	if(n==1){
		cout<<"1\n";
		return;
	}if(n==2){
		cout<<(calc(q[1].x-q[2].x,q[1].y-q[2].y)==1)<<"\n";
		return;
	}
	convex_hull(n);
	ll area=0;p[0]=p[n];
	for(int i=1;i<=n;++i)
		area+=p[i]*p[i-1];
	area=abs(area);
//	cerr<<"area : "<<area<<"\n";
	ll edge=0;
	for(int i=0;i<n;++i){
		edge+=calc(p[i].x-p[i+1].x,p[i].y-p[i+1].y);
//		cerr<<"calc : "<<i<<" "<<edge<<"\n";
	}
//	cerr<<"edge : "<<edge<<"\n";
	int expect=area-edge;
	if(expect&1)
		cout<<"0\n";
	expect/=2;++expect;
//	cerr<<"expect : "<<expect<<"\n";
	cout<<(expect==m-edge)<<"\n";
}

void Main(){
	int T;cin>>T;
	while(T--)
		Work();
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}