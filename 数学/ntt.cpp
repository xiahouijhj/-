#include <bits/stdc++.h>
using namespace std;
const int MAXN=3*1e6+10;
const int mod=998244353,G=3,Gi=332748118;//绝大多数情况下如此
int n,m,limit=1,L,r[MAXN];
long long a[MAXN],b[MAXN];
long long fastpow(long long a, long long k)
{
    long long res=1ll;
    while(k)
    {
        if(k&1)
        {
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        k>>=1ll;
    }
    return res%mod;
}
void NTT(long long *A,int type)//NTT板子
{
    for(int i=0;i<limit;i++)
    {
        if(i<r[i])
        {
            swap(A[i],A[r[i]]);
        }
    }
    for(int mid=1;mid<limit;mid<<=1)
    {
        long long Wn=fastpow(type==1?G:Gi,(mod-1)/(mid<<1));
        for(int j=0;j<limit;j+=(mid<<1))
        {
            long long w = 1;
            for(int k = 0; k < mid; k++, w = (w * Wn) % mod)
            {
                 int x=A[j+k];
                 int y=w*A[j+k+mid]%mod;
                 A[j+k]=(x+y)%mod,
                 A[j+k+mid]=(x-y+mod)%mod;
            }
        }
    }
    if(type==-1)
    {
        long long inv =fastpow(limit,mod-2);
        for(int i=0;i<=n+m;i++)
        {
           A[i]=(A[i]*inv)%mod;
        }
    }
}
void poly_mul(long long *a,long long *b,int deg)//多项式乘法
{
    while(limit<=deg)
    {
        limit<<=1;
        L++;
    }
    for(int i=0;i<limit;i++)
    {
        r[i]=(r[i>>1]>>1)|((i&1)<<(L-1));
    }
    NTT(a,1);
    NTT(b,1);
    for(int i=0;i<limit;i++)
    {
        a[i]=(a[i]*b[i])%mod;
    }
    NTT(a, -1);
}
int main()
{
    cin>>n>>m;
    for(int i = 0; i <= n; i++)
    {
        cin>>a[i];
        a[i]=(a[i]+mod)%mod;
    }
    for(int i = 0; i <= m; i++)
    {
        cin>>b[i];
        b[i]=(b[i]+mod)%mod;
    }
    poly_mul(a,b,n+m);
    for(int i=0;i<=n+m;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}

