//跑完网络流以后，
// 找左边未匹配的点，之后跑交叉路打标记，
// 左边没标记的和右边标记的即为答案
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18+10;
const int maxn=2e6+100;
int cur[maxn];
int n,m,s,t;
struct stu
{
    int v,next;
    long long val;
}e[maxn];
int head[maxn],cnt=1,dep[maxn];
inline void add(int u,int v,long long w)
{
    e[++cnt].next=head[u];
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
    for(int i=s;i<=t;i++) cur[i]=head[i];
    queue<int> q;
    for(int i=s;i<=t;i++) dep[i]=0;
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
int vs[maxn];
int sh[maxn];
inline void dfsa(int x)
{
    vs[x]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        if(e[i].v!=s&&e[i].v!=t&&vs[e[i].v]!=1&&sh[e[i].v]!=0)
        {
            vs[e[i].v]=1;
            dfsa(sh[e[i].v]);
        }
    }
}
signed main()
{
    while(1)
    {
        int r,c,n;
        cin>>r>>c>>n;
        if(r==0&&c==0&&n==0) break;
        s=0;t=r+c+1;
        cnt=1;
        for(int i=1;i<=n;i++)
        {
            int x,y;
            cin>>x>>y;
            add(x,r+y,1);
        }
        for(int i=1;i<=r;i++) add(s,i,1);
        for(int i=1;i<=c;i++) add(i+r,t,1);
        int ans=0;
        while(bfs())
        {
            ans+=dfs(s,inf);
        }
        for(int i=s;i<=t;i++) vs[i]=0;
        for(int i=s;i<=t;i++) sh[i]=0;
        for(int i=1;i<=c;i++)
        {
            for(int j=head[r+i];j;j=e[j].next)
            {
                if(e[j].val==1&&e[j].v!=t)
                {
                    sh[i+r]=e[j].v;
                }
            }
        }
        for(int i=head[s];i;i=e[i].next)
        {
            if(e[i].val==1)
            {
                // cout<<e[i].v<<endl;
                if(vs[e[i].v]==0)
                {
                    dfsa(e[i].v);
                }
            }
        }
        cout<<ans<<' ';
        for(int i=1;i<=r;i++) if(vs[i]==0) cout<<"r"<<i<<' ';
        for(int i=1;i<=c;i++) if(vs[i+r]==1) cout<<"c"<<i<<' ';
        cout<<endl; 
        for(int i=s;i<=t;i++) head[i]=0;
    }
}
