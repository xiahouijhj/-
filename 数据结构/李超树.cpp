#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn=1e6+10;
const double eps=1e-10;
const int mod1=39989;
const int mod2=1e9;
int cnt=1;
int cn=1;
double k[maxn],b[maxn];
struct node
{
    int l,r,id;
}t[maxn];
inline double calc(int id,int x)
{
    return k[id]*x+b[id];
}
inline bool cmp(int a,int b,int x)
{
    if(calc(a,x)-calc(b,x)>eps) return true;
    if(calc(b,x)-calc(a,x)>eps) return false;
    return a<b;
}
inline int query(int now,int l,int r,int x)
{
    if(now==0) return 0;
    int ans=t[now].id;
    if(l==r) return ans;
    int f=0;
    int mid=(l+r)>>1;
    if(x<=mid) f=query(t[now].l,l,mid,x);
    else f=query(t[now].r,mid+1,r,x);
    if(cmp(f,ans,x)) ans=f;
    // cout<<l<<' '<<r<<' '<<ans<<' '<<x<<endl;
    return ans;
}
inline void insert(int &now,int l,int r,int L,int R,int id)
{
    // cout<<l<<' '<<r<<' '<<t[now].id<<' '<<L<<' '<<R<<endl;
    if(r<L||l>R) return ;
    if(now==0) now=cnt++;
    int &nid=t[now].id;
    int mid=(l+r)>>1;
    if(L<=l&&r<=R)
    {
        if(cmp(id,nid,l)&&cmp(id,nid,r))
        {
            // cout<<1<<endl;
            t[now].id=id;
            return ;
        }
        if(cmp(nid,id,l)&&cmp(nid,id,r))
        {
            // cout<<2<<endl;
            return ;
        }
        if(cmp(id,nid,mid)) swap(id,t[now].id);
        if(cmp(id,nid,l)) insert(t[now].l,l,mid,L,R,id);
        if(cmp(id,nid,r)) insert(t[now].r,mid+1,r,L,R,id);
    }
    else
    {
        insert(t[now].l,l,mid,L,R,id);
        insert(t[now].r,mid+1,r,L,R,id);
    }
}
