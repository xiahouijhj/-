#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn=3030;
const int inf=1e18+10;
int a[maxn];
int dp[maxn][maxn/10];
int n,m;
int qu[maxn];
int w[maxn][maxn];
inline int bin_search(int a,int b,int now)
{
    int l=max(a,b),r=n+1;
    while(l<r)
    {
        int mid=(l+r+1)>>1;
        if(w[a][mid]+dp[a][now]<w[b][mid]+dp[b][now])
        {
            l=mid;
        }
        else
        {
            r=mid-1;
        }
    }
    return l;
}
int sum[maxn];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int ans=inf;
    for(int i=1;i<=m;i++)
    {
        int head=1;
        int tail=2;
        qu[1]=0;
        for(int j=1;j<=n;j++)
        {
            while(head+1<tail&&bin_search(qu[head],qu[head+1],i-1)<j)
            {
                head++;
            }
            dp[j][i]=min(dp[qu[head]][i-1]+w[qu[head]][j],dp[j][i]);
            ans=min(dp[j][i],ans);
            while(bin_search(qu[tail-1],j,i-1)<=bin_search(qu[max(head,tail-2)],qu[tail-1],i-1)&&head<tail) tail--;
            qu[tail]=j;
            tail++;
        }
    }
    cout<<ans<<endl;
}
