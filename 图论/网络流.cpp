#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int M=6e6,N=300000;
const int inf=1e9+10;
const int maxn=1e4+100;
int cur[maxn];
int n,m,s,t;
struct stu
{
	int v,next;
	long long val;
}e[M];
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
    memset(dep,0,sizeof(dep));
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
int r,c;
string a[maxn];
int xj[4];
int yj[4];
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
}
 
