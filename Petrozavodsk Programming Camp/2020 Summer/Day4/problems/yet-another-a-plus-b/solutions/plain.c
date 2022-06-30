#include <stdio.h>

int tcase,n,m;
char s[200010];
long long ans,A,B;

int calc(int x)
{
    int ret = 0;
    for(;x;x>>=1) ret += x&1;
    return ret;
}

void gao(int x)
{
    int i;
    long long a = 0,b = 0;
    for(i=1;i<=n+m;i++,x>>=1)
    {
        if(x&1) a = a*2 + s[i]-'0';
        else b = b*2 + s[i]-'0';
    }
    if(a + b > ans) ans = a + b, A = a, B = b;
}

void print()
{
    int i,t[20] = {0};
    if(!ans) { printf("0\n"); return; }
    for(i=1;ans;ans>>=1,i++) t[i] = ans & 1;
    for(i--;i;i--) printf("%d",t[i]);
    printf("\n");
}

int main()
{
    int i;
    scanf("%d",&tcase);

    while(tcase--)
    {
        scanf("%d%d%s",&n,&m,s+1); ans = 0;
        for(i=(1<<(n+m))-1;i;i--) if(calc(i) == n) gao(i);
        print();
    }

    return 0;
}
