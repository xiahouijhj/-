#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int a[maxn],b[maxn],c[maxn],p[maxn],v[maxn],q[maxn];
int t[maxn];
int ans[maxn];
int cnt[maxn];
inline bool cmp(int x,int y)
{
    return a[x]<a[y]||(a[x]==a[y]&&(b[x]<b[y]||(b[x]==b[y]&&c[x]<c[y])));
}
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}
int n,k;
inline int lowbit(int now)
{
    return now&-now;
}
inline void up(int now,int j)
{
    while(now<=k)
    {
        t[now]+=j;
        now+=lowbit(now);
    }
}
inline int ask(int now)
{
    int ans=0;
    while(now)
    {
        ans+=t[now];
        now-=lowbit(now);
    }
    return ans;
}
inline void cdq(int *p,int le)
{
    // cout<<le<<endl;
    if(le==1) return ;
    int i,j,k=0;
    int m=le>>1;
    cdq(p,m);
    cdq(p+m,(le-m));
    memcpy(q,p,le*sizeof(int));//把 p 开头的 le 个 int 复制到 q 里。
    // cout<<le<<endl;
    for(i=0,j=m;i<m&&j<le;k++)
    {
        // cout<<i<<endl;
        int x=q[i];
        int y=q[j];
        if(b[x]<=b[y])
        {
            up(c[p[k]=x],v[x]);
            i++;
        }
        else
        {
            cnt[y]+=ask(c[p[k]=y]);
            j++;
        }
    }
    for(;j<le;j++) cnt[q[j]]+=ask(c[q[j]]);
    memcpy(p+k,q+i,(m-i)*sizeof(int));
    for(i--;~i;i--) up(c[q[i]],-v[q[i]]);
}
int main()
{
    memset(v,0,sizeof(v));
    memset(cnt,0,sizeof(cnt));
    n=read();k=read();
    // memset(t,0,sizeof(t));
    for(int i=0;i<=k;i++) t[i]=0;
    for(int i=0;i<n;i++)
    {
        p[i]=i;
        a[i]=read();b[i]=read();c[i]=read();
    }
    sort(p,p+n,cmp);
    int i,j;
    for(i=0,j=1;j<n;j++)
    {
        int x=p[j],y=p[i];v[y]++;
        if(a[x]^a[y]||b[x]^b[y]||c[x]^c[y]) p[++i]=x;
    }
	//去重
    v[p[i++]]++;
    cdq(p,i);
    for(j=0;j<i;j++)
    {
        // cout<<v[p[j]]<<endl;
        ans[cnt[p[j]]+v[p[j]]-1]+=v[p[j]];
    }
    for(int i=0;i<n;i++)
    {
        cout<<ans[i]<<'\n';
    }
}
