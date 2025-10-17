#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define lson x<<1
#define rson x<<1|1
const int maxn=5e5+10;
struct node
{
    int flag;
}t[maxn*4];
inline node merge(node a,node b)
{
    node x;
    return x;
}
inline void build(int x,int l,int r)
{
    if(l==r)
    {
        t[x].flag=0;
        return ;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    t[x]=merge(t[lson],t[rson]);
}
inline void jia(node &a,int now)
{

}
inline void push_down(int x)
{
    jia(t[lson],t[x].flag);
    jia(t[rson],t[x].flag);
    t[x].flag=0;
}
inline void change(int x,int l,int r,int L,int R,int k)
{
    if(L<=l&&r<=R)
    {
        jia(t[x],k);
        return ;
    }
    int mid=(l+r)>>1;
    if(t[x].flag!=0)
    {
        push_down(x);
    }
    if(L<=mid) change(lson,l,mid,L,R,k);
    if(mid<R) change(rson,mid+1,r,L,R,k);
    t[x]=merge(t[lson],t[rson]);
}
inline node ask(int x,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
    {
        return t[x];
    }
    int mid=(l+r)>>1;
    if(t[x].flag!=0)
    {
        push_down(x);
    }
    node ans;
    if(L<=mid)
    {
        ans=ask(lson,l,mid,L,R);
        if(mid<R) ans=merge(ans,ask(rson,mid+1,r,L,R));
    }
    else if(mid<R) ans=ask(rson,mid+1,r,L,R);
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t=1;
    // cin>>t;
}
