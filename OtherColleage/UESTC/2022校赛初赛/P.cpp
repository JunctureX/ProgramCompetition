#include<bits/stdc++.h>

using std::cin;
using std::cerr;
using std::cout;

const int N=1e4+7;

bool vs[N];
struct node{int a,b,c;}mk[N];

void Main(){
	std::queue<int> Q;
	Q.push(0);vs[0]=true;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		auto t=mk[u];
		if(u+8<N&&!vs[u+8]){
			vs[u+8]=true;Q.push(u+8);
			++t.a;mk[u+8]=t;--t.a;
		}if(u+9<N&&!vs[u+9]){
			vs[u+9]=true;Q.push(u+9);
			++t.b;mk[u+9]=t;--t.b;
		}if(u+10<N&&!vs[u+10]){
			vs[u+10]=true;Q.push(u+10);
			++t.c;mk[u+10]=t;--t.c;
		}
	}int T;cin>>T;
	while(T--){
		int x;cin>>x;
		if(!vs[x]){
			cout<<-1<<"\n";
		}else {
			cout<<mk[x].a<<" "<<mk[x].b<<" "<<mk[x].c<<"\n";
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