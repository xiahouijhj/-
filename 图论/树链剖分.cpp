#include<bits/stdc++.h>
using namespace std;
const int M=1e5+60;
struct be
{
	int v,next;
}e[M<<2];
struct ben
{
	int v,add;
}t[M<<1];
int head[M];
int n,m,r,p,cnt=1,cn=0;
int a[M];
long long top[M],dep[M],son[M],ww[M],fa[M],size[M],id[M];
inline void add(int u,int v)
{
	e[++cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline void dfs1(int now,int fat,int de)
{
	dep[now]=de;
	size[now]=1;
	fa[now]=fat;
	int maxson=-1;
	for(int i=head[now];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==fat) continue; 
		dfs1(v,now,de+1);
		size[now]+=size[v];
		if(size[v]>maxson)
		{
			maxson=size[v];
			son[now]=v;
		}
	}
}
inline void dfs2(int now,int topf)
{
	id[now]=++cn;
	ww[cn]=a[now];
	top[now]=topf;
	if(!son[now]) return; 
	dfs2(son[now],topf);
	for(int i=head[now];i;i=e[i].next)
	{
		if(e[i].v==fa[now]||e[i].v==son[now]) continue; 
		dfs2(e[i].v,e[i].v);
	} 
}
inline void build(int w,int l,int r)
{
	if(r==l)
	{
		t[w].v=ww[r];
		t[w].v%=p;
		return;
	}
	int mid=(r+l)>>1;
	build(w*2,l,mid);
	build(w*2+1,mid+1,r);
	t[w].v=t[w*2].v+t[w*2+1].v;
	return;
}
inline void addd(int w,int l,int r)
{
	int mid=(r+l)>>1;
	t[w*2].v+=t[w].add*(mid-l+1);
	t[w*2+1].v+=t[w].add*(r-mid);
	t[w*2+1].add+=t[w].add;
	t[w*2].add+=t[w].add;
	t[w].add=0;
}
inline void up(int w,int l,int r,int L,int R,int k)
{
	if(L<=l&&r<=R)
	{
		t[w].v+=k*(r-l+1);
		t[w].v%=p;
		t[w].add+=k;
		return ; 
	}
	if(t[w].add) addd(w,l,r);
	int mid=(l+r)>>1;
	if(mid>=L) up(w*2,l,mid,L,R,k);
	if(mid<R) up(w*2+1,mid+1,r,L,R,k);
	t[w].v=(t[w*2].v+t[w*2+1].v)%p;
}
inline int ask(int w,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	{
		return t[w].v;
	}
	if(t[w].add) addd(w,l,r);
	int ans=0;
	int mid=(l+r)>>1;
	if(mid>=L) ans+=ask(w*2,l,mid,L,R);
	if(mid<R) ans+=ask(w*2+1,mid+1,r,L,R);
	return ans%p; 
}
inline void up1(int x,int y,int k)
{
	k%=p;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		up(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	up(1,1,n,id[x],id[y],k);
}
inline void ask1(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{		
	    if(dep[top[x]]<dep[top[y]]) swap(x,y);
	    int res=ask(1,1,n,id[top[x]],id[x]);
	    ans+=res;
	    ans%=p;
	    x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	int res=ask(1,1,n,id[x],id[y]);
	ans+=res; 
	printf("%d\n",ans%p);
 }
int main()
{
	int u,v;
	scanf("%d%d%d%d",&n,&m,&r,&p);
	for(int i=1;i<=n;i++)
	{
	    scanf("%d",&a[i]);	
	} 
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u); 
	}
	dfs1(r,0,1);
	dfs2(r,r);
	build(1,1,n);
	int b,c,d,e,x,y,z;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&b,&x);
		if(b==1)
		{
			scanf("%d",&y);
			scanf("%d",&z);
			up1(x,y,z);
		}
		else if(b==2)
		{
			scanf("%d",&y);
			ask1(x,y);
		}
		else if(b==3)
		{
			scanf("%d",&y);
			up(1,1,n,id[x],id[x]+size[x]-1,y);
		}
		else
		{
			int ans=ask(1,1,n,id[x],id[x]+size[x]-1);
			ans%=p;
			printf("%d\n",ans);
		}
	} 
}
