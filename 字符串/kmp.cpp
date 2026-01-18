#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn=1e6+10;
int kmp[maxn];
int nxt[maxn];
signed main()
{
    string a;
    cin>>a;
    string b;
    cin>>b;
    int n=a.size(),m=b.size();
    a=' '+a+'#';
    b=' '+b;
    nxt[1]=0;
    for(int i=2;i<=m;i++)
    {
        int j=nxt[i-1];
        while(j&&b[j+1]!=b[i]) j=nxt[j];
        if(b[j+1]==b[i]) j++;
        nxt[i]=j;
    }
    kmp[0]=0;
    for(int i=1;i<=n;i++)
    {
        int j=kmp[i-1];
        if(j==m) j=nxt[j];
        while(j&&b[j+1]!=a[i]) j=nxt[j];
        if(b[j+1]==a[i]) j++;
        kmp[i]=j;
    }
}
