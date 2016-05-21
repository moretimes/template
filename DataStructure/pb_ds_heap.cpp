#include<iostream>
#include<cstdio>
#include<cstring>
#include<ext/pb_ds/priority_queue.hpp>
#define ll long long
#define pa pair<ll,int>
#define llinf 9000000000000000000LL
using namespace std;
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<pa,greater<pa>,pairing_heap_tag > heap;
int n,m,cnt,last[1000005];
int T,rxa,rxc,rya,ryc,rp;
heap::point_iterator id[1000005];
int x,y,z;
ll dis[1000005];
struct data{int to,next,v;}e[10000005];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void insert(int u,int v,int w)
{
    e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;
}
void dijkstra()
{
    heap q;
    for(int i=1;i<=n;i++)dis[i]=llinf;
    dis[1]=0;id[1]=q.push(make_pair(0,1));
    while(!q.empty())
    {
        int now=q.top().second;q.pop();
        for(int i=last[now];i;i=e[i].next)
            if(e[i].v+dis[now]<dis[e[i].to])
            {
                dis[e[i].to]=e[i].v+dis[now];
                if(id[e[i].to]!=0)
                    q.modify(id[e[i].to],make_pair(dis[e[i].to],e[i].to));
                else id[e[i].to]=q.push(make_pair(dis[e[i].to],e[i].to));
            }
    }
}
int main()
{
    n=read();m=read();
    T=read();rxa=read();rxc=read();rya=read();ryc=read();rp=read();
    int a,b;
    for(int i=1;i<=T;i++)
    {
        x=((ll)x*rxa+rxc)%rp;
        y=((ll)y*rya+ryc)%rp;
        a=min(x%n+1,y%n+1);
        b=max(y%n+1,y%n+1);
        insert(a,b,100000000-100*a);
    }
    for(int i=1;i<=m-T;i++)
    {
        x=read(),y=read(),z=read();
        insert(x,y,z);
    }
    dijkstra();
    printf("%lld",dis[n]);
    return 0;
}
