#include <bits/stdc++.h>

using db=double;
using std::cin;
using std::cout;
using std::cerr;

const db pi=acos(-1);
const db eps=1e-8;

int m;
db R;

db cal_ang(db a,db b,db c){
	return acos((a*a+b*b-c*c)/2/a/b);
}

void Work(){
	cin>>m>>R;db ans=2*pi*R;
	while(m--){
		db x,y,r;
		cin>>x>>y>>r;
		db d=sqrt(x*x+y*y);
		if(d>=R+r+eps)continue;
		if(d<=abs(R-r)-eps)continue;
		db a=cal_ang(R,d,r);
		ans-=2*a*R;
		a=cal_ang(r,d,R);
		ans+=2*a*r;
	}cout<<ans<<"\n";
}

void Main(){
	int T;cin>>T;
	while(T--)
		Work();
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
	cout<<std::fixed<<std::setprecision(10);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}