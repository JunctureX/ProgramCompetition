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

using pii=std::pair<int,int>;
using std::cin;
using std::cerr;
using std::cout;

const int N=3e5+7;

int n,m,ct;
int dif[N];
struct op{int l,r,x;}nd[N];
std::set<int> S;

void modify(int l,int r,int x){
	if(!x)return;
	if(!dif[l])
		S.insert(l);
	else if(dif[l]&&dif[l]+x==0)
		S.erase(l);
	if(!dif[r+1])
		S.insert(r+1);
	else if(dif[r+1]&&dif[r+1]-x==0)
		S.erase(r+1);
	dif[l]+=x;dif[r+1]-=x;
	S.insert(1);S.insert(n+1);
}

void qry(int p){
	auto L=S.upper_bound(p),R=L--;
	cout<<(*L)<<" "<<(*R)-1<<"\n";
}

void Main(){
	n=gi(),m=gi();
	S.insert(1);
	S.insert(n+1);
	while(m--){
		switch(ga()){
			case 'A':{
				int l=gi(),r=gi(),x=gi();
				nd[++ct]={l,r,x};
				modify(l,r,x);
				break;
			}
			case 'B':{
				int p=gi();
				qry(p);
				break;
			}
			case 'C':{
				auto [l,r,x]=nd[ct--];
				modify(l,r,-x);
				break;
			}
		}
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}