
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9+10;
const int maxn=1e6+100;
int cur[maxn];
int n,m,s,t;
struct stu
{
    int v,next,u;
    long long val;
}e[maxn];
int head[maxn],cnt=1,dep[maxn];
inline void add(int u,int v,long long w)
{
    e[++cnt].next=head[u];
    e[cnt].u=u;
    e[cnt].v=v;
    e[cnt].val=w;
    head[u]=cnt;
    e[++cnt].next=head[v];
    e[cnt].v=u;
    e[cnt].val=0;
    head[v]=cnt;
}
inline bool bfs()
{
    for(int i=0;i<=n;i++) cur[i]=head[i];
    queue<int> q;
    for(int i=0;i<=n;i++) dep[i]=0;
    q.push(s);
    dep[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i!=0;i=e[i].next)
        {
            int v=e[i].v;
            if(dep[v]==0&&e[i].val>0)
            {
                dep[v]=dep[u]+1;
                if(v==t) return true;
                q.push(v);
            }
        }
    }
    // if(dep[t]!=0) return 1;
    return false;
}
inline int dfs(int u,long long in)
{
    long long out=0;
    if(t==u) return in;
    for(int i=cur[u];i!=0&&in;i=e[i].next)
    {
        cur[u]=i;
        int v=e[i].v;
        if(e[i].val==0||dep[v]!=dep[u]+1) continue;
        long long k=dfs(v,min(in,e[i].val));
        out=out+k;
        in=in-k;
        e[i].val-=k;
        e[i^1].val+=k;
        if(in==0) break;
    }
    if(out==0) dep[u]=0;
    return out;
}
int cn=1;
struct node
{
    int u,v,w,next;
}ee[maxn];
int low[maxn],dfn[maxn],sta[maxn],sd[maxn],vis[maxn],hea[maxn];
int tt=1,hh=1;
inline void ad(int u,int v)
{
    ee[++cn].v=v;
    ee[cn].u=u;
    ee[cn].next=hea[u];
    hea[u]=cn;
}
inline void tarjan(int x)
{
    low[x]=dfn[x]=++tt;
    sta[++hh]=x;vis[x]=1;
    for(int i=hea[x];i;i=ee[i].next)
    {
        int v=ee[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(vis[v])
        {
            low[x]=min(low[x],dfn[v]);
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
signed main()
{
    memset(vis,0,sizeof(vis));
    memset(head,0,sizeof(head));
    memset(hea,0,sizeof(hea));
    memset(dfn,0,sizeof(dfn));
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        add(x,y,w);
    }
    int ans=0;
    while(bfs()) ans+=dfs(s,inf);
    // cout<<ans<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=head[i];j!=0;j=e[j].next)
        {
            int v=e[j].v;
            if(e[j].val==0) continue;
            // cout<<i<<' '<<v<<endl;
            ad(i,v);
        }
    }
    for(int i=1;i<=n;i++) if(dfn[i]==0) tarjan(i);
    for(int i=1;i<=m;i++)
    {
        int u=e[i*2].u;
        int v=e[i*2].v;
        if(e[i*2].val!=0) cout<<0<<' '<<0<<endl;
        else
        {
            if(sd[u]==sd[v]) cout<<0<<' ';
            else cout<<1<<' ';
            if(sd[u]==sd[s]&&sd[v]==sd[t]) cout<<1<<endl;
            else cout<<0<<endl;
        }
    }
}
