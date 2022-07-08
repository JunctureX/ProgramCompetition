#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

const int N=8e3+7;

const int M=N<<2|7;

#define lc (u<<1)
#define rc (lc|1)
#define md ((l+r)>>1)
#define Lc lc,l,md
#define Rc rc,md+1,r

int n;
int rk[N];
bool chk[M];
int mnp[M];

void build(int u,int l,int r){
	chk[u]=true;mnp[u]=1e9;
	if(l==r)return;
	build(Lc);build(Rc);
}

std::vector<int> vec;

void get_ins(int u,int l,int r,int p){
	if(l==r){
		chk[u]=true;
		mnp[u]=p;
		return;
	}chk[u]=false;
	p<=md?get_ins(Lc,p):get_ins(Rc,p);
	if(chk[lc]&&mnp[lc]<=n)vec.push_back(mnp[lc]);
	if(chk[rc]&&mnp[rc]<=n)vec.push_back(mnp[rc]);
}

void get_del(int u,int l,int r,int p){
	if(l==r){
		chk[u]=true;
		mnp[u]=1e9;
		return;
	}chk[u]=false;
	p<=md?get_del(Lc,p):get_del(Rc,p);
	if(chk[lc]&&mnp[lc]<=n)vec.push_back(mnp[lc]);
	if(chk[rc]&&mnp[rc]<=n)vec.push_back(mnp[rc]);
}

void update(int u,int l,int r){
	if(chk[u])return;
	update(Lc);update(Rc);
	chk[u]=true;
	int lp=mnp[lc],rp=mnp[rc];
	if(lp>n&&rp>n)
		mnp[u]=1e9;
	else if(lp>n)
		mnp[u]=rp;
	else if(rp>n)
		mnp[u]=lp;
	else mnp[u]=rk[lp]<rk[rp]?lp:rp;
}

void Main(){
	cin>>n;
	build(1,1,n);
	int T=n+n;
	while(T--){
		string s;cin>>s;
		int x;cin>>x;
		if(s=="add"){
			get_ins(1,1,n,x);
		}else {
			get_del(1,1,n,x);
		}
		cout<<vec.size()<<" ";
		for(auto t:vec)
			cout<<t<<" ";
		cout<<endl;
	//	cerr<<"the query\n";
		std::fflush(stdout);
	//	cerr<<"vec : ";
		for(size_t i=1;i<=vec.size();++i){
	//		cerr<<"i : "<<i<<"\n";
			int p;cin>>p;
			rk[p]=i;
		}update(1,1,n);
		vec.clear();
//		cerr<<"GetMin\n";
		if(mnp[1]>n)
			cout<<-1<<"\n";
		else cout<<mnp[1]<<"\n";
		std::fflush(stdout);
	}
}

inline void File(){
	// interactive problem
}signed main(){File();Main();return 0;}