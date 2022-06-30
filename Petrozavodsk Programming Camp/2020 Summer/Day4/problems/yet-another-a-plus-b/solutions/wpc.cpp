#include <cstdio>
#include <vector>
using namespace std;

int tcase,n,m,ans[100010];
char s[200010];

vector<int> vec;
int A[100010],B[100010];

void gao0(int &a,int *A,int &b,int *B)
{
    if(a) A[a--] = 0;
    else B[b--] = 0;
}

void gao1(int &a,int *A,int &b,int *B,int x)
{
    if(!a) { B[b--] = 1; return; }
    else if(!b) { A[a--] = 1; return; }

    int y = b-a+1;
    if(x+y <= vec.size() && n+m-vec[x+y-1] >= b-y) A[a--] = 1;
    else B[b--] = 1;
}

void print()
{
    int i,x,y,a,b;
    short flag = 0;

    for(i=1;i<=n||i<=m;i++)
    {
        a = i <= n ? A[i] : 0;
        b = i <= m ? B[i] : 0;
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
    int i,a,b,x;

    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d%d%s",&n,&m,s+1); vec.clear();
        for(i=1;i<=n+m;i++) if(s[i] == '1') vec.push_back(i);

        for(i=1,a=n,b=m,x=0;i<=n+m;x+=s[i++]-'0') if(s[i] == '0')
        {
            if(a < b) gao0(a,A,b,B);
            else gao0(b,B,a,A);
        }
        else
        {
            if(a < b) gao1(a,A,b,B,x+1);
            else gao1(b,B,a,A,x+1);
        }

        print();
    }

    return 0;
}
