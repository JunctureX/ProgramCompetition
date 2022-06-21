#include <bits/stdc++.h>

typedef long long ll;
using std::cin;
using std::cout;
using std::cerr;

const int N=53;

struct pt{
	int x,y;
	friend pt operator-(const pt &a,const pt &b){
		return (pt){a.x-b.x,a.y-b.y};
	}friend ll operator*(const pt &a,const pt &b){
		return (ll)a.x*b.y-(ll)b.x*a.y;
	}
}p[N];

ll crs(const pt &a,const pt &b,const pt &c){
	return (b-a)*(c-a);
}

int cur,n;
char s[N];
bool vs[N];

void go(char c){
	int nx=-1,t=c=='L'?-1:1;
	for(int i=0;i<n;++i)
		if(!vs[i]){
			if(nx==-1||crs(p[cur],p[nx],p[i])*t>0)
				nx=i;
		}
	cur=nx;
	cout<<nx+1<<" ";vs[nx]=true;
}

void Main(){
	cin>>n;
	for(int i=0;i<n;++i)
		cin>>p[i].x>>p[i].y;
	cin>>s;
	cur=0;
	for(int i=1;i<n;++i)
		if(p[i].x<p[cur].x)
			cur=i;
	cout<<cur+1<<" ";vs[cur]=true;
	for(int i=0;i+2<n;++i)
		go(s[i]);
	for(int i=0;i<n;++i)
		if(!vs[i])cout<<i+1<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}
