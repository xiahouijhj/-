#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
int n,m;
int cnt=0;
int cn=0;
int vis[maxn],d[maxn],c[maxn];
stack<int> s;
int dfn[maxn],low[maxn];
vector<int> u[maxn];
inline void tarjan(int now)
{
    dfn[now]=low[now]=++cnt;
    vis[now]=1;
    s.push(now);
    for(int v:u[now])
    {
        if(!dfn[v])
        {
            tarjan(v);
            low[now]=min(low[now],low[v]);
        }
        else if(vis[v])
        {
            low[now]=min(low[now],low[v]);
        }
    }
    if(low[now]==dfn[now])
    {
        cn++;
        int t;
        while(1)
        {
            t=s.top();
            s.pop();
            vis[t]=0;
            d[t]=cn;
            if(t==now) break;
        }
    }
}
int main()
{
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,a,b,y;
        cin>>x>>a>>y>>b;
        u[x+(a^1)*n].push_back(y+b*n);
        u[y+(b^1)*n].push_back(x+a*n);
    }
    for(int i=1;i<=2*n;i++)
    {
        if(dfn[i]==0)
        {
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(d[i]==d[i+n])
        {
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
    }
    cout<<"POSSIBLE"<<endl;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        int h=0;
        if(d[i+n]<d[i]) h=1; 
        cout<<h<<' ';
    }
    cout<<endl;
}
