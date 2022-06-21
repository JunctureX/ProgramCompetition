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

struct Rec
{
	int mi,pmi;
	Rec()
	{
		Rec(INF,INF);
	}
	Rec(int x,int y)
	{
		mi=x;
		pmi=y;
		//assert(x<=y);
	}
};

Rec operator+(Rec r1,Rec r2)
{
	if (r1.mi<r2.mi)
		return Rec(r1.mi,min(r1.pmi,r2.mi));
	else
		return Rec(r2.mi,min(r2.pmi,r1.mi));

}
int x[MAXN];
Rec a[MAXN<<2];
#define MID (l+r)/2
#define LS (pos<<1)
#define RS (pos<<1|1)
void pushup(int pos)
{
	a[pos]=a[LS]+a[RS];
}

void build(int pos,int l,int r)
{
	if (l==r)
	{
		a[pos]=Rec(x[l],INF);
		return ;
	}
	build(LS,l,MID);
	build(RS,MID+1,r);
	pushup(pos);
}

Rec query(int pos,int l,int r,int L,int R)
{
	if (l>R || r<L)
		return Rec(INF,INF);
	if (l>=L && r<=R)
		return a[pos];
	return query(LS,l,MID,L,R)+query(RS,MID+1,r,L,R);
}

void init()
{

}
int n,m,l,r;
void work()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		scanf("%d",&x[i]);
	x[0]=n;
	x[n+1]=n+1;
	build(1,0,n+1);
	while (m--)
	{
		scanf("%d%d",&l,&r);
		Rec tmp=query(1,0,n+1,0,l-1)+query(1,0,n+1,r+1,n+1);
		printf("%d\n",tmp.pmi);
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
