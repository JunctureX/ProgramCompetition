#include <bits/stdc++.h>
#define DB double
#define LL long long

#define MST(a,b) memset((a),(b),sizeof(a))

#ifdef _DEBUG_
#define MRK() cout<<"Mark"<<endl;
#define WRT(x) cout<<#x<<" = "<<(x)<<endl;
#else
#define MRK() ;
#define WRT(x) ;
#endif

#define MAXN 1010000
#define MAXM 2010000
#define MOD 998244353  //1000000007
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define EPS 1e-5

#define _ 0
using namespace std;
int n,m;
LL a[MAXN],q[MAXN];
void init()
{

}
typedef pair<int,int> pii;
void work()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	for (int i=1;i<=m;i++)
	{
		cin>>q[i];
	}
	LL sum=0;
	int ptr=1;
	for (int i=1;i<=n;i++)
	{
		LL cnt=1;
		LL val=a[i];
		while (val%3==0)
		{
			val/=3;
			cnt*=3;
		}
		while (ptr<=m && q[ptr]>sum && q[ptr]<=sum+cnt)
		{
			printf("%lld ",val);
			ptr++;
		}
		sum+=cnt;
	}
}

int main()
{
	init();
	int casenum=1;
	//scanf("%d",&casenum);
	for (int testcase=1;testcase<=casenum;testcase++)
	{
		#ifdef _DEBUG_
		printf("Case #%d:\n",testcase);
		#endif
		work();
	}
	return ~~(0^_^0);
}
