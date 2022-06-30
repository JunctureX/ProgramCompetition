#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#define inf 1000000007
#define N 5010
using namespace std;
int d[N][4],u[N][4],l[N],r[N];
long long f[N][N];
long long sumx[N],sumy[N];
int n,m;
void init()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)l[i]=0;
    for(int i=0;i<=n;i++)r[i]=i;
    for(int i=0;i<=n;i++)sumx[i]=sumy[i]=0;
    for(int i=0;i<=n;i++)
        for(int j=1;j<=3;j++)d[i][j]=i,u[i][j]=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            f[i][j]=0;
    for (int i=1;i<=m;i++) 
    {
        int l,r,x;
        scanf("%d%d%d",&l,&r,&x);
        d[r][x]=min(d[r][x],l);
        u[r][x]=max(u[r][x],l);
    }
}
void walk(int j, int ll, int rr) 
{
    if (l[j]>r[j])return;
    ll=max(ll,l[j]); rr=min(rr,r[j]);
    if (ll<=rr)
    {
        for(int k=l[j];k<ll;k++)sumx[k]=((sumx[k]-f[j][k])%inf+inf)%inf;
        for(int k=r[j];k>rr;k--)sumx[k]=((sumx[k]-f[j][k])%inf+inf)%inf;
        for(int k=l[j];k<ll;k++)sumy[j]=((sumy[j]-f[j][k])%inf+inf)%inf;
        for(int k=r[j];k>rr;k--)sumy[j]=((sumy[j]-f[j][k])%inf+inf)%inf;
        l[j]=ll,r[j]=rr;
        return;
    }
    for(int k=l[j];k<=r[j];k++)sumx[k]=((sumx[k]-f[j][k])%inf+inf)%inf;
    for(int k=l[j];k<=r[j];k++)sumy[j]=((sumy[j]-f[j][k])%inf+inf)%inf;
    l[j]=ll,r[j]=rr;
}
long long dp()
{
    sumx[0]=3; sumy[0]=3;
    f[0][0]=3;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<u[i][2];++j)walk(j,i,i);
        for(int j=u[i][2];j<d[i][1];++j)walk(j,u[i][3],d[i][2]-1);
        for(int j=d[i][1];j<i;++j)walk(j,i,i);
        if (i==n)break; 
        for(int j=u[i][2];j<d[i][1];j++)(f[i][j]+=sumy[j])%=inf;
        for(int j=u[i][3];j<d[i][2];j++)(f[i][j]+=sumx[j])%=inf;
        for(int j=0;j<=i;j++)(sumx[j]+=f[i][j])%=inf;
        for(int j=0;j<=i;j++)(sumy[i]+=f[i][j])%=inf;
    }
    long long ret=0;
    for(int i=u[n][3];i<d[n][2];i++)(ret+=sumx[i])%=inf;
    return ret;
}
int main()
{
    int T;
    cin>>T;
    while (T--)
    {
        init();
        printf("%lld\n",dp());
    }
}