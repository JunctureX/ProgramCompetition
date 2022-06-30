#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 1e9
using namespace std;

int tcase,n,K,ans1,ans2;

int e[2000010][2],p[1000010];
int root,sum;
int q[1000010],dis[1000010];

void adde(int sn,int fn,int id)
{
    e[id][0] = fn; e[id][1] = p[sn]; p[sn] = id;
}

int bfs(int S)
{
    int i,sn,fn,head = 1,tail = 2;
    memset(dis,-1,sizeof(int)*(K+3));
    q[1] = S; dis[S] = 0;

    while(head != tail)
    {
        sn = q[head++];
        for(i=p[sn];i;i=e[i][1])
        {
            fn = e[i][0];
            if(dis[fn] >= 0) continue;
            dis[fn] = dis[sn] + 1;
            q[tail++] = fn;
        }
    }

    return q[head-1];
}

int main()
{
    int i,j,a,b,x,y;

    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d",&n);
        sum = 0; ans1 = -INF; ans2 = INF;

        for(i=1;i<=n;i++)
        {
            scanf("%d",&K);
            memset(p,0,sizeof(int)*(K+3));
            for(j=1;j<=K;j++)
            {
                scanf("%d",&x);
                if(!x) root = j;
                else adde(x,j,j<<1), adde(j,x,j<<1|1);
            }
            
            if(K == 1) continue;
            x = bfs(root); a = dis[x]*2;
            y = bfs(x); b = dis[y];
            sum += a; ans1 = max(ans1,b-a); ans2 = min(ans2,b-a);
        }

        if(ans1 == -INF) ans1 = 0;
        if(ans2 == INF) ans2 = 0;
        printf("%d %d\n",ans1+sum,ans2+sum);
    }

    return 0;
}