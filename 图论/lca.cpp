#include<bits/stdc++.h>
using namespace std;
const int M=500010;
int lg[M];
struct ben
{
	int u,v,w,next;
}e[M<<1];
int head[M],dep[M];
int fat[M][64];
int cnt=1;
inline void add(int u,int v)
{
	e[++cnt].v=v;
	e[cnt].u=u;
	e[cnt].next=head[u];
	head[u]=cnt;
 } 
inline void dfs(int now,int fa)
{
	fat[now][0]=fa;
	dep[now]=dep[fa]+1;
	for(int i=1;i<=lg[dep[now]];i++)
	{
		fat[now][i]=fat[fat[now][i-1]][i-1];
	}
	for(int i=head[now];i;i=e[i].next)
	   if(e[i].v!=fa) dfs(e[i].v,now);
 } 
inline int ask(int x,int y)
{
 	if(dep[x]<dep[y]) swap(x,y);
 	while(dep[x]>dep[y])
 	{
 		x=fat[x][lg[dep[x]-dep[y]]-1]; 
	}
	if(x==y) return x;
	for(int k=lg[dep[x]]-1;k>=0;k--)
	{
		if(fat[x][k]!=fat[y][k])
		{
			x=fat[x][k];
			y=fat[y][k];
		 } 
	}
	return fat[x][0];
} 
int main()
{
	int n,m,s;
	scanf("%d%d%d",&n,&m,&s);
	int u,v;
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d %d",&u,&v);
		add(u,v);
		add(v,u);
	}
	lg[0]=0;
	for(int i=1;i<=M;i++)
	{
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	}
	dfs(s,0);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y); 
	    printf("%d\n",ask(x,y));	
	 } 
 } 
