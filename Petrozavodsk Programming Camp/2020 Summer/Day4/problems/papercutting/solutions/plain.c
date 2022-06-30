#include <stdio.h>

int tcase,n,m,ans;
char MAP[25][25];

int root[410];
short dir[4][2] = {0,1,1,0,0,-1,-1,0};

short check(int U,int D,int L,int R,short col,int x)
{
    int i,j;

    if(col)
    {
        for(i=1;x-i+1>=L && x+i<=R;i++)
            for(j=U;j<=D;j++)
                if(MAP[j][x-i+1] != MAP[j][x+i]) return 0;
    }
    else
    {
        for(i=1;x-i+1>=U && x+i<=D;i++)
            for(j=L;j<=R;j++)
                if(MAP[x-i+1][j] != MAP[x+i][j]) return 0;
    }

    return 1;
}

int findroot(int nod)
{
    if(root[nod] != nod) root[nod] = findroot(root[nod]);
    return root[nod];
}

int calc(int U,int D,int L,int R)
{
    int i,j,k,x,y,ii,jj,ret = 0;

    for(i=U;i<=D;i++)
        for(j=L;j<=R;j++)
        {
            x = (i-1)*m+j;
            root[x] = x;
        }

    for(i=U;i<=D;i++) for(j=L;j<=R;j++) if(MAP[i][j] == '0')
    {
        x = (i-1)*m+j;
        for(k=0;k<4;k++)
        {
            ii = dir[k][0] + i;
            jj = dir[k][1] + j;
            if(ii < U || jj < L || ii > D || jj > R || MAP[ii][jj] != '0') continue;
            y = (ii-1)*m+jj;
            root[findroot(x)] = findroot(y);
        }
    }

    for(i=U;i<=D;i++) for(j=L;j<=R;j++) if(MAP[i][j] == '0')
    {
        x = (i-1)*m+j;
        if(findroot(x) == x) ret++;
    }
    return ret;
}

void dfs(int U,int D,int L,int R,short col)
{
    int i,x;

    if(col)
    {
        x = calc(U,D,L,R);
        if(x < ans) ans = x;
        for(i=L;i<R;i++) if(check(U,D,L,R,1,i))
        {
            if(i-L+1 < R-i) dfs(U,D,i+1,R,1);
            else dfs(U,D,L,i,1);
        }
    }
    else
    {
        for(i=U;i<D;i++) if(check(U,D,L,R,0,i))
        {
            if(i-U+1 < D-i) dfs(i+1,D,L,R,0);
            else dfs(U,i,L,R,0);
        }
        dfs(U,D,L,R,1);
    }
}

int main()
{
    int i;

    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++) scanf("%s",MAP[i]+1);

        ans = n*m;
        dfs(1,n,1,m,0);
        printf("%d\n",ans);
    }

    return 0;
} 
