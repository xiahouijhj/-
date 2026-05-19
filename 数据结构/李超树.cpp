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
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    memset(t,0,sizeof(t));
    memset(k,0,sizeof(k));
    memset(b,0,sizeof(b));
    int n;
    cin>>n;
    int lastans=0;
    int d=0;
    for(int i=1;i<=n;i++)
    {
        int op;
        cin>>op;
        if(op==0)
        {
            int k;
            cin>>k;
            lastans=query(d,1,mod1,(k+lastans-1)%mod1+1);
            cout<<lastans<<endl;
        }
        else
        {
            int x0,y0,x1,y1;
            cin>>x0>>y0>>x1>>y1;
            x0=(x0+lastans-1)%mod1+1;
            x1=(x1+lastans-1)%mod1+1;
            y0=(y0+lastans-1)%mod2+1;
            y1=(y1+lastans-1)%mod2+1;
            if(x0>x1)
            {
                swap(x0,x1);
                swap(y0,y1);
            }
            if(x0!=x1) k[cn]=1.0*(y1-y0)/(x1-x0);
            else k[cn]=0,y0=max(y0,y1);
            b[cn]=y0*1.0-x0*k[cn];
            insert(d,1,mod1,min(x0,x1),max(x1,x0),cn);
            cn++;
        }
    }
    // cout<<cmp(1,2,2)<<endl;
    return 0;
}
