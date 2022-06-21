#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
inline void read(int &x)
{
    x=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
}
const int maxn=2e5+5;
int n,m;
ll ans[4],res[4];
struct SegmentTree{
    int d[maxn<<2][4],f[maxn<<2][4];
    ll s[maxn<<2][4];
    #define lc x<<1
    #define rc x<<1|1
    void FoundData(int x) 
    {
        for(int i=0;i<4;++i)
        {
            d[x][i]=d[lc][i]+d[rc][i];
            s[x][i]=s[lc][i]+s[rc][i];
        }
    }
    void BuildTree(int x,int l,int r)
    {
        if(l==r)
        {
            char c=getchar();
            switch(c)
            {
                case 'E':
                    d[x][0]=s[x][0]=1;break;
                case 'S':
                    d[x][1]=s[x][1]=1;break;
                case 'W':
                    d[x][2]=s[x][2]=1;break;
                case 'N':
                    d[x][3]=s[x][3]=1;break;
                exit(0);
            }
            return ;
        }
        int mid=l+r>>1;
        BuildTree(lc,l,mid);
        BuildTree(rc,mid+1,r);
        FoundData(x);
    }
    void Upit(int x,int p,int w)
    {
        f[x][p]+=w;
        s[x][p]+=d[x][p]*w;
    }
    void LazyDown(int x)
    {
        for(int i=0;i<4;++i)
            if(f[x][i])
            {
                s[x][i]+=1ll*d[x][i]*f[x][i];
                Upit(lc,i,f[x][i]);
                Upit(rc,i,f[x][i]);
                f[x][i]=0;
            }
    }
    void Updata(int x,int l,int r,int L,int R,int p,int w)
    {
        if(L<=l&&r<=R) return Upit(x,p,w);
        int mid=l+r>>1;LazyDown(x);
        if(R<=mid) Updata(lc,l,mid,L,R,p,w);
        else if(L>mid) Updata(rc,mid+1,r,L,R,p,w);
        else Updata(lc,l,mid,L,mid,p,w),Updata(rc,mid+1,r,mid+1,R,p,w);
        FoundData(x);
    }
    void Query(int x,int l,int r,int L,int R)
    {
        if(L<=l&&r<=R)
        {
            for(int i=0;i<4;++i) 
            {
                res[i]+=s[x][i];
            }
            return ;
        }
        int mid=l+r>>1;LazyDown(x);
        if(R<=mid) Query(lc,l,mid,L,R);
        else if(L>mid) Query(rc,mid+1,r,L,R);
        else Query(lc,l,mid,L,mid),Query(rc,mid+1,r,mid+1,R);
        FoundData(x);
    }
}sgt;
void clear() {for(int i=0;i<4;++i) res[i]=0;}
signed main()
{
    read(n),read(m);
    sgt.BuildTree(1,1,n);
    while(m--)
    {
        int op,l,r,t;
        read(op),read(l),read(r);
        if(op==1)
        {
            char c=getchar();
            switch(c)
            {
                case 'E':
                    sgt.Updata(1,1,n,l,r,0,1);break;
                case 'S':
                    sgt.Updata(1,1,n,l,r,1,1);break;
                case 'W':
                    sgt.Updata(1,1,n,l,r,2,1);break;
                case 'N':
                    sgt.Updata(1,1,n,l,r,3,1);break;
                exit(0);
            }
        }
        else
        {
            read(t);
            clear();
            sgt.Query(1,1,n,l,r);
            for(int i=0;i<4;++i)
            {
                ans[i]=res[i]*(t/(r-l+1));
            }
            clear();
            if(t%(r-l+1)) sgt.Query(1,1,n,l,l+(t%(r-l+1))-1);
            for(int i=0;i<4;++i)
            {
                ans[i]+=res[i];
            }
            printf("%lld %lld\n",ans[0]-ans[2],ans[3]-ans[1]);
        }
    }
    return 0;
}
/*
11 4
NSWWNSNEEWN
2 1 11 12
1 1 4 W
1 1 4 W
2 1 5 11
*/
