#include<bits/stdc++.h>
using namespace std;
int n,d[9999],dd[9999];
char s[10],t[10];
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        for(int i='a';i<='z';++i) d[i]=dd[i]=0;
        scanf("%s",s+1);
        scanf("%s",t+1);
        for(int i=1;i<=5;++i) ++d[t[i]],++dd[s[i]];
        for(int i=1;i<=5;++i)
            if(s[i]==t[i]) putchar('g');
            else if(s[i]!=t[i]&&dd[s[i]]>d[s[i]]) putchar('x');
            else putchar('y');
        putchar('\n');
    }
    return 0;
}

/*
4 
teeth
earth
robot
tooth
favor
vague
apple
opera
*/
