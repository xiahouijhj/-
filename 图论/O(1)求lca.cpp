#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int mod=998244353;
const int maxn=1e6+10;
const int N=1e6+10;
int n,m,rt;
int dep[N],lg[N<<1],f[N<<1][21];
int dfn[N<<1],que[N<<1],idx;
vector<int> u[maxn];
inline int fa(int x,int k)
{
    int ans=1;
    while(k)
    {
        if(k&1) ans=ans*x%mod;
        x=x*x%mod;
        k=k>>1;
    }
    return ans;
}
void buildst()
{
    for(int i=1;i<=idx;i++) f[i][0]=que[i];
	for(int j=1;j<=20;j++)
    {
		for(int i=1;i+(1<<j)<=idx;++i){
			int f1=f[i][j-1],f2=f[i+(1<<(j-1))][j-1];
			f[i][j]=dep[f1]<dep[f2]?f1:f2;
		}
    }
	lg[0]=-1;
	for(int i=1;i<=idx;i++) lg[i]=lg[i>>1]+1;
}
inline int getlca(int u,int v)
{
	if(dfn[u]>dfn[v])swap(u,v);
	u=dfn[u],v=dfn[v];
	int kk=lg[v-u+1],f1=f[u][kk],f2=f[v-(1<<kk)+1][kk];
	return dep[f1]<dep[f2]?f1:f2;
}
void dfs(int x,int pa)
{
	dfn[x]=++idx,que[idx]=x;
	dep[x]=dep[pa]+1;
	for(int v:u[x]){
		if(v==pa)continue;
		dfs(v,x);
		que[++idx]=x;
	}
}
signed main()
{

}
