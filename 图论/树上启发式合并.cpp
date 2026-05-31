#include<bits/stdc++.h>
using namespace std;
int n,num_edge,ans,mi,ma;
struct Edge{
	int to,next;
}e[400010];
int head[200010];
int a[200010];
int siz[200010];
int son[200010];
int t[2][200010];
void add_edge(int from,int to){
	e[++num_edge].to=to;
	e[num_edge].next=head[from];
	head[from]=num_edge;
}
void add(int x){
	t[1][t[0][x]]--;
	t[0][x]++;
	t[1][t[0][x]]++;
	if(t[0][x]<mi) mi=t[0][x];
	if(t[0][x]>ma) ma=t[0][x];
	if(!t[1][mi]) mi++;
}
void del(int x){
	t[1][t[0][x]]--;
	t[0][x]--;
	t[1][t[0][x]]++;
	if(t[0][x]&&t[0][x]<mi) mi=t[0][x];
	if(!t[1][ma]) ma--;
}
void dfs0(int u){
	int v;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].next){
		v=e[i].to;
		dfs0(v);
		if(siz[v]>siz[son[u]]) son[u]=v;
		siz[u]+=siz[v];
	}
}
void dfs1(int u,int ty){
	int v;
	if(!ty) del(a[u]);
	else add(a[u]);
	for(int i=head[u];i;i=e[i].next){
		v=e[i].to;
		dfs1(v,ty);
	}
}
void dfs2(int u){
	int v;
	for(int i=head[u];i;i=e[i].next){
		v=e[i].to;
		if(v==son[u]) continue;
		dfs2(v);
		dfs1(v,0);
	}
	if(son[u]) dfs2(son[u]);
	for(int i=head[u];i;i=e[i].next){
		v=e[i].to;
		if(v==son[u]) continue;
		dfs1(v,1);
	}
	add(a[u]);
	if(mi==ma) ans++;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>a[i]>>x;
		add_edge(x,i);
	}
	dfs0(1);
	mi=1;
	dfs2(1);
	cout<<ans;
	return 0;
}
