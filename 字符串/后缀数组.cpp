#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define int long long
using namespace std;
const int Maxn=2e5+5;
const int moda=1e9+7;
const int modb=1e8+7;
int n,m,x[Maxn],y[Maxn],c[Maxn],sa[Maxn];
int height[Maxn],rk[Maxn];
int da[Maxn];
void SA(string t)
{
    int n=t.size()-1;
    m=122;
    for(int i=0;i<=m;i++) c[i]=0;
    for(int i=1;i<=n;i++){x[i]=t[i];++c[x[i]];}
    for(int i=2;i<=m;i++)c[i]+=c[i-1];
    for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k=k<<1)
    {	
        int num=0;
        for (int i=n-k+1;i<=n;++i) y[++num]=i;
        for(int i=1;i<=n;i++)
        if(sa[i]>k)y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++)c[i]=0;
        for(int i=1;i<=n;i++)c[x[i]]++;
        for(int i=2;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i>=1;i--){sa[c[x[y[i]]]--]=y[i];y[i]=0;}
        swap(x,y);
        num=1;x[sa[1]]=1;
        for(int i=2;i<=n;i++)
        {	
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])x[sa[i]]=num;
            else x[sa[i]]=++num;
        }
        if(num==n)break;
        m=num;
    }
    for(int i=1;i<=n;i++)
    {
        da[sa[i]]=i;
    }
    // for(int i=1;i<=n;i++)
    // printf("%d",sa[i]);
    // printf("\n");
}
signed main()
{	
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    // for(int i=1;i<=t;i++) solve();
    return 0;
}
