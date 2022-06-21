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

LL n,m;
LL dp[33][33];
void init()
{

}

void work()
{
	cin>>n>>m;
	n--,m--;
	MST(dp,INF);
	dp[0][0]=0;
	int ln=64-__builtin_clzll(n)-1;
	int lm=64-__builtin_clzll(m)-1;
	if (n==0)
		ln=0;
	if (m==0)
		lm=0;
	//cout<<ln<<' '<<lm<<endl;
	for (int i=0;i<=ln+1;i++)
		for (int j=0;j<=lm+1;j++)
		{
			if (i<=ln)
				dp[i+1][j]=min(dp[i+1][j],dp[i][j]*2ll+(n>>(ln-i))%2);
			if (j<=lm)
				dp[i][j+1]=min(dp[i][j+1],dp[i][j]*2ll+(m>>(lm-j))%2);
		}
	cout<<dp[ln+1][lm+1]<<endl;
}

int main()
{
	init();
	int casenum=1;
	scanf("%d",&casenum);
	for (int testcase=1;testcase<=casenum;testcase++)
	{
		#ifdef _DEBUG_
		printf("Case #%d:\n",testcase);
		#endif
		work();
	}
	return ~~(0^_^0);
}
