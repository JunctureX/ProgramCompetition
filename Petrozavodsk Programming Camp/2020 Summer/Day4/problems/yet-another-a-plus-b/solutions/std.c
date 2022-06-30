#include <stdio.h>

int tcase,n,m,ans[100010];
char s[200010];

int A[100010],B[100010];

void print()
{
    int i,x,y,a,b;
    short flag = 0;

    for(i=1,x=n,y=m;x||y;i++)
    {
        a = x ? A[x--] : 0;
        b = y ? B[y--] : 0;
        ans[i] += a + b;
        ans[i+1] += ans[i] >> 1;
        ans[i] &= 1;
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
    int i,j;

    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d%d%s",&n,&m,s+1);
        if(n < m) n ^= m ^= n ^= m;
        for(i=1;i<=m;i++) B[i] = s[i]-'0';
        for(i=1;i<=n;i++) A[i] = s[m+i] - '0';

        for(j=m;j&&!B[j];j--);
        for(i=1;j&&n-i>m-j;i++) if(!A[i])
        {
            A[i] = 1; B[j] = 0;
            for(;j&&!B[j];j--);
        }

        print();
    }

    return 0;
}