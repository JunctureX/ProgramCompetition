#include<bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::min;
using std::max;

struct pt{
	int x,y;pt(){}pt(int _x,int _y):x(_x),y(_y){}
	friend pt operator+(const pt &a,const pt &b){
		return pt(a.x+b.x,a.y+b.y);
	}friend pt operator-(const pt &a,const pt &b){
		return pt(a.x-b.x,a.y-b.y);
	}friend int operator*(const pt &a,const pt &b){
		return a.x*b.y-b.x*a.y;
	}
};

int crs(const pt &a,const pt &b,const pt &c){
	return (b-a)*(c-a);
}

bool dif_side(const pt &a,const pt &b,const pt &c,const pt &d){
	return crs(a,b,c)*crs(a,b,d)<0;
}

bool inter(const pt &a,const pt &b,const pt &c,const pt &d){
	return dif_side(a,b,c,d)&&dif_side(c,d,a,b);
}

const int N=10;

int n;
int id[N];
pt a[N],b[N];

void Work(){
	cin>>n;
	for(int i=0;i<n;++i)
		cin>>a[i].x>>a[i].y;
	for(int i=0;i<n;++i)
		cin>>b[i].x>>b[i].y;
	for(int i=0;i<n;++i)
		id[i]=i;
	do{
		bool flag=true;
		for(int i=0;i<n&&flag;++i)
			for(int j=i+1;j<n&&flag;++j)
				if(inter(a[i],b[id[i]],a[j],b[id[j]]))
					flag=false;
		if(flag){
			for(int i=0;i<n;++i){
				cout<<2<<"\n";
				cout<<a[i].x<<" "<<a[i].y<<"\n";
				cout<<b[id[i]].x<<" "<<b[id[i]].y<<"\n";
			}
			return;
		}
	}while(std::next_permutation(id,id+n));
	cout<<"fuck\n";
}

void Main(){
	int T;cin>>T;
	while(T--)Work();
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}