#include<bits/stdc++.h>

using ll=long long;
using std::string;
using pii=std::pair<int,int>;
using std::cin;
using std::cerr;
using std::cout;
using std::min;
using std::max;

const int mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}

const int N=5e2+7;

int n;
int cnt[N];
string pr[N],sf[N],S;
struct node{
	int typ,id;
	string s;
};
std::vector<node> lst[N];

void work(int u){
	int m;cin>>m;
	lst[u].resize(m);
	for(auto &nd:lst[u]){
		string s;cin>>s;
		if(isdigit(s[0])){
			nd.typ=0;sscanf(s.c_str(),"%d",&nd.id);
		}else {
			nd.typ=1;nd.s=s;
		}
	}
}

int calc(const string &t,const string &s){
	std::vector<int> nx(t.size(),-1);
	for(int i=1,j=-1;i<t.size();++i){
		while(j!=-1&&t[j+1]!=t[i])
			j=nx[j];
		if(t[j+1]==t[i])++j;
		nx[i]=j;
	}int ans=0;
	for(int i=0,j=-1;i<s.size();++i){
		while(j!=-1&&t[j+1]!=s[i])
			j=nx[j];
		if(t[j+1]==s[i])++j;
		if(j+1u==t.size())
			++ans,j=nx[j];
	}return ans;
}

void get_pr(int u,int l,int p,string &str){
	if(p==lst[u].size())return;
	if(lst[u][p].typ==0){
		int v=lst[u][p].id;
		if(pr[v].size()>=l)
			str+=pr[v].substr(0,l);
		else{
			str+=pr[v];
			get_pr(u,l-pr[v].size(),p+1,str);
		}
	}else {
		auto &s=lst[u][p].s;
		if(s.size()>=l)
			str+=s.substr(0,l);
		else {
			str+=s;
			get_pr(u,l-s.size(),p+1,str);
		}
	}
}

void get_sf(int u,int l,int p,string &str){
	if(p==-1)return;
	if(lst[u][p].typ==0){
		int v=lst[u][p].id;
		if(sf[v].size()>=l)
			str=sf[v].substr(sf[v].size()-l,l);
		else{
			get_sf(u,l-sf[v].size(),p-1,str);
			str+=sf[v];
		}
	}else{
		auto &s=lst[u][p].s;
		if(s.size()>=l)
			str=s.substr(s.size()-l,l);
		else {
			get_sf(u,l-s.size(),p-1,str);
			str+=s;
		}
	}
}

void Calc(int u){
	for(auto &[typ,id,s]:lst[u]){
		if(!typ)
			Inc(cnt[u],cnt[id]);
		else Inc(cnt[u],calc(S,s));
	}get_pr(u,S.size()-1,0,pr[u]);
	get_sf(u,S.size()-1,lst[u].size()-1,sf[u]);
	for(size_t i=0;i+1<lst[u].size();++i){
		string fi,se;
		get_pr(u,S.size()-1,i+1,se);
		if(lst[u][i].typ){
			string &s=lst[u][i].s;
			fi=s.size()+1<S.size()?s:s.substr(s.size()-S.size()+1,S.size()-1);;
		}else {
			fi=sf[lst[u][i].id];
		}
		
		Inc(cnt[u],calc(S,fi+se));
	}
}

void Main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		work(i);
	cin>>S;
	for(int i=1;i<=n;++i)
		Calc(i);
	cout<<cnt[n]<<"\n";
}

inline void File(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
#ifdef zxyoi
	freopen("my.in","r",stdin);
#endif
}signed main(){File();Main();return 0;}
