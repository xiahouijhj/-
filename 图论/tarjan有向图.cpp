#include<bits/stdc++.h>
using namespace std;
const int maxn=100003;
int cnt=1;
struct node
{
    int u,v,w,next;
}e[maxn];
int low[maxn],dfn[maxn],sta[maxn],sd[maxn],vis[maxn],head[maxn];
int t=1,hh=1;
inline void add(int u,int v)
{
    e[++cnt].v=v;
    e[cnt].u=u;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void tarjan(int x)
{
    low[x]=dfn[x]=++t;
    sta[++hh]=x;vis[x]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(vis[v])
        {
            low[x]=min(low[x],low[v]);
        }
    }
    if(dfn[x]==low[x])
    {
        int y;
        while(y=sta[hh--])
        {
            sd[y]=x;
            vis[y]=0;
            if(x==y) break;
        }
    }
}
