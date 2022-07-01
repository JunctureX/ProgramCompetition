#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;


const int N=2e5+7;
char s[N];
ll st[N],typ[N],tp;
int rec[N],op;
ll ans;

namespace Roll{

const int N=::N*100;

ll *st[N],vl[N];int tp;

void pack(ll &A){
	st[++tp]=&A;
	vl[tp]=A;
}

void roll(int rec){
	while(tp>rec)
		*st[tp]=vl[tp],--tp;
}

}

using Roll::pack;
using Roll::roll;

void Main(){
	cin>>s;int n=strlen(s);
	typ[0]=1;
	for(int i=0;i<n;++i){
	//	cerr<<s[i]<<" ";
		switch(s[i]){
			case '(':{
				rec[++op]=Roll::tp;
				pack(tp);++tp;
				pack(typ[tp]);
				pack(st[tp]);
				typ[tp]=0;
				st[tp]=0;
				break;
			}
			case ')':{
				rec[++op]=Roll::tp;
				if(typ[tp]==0){
					pack(tp);pack(typ[tp]);
					pack(st[tp]);pack(ans);
					--tp;++ans;
					if(typ[tp]==0){
						ans+=st[tp];
						pack(st[tp]);
						++st[tp];
					}else if(typ[tp]==1){
						ans+=st[tp];
						pack(st[tp]);
						++st[tp];
					}else {
						++tp;
						typ[tp]=1;
						st[tp]=1;
					}
				}else if(typ[tp]==1){
					pack(tp);++tp;
					pack(typ[tp]);typ[tp]=2;
				}else if(typ[tp]==2){
					pack(tp);++tp;
					pack(typ[tp]);typ[tp]=2;
				}
				break;
			}
			case '-':{
				roll(rec[op--]);
				break;
			}
		}
		cout<<ans<<"\n";
	}
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}