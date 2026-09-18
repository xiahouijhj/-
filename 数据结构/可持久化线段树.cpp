#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
struct tree
{
	int val,r,l;
}t[maxn*30];
int top=0;
int a[maxn],n,m;
int rt[maxn];
inline int build(int l,int r)
{
	top++;
	int node=top;
	if(l==r)
	{
		t[node].val=a[l];
		return node;
	}
	int mid=(l+r)>>1;
	t[node].l=build(l,mid);
	t[node].r=build(mid+1,r);
	return node;
}
inline int change(int node,int l,int r,int x,int v)
{
	top++;
	t[top]=t[node];
	node=top;
	if(l==r)
	{
		t[node].val=v;
		return node;
	}
	int mid=(l+r)>>1;
	if(x<=mid) t[node].l=change(t[node].l,l,mid,x,v);
	else t[node].r=change(t[node].r,mid+1,r,x,v);
	return node;
}
inline int ask(int node,int l,int r,int x)
{
	int ans;
	if(l==r)
	{
		return node;
	}
	int mid=(l+r)>>1;
	if(x<=mid) ans=ask(t[node].l,l,mid,x);
	else ans=ask(t[node].r,mid+1,r,x);
	return ans;
}
int main()
{
	int v,pan,ans,loc,value;
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	rt[0]=build(1,n);
	for(int i=1;i<=m;i++)
	{
		v=read();
		pan=read();
		loc=read();
		if(pan==1)
		{
			value=read();
			rt[i]=change(rt[v],1,n,loc,value);
		}
		else
		{
			ans=ask(rt[v],1,n,loc);
			cout<<t[ans].val<<endl;
			rt[i]=rt[v];
		}
	}
}
