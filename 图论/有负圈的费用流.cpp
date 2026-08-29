#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e9+10;
const int M=1e7+10,N=1e7+10;
int n,m,s,t;
struct stu
{
	int v,next,w;
	int val;
}e[M];
int cur[N];
int head[N],cnt=1,dis[N],vis[N];
int mia=0;
inline void add(int u,int v,int w,int ww)
{
	e[++cnt].next=head[u];
	e[cnt].v=v;
	e[cnt].val=w;
	e[cnt].w=ww;
	head[u]=cnt;
	e[++cnt].next=head[v];
	e[cnt].v=u;
	e[cnt].val=0;
	e[cnt].w=-ww;
	head[v]=cnt;
}
queue<int> q;
inline int bfs()
{
	for(int i=0;i<=n+1;i++) vis[i]=0;
	for(int i=0;i<=n+1;i++) dis[i]=inf;
    for(int i=0;i<=n+1;i++) cur[i]=head[i];
	q.push(s);
	vis[s]=1;
	dis[s]=0;
	while(!q.empty())
	{
        int u=q.front();
		// cout<<u<<endl;
        // cout<<u<<endl;
		q.pop();
		vis[u]=0;
		for(int i=head[u];i!=0;i=e[i].next)
		{
            int v=e[i].v;
			if(dis[u]+e[i].w<dis[v]&&e[i].val>0)
			{
				dis[v]=dis[u]+e[i].w;
				if(vis[v]==0)
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
    // cout<<t<<' '<<dep[t]<<endl;
	if(dis[t]!=inf) return 1;
	else return 0;
}
inline int dfs(int u,int in)
{
	long long out=0;
	if(t==u) return in;
	vis[u]=1;
	for(int i=cur[u];i!=0&&in;i=e[i].next)
	{
        cur[u]=i;
		int v=e[i].v;
		if(vis[v]==1||e[i].val==0||dis[v]!=dis[u]+e[i].w) continue;
		long long k=dfs(v,min(in,e[i].val));
		out=out+k;
		in=in-k;
		e[i].val-=k;
		e[i^1].val+=k;
		mia+=k*e[i].w;
        if(in==0) break;
	}
	if(out==0) dis[u]=inf;
	vis[u]=0;
	return out;
}
int dx[M];
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int S,T;
    cin>>n>>m>>S>>T;
    s=0,t=n+1;
    int sum=0;
    for(int i=1;i<=m;i++)
    {
        int x,y,f,v;
        cin>>x>>y>>f>>v;
        if(v<0)
        {
            dx[x]-=f;
            dx[y]+=f;
            sum+=f*v;
            add(y,x,f,-v);
        }
        else
        {
            add(x,y,f,v);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(dx[i]>0) add(s,i,dx[i],0);
        else if(dx[i]<0) add(i,t,-dx[i],0);
    }
    add(T,S,inf,0);
    int ans=0;
    while(bfs())
    {
        // cout<<1<<endl;
        dfs(s,inf);
    }
    ans=e[cnt].val;
    // cout<<1<<endl;
    e[cnt].val=e[cnt-1].val=0;
    s=S;
    t=T;
    while(bfs())
    {
        ans+=dfs(s,inf);
    }
    cout<<ans<<' '<<mia+sum<<endl;
} 
