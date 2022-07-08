#include <bits/stdc++.h>

using ll=long long;
using std::cin;
using std::cout;
using std::cerr;
using std::string;
using std::min;
using std::max;

const int N=4e2+7;
const int N2=N*N;

int n,m,Q;

bool mrk[N2];
bool vs[N][N][2];
int vl[N][N];

void Work(){
	cin>>n>>m>>Q;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			cin>>vl[i][j];
	while(Q--){
		int x,y;cin>>x>>y;
		string s;cin>>s;
		int xl=x,xr=x,yl=y,yr=y;
		for(auto c:s){
			switch(c){
				case 'R':{
					vs[x][y][1]=true;
					xr=max(xr,++x);
					break;
				}
				case 'L':{
					xl=min(xl,--x);
					vs[x][y][1]=true;
					break;
				}
				case 'U':{
					vs[x][y][0]=true;
					yr=max(yr,++y);
					break;
				}
				case 'D':{
					yl=min(yl,--y);
					vs[x][y][0]=true;
					break;
				}
			}
		}
		std::vector<int> vec;
		for(int i=xl;i<xr;++i)
			for(int j=yl;j<yr;++j)
				if(vs[i][j][0]&&vs[i][j][1]){
					if(!mrk[vl[i+1][j+1]])
						vec.push_back(vl[i+1][j+1]),mrk[vl[i+1][j+1]]=true;
					vs[i][j+1][1]^=1,vs[i+1][j][0]^=1;
					vs[i][j][0]=vs[i][j][1]=false;
				}
		cout<<vec.size()<<"\n";
		for(auto t:vec)mrk[t]=false;
	}
	
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