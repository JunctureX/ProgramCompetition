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

int var[MAXN];
int to0[MAXN];
int add[MAXN];
int n,k;
char c;
int x,y;
int nxtpos[MAXN][40];
int lstpos[MAXN][40];
int nxtto0[MAXN][40];
LL nxtadd[MAXN][40];
int q[MAXN];
void init()
{

}

void work()
{
	cin>>n>>k;
	for (int i=1;i<=n;i++)
		var[i]=i;
	for (int i=1;i<=k;i++)
	{
		scanf("\n%c%d",&c,&x);
		//WRT(c)
		if (c=='+')
			add[var[x]]++;
		if (c=='E')
		{
			to0[var[x]]=1;
			add[var[x]]=0;
		}
		if (c=='S')
		{
			scanf("%d",&y);
			swap(var[x],var[y]);
		}
	}
	for (int i=1;i<=n;i++)
	{
		//WRT(var[i])
		nxtpos[var[i]][0]=i;
		lstpos[i][0]=var[i];
		nxtadd[i][0]=add[i];
		nxtto0[i][0]=to0[i];
	}
	//for (int i=1;i<=n;i++)
	//	cout<<nxtpos[i][0]<<' '<<lstpos[i][0]<<' '<<nxtto0[i][0]<<' '<<nxtadd[i][0]<<endl;
	for (int j=1;j<40;j++)
		for (int i=1;i<=n;i++)
		{
			nxtpos[i][j]=nxtpos[nxtpos[i][j-1]][j-1];
			lstpos[i][j]=lstpos[lstpos[i][j-1]][j-1];
			int nx=nxtpos[i][j-1];
			nxtto0[i][j]=max(nxtto0[i][j-1],nxtto0[nx][j-1]);
			if (nxtto0[nx][j-1])
				nxtadd[i][j]=nxtadd[nx][j-1];
			else
				nxtadd[i][j]=nxtadd[i][j-1]+nxtadd[nx][j-1];
			//cout<<i<<' '<<j<<' '<<nxtpos[i][j]<<' '<<lstpos[i][j]<<' '<<nxtto0[i][j]<<' '<<nxtadd[i][j]<<endl;
		}
	for (int i=1;i<=n;i++)
	{
		cin>>q[i];
		int stpos=i;
		LL tmp=q[i];
		for (int j=39;j>=0;j--)
			if ((tmp>>j)%2)
				stpos=lstpos[stpos][j];
		//WRT(stpos)
		tmp=q[i];
		LL val=0;
		for (int j=39;j>=0;j--)
			if ((tmp>>j)%2)
			{
				if (nxtto0[stpos][j])
					val=0;
				val+=nxtadd[stpos][j];
				stpos=nxtpos[stpos][j];
				//WRT(val)
			}
		cout<<val<<' ';
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
