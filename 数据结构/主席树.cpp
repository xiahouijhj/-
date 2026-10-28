
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=2e5+7;

struct node
{
    int l,r,sum;
}tr[N*22];

int a[N],b[N],root[N];
int tot,n,m;

int update(int pre,int l,int r,int pos)
{
    int p=++tot;
    tr[p]=tr[pre];
    tr[p].sum++;
    if(l==r) return p;
    int mid=(l+r)>>1;
    if(pos<=mid)
        tr[p].l=update(tr[pre].l,l,mid,pos);
    else
        tr[p].r=update(tr[pre].r,mid+1,r,pos);
    return p;
}

int query(int u,int v,int l,int r,int k)
{
    if(l==r) return l;
    int mid=(l+r)>>1;
    int cnt=tr[tr[v].l].sum-tr[tr[u].l].sum;
    if(k<=cnt)
        return query(tr[u].l,tr[v].l,l,mid,k);
    else
        return query(tr[u].r,tr[v].r,mid+1,r,k-cnt);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        b[i]=a[i];
    }

    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;

    for(int i=1;i<=n;i++)
    {
        int x=lower_bound(b+1,b+m+1,a[i])-b;
        root[i]=update(root[i-1],1,m,x);
    }

    while(q--)
    {
        int l,r,k;
        cin>>l>>r>>k;
        int x=query(root[l-1],root[r],1,m,k);
        cout<<b[x]<<'\n';
    }
    return 0;
}
