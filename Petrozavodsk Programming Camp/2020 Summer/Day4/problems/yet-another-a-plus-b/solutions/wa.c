#include <stdio.h>
#include <assert.h>

int tcase,n,m,ans[100010];
char s[200010];

int nxt[200010][10],A[100010],B[100010];

int find(int l,int r)
{
    int i;
    for(i=9;i>=0;i--) if(nxt[l][i] <= r) return nxt[l][i];
    assert(0); return -1;
}

void gao()
{
    int i,x,y,a,b;
    short flag = 0;

    for(i=1,x=n,y=m;x||y;i++)
    {
        a = x ? A[x--] : 0;
        b = y ? B[y--] : 0;
        ans[i] += a + b;
        ans[i+1] += ans[i] / 2;
        ans[i] %= 2;
    }

    for(;i;i--)
    {
        if(ans[i]) flag = 1;
        if(flag) printf("%d",ans[i]);
        ans[i] = 0;
    }
    if(!flag) printf("0");
    printf("\n");
}

int main()
{
    int i,j,x,y,z;

    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d%d%s",&n,&m,s+1);

        for(j=0;j<=9;j++) nxt[n+m+1][j] = n+m+1;
        for(i=n+m;i;i--) for(j=0;j<=9;j++)
        {
            if(s[i] == j + '0') nxt[i][j] = i;
            else nxt[i][j] = nxt[i+1][j];
        }

        x = n; y = m;
        while(x || y)
        {
            if(x > y)
            {
                x--;
                z = find(n+m-x-y,n+m-x);
                A[n-x] = s[z] - '0';
                for(i=n+m-x-y;i<z;i++) y--, B[m-y] = s[i] - '0';
            }
            else
            {
                y--;
                z = find(n+m-x-y,n+m-y);
                B[m-y] = s[z] - '0';
                for(i=n+m-x-y;i<z;i++) x--, A[n-x] = s[i] - '0';
            }
        }

        gao();
    }

    return 0;
}
