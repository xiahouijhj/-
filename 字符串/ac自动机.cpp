#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn=1e6+10;
int cnt=0;
struct node
{
    int end;
    int fail;
    int vis[27];
}e[maxn];
inline void add(string s)
{
    int now=0;
    for(int i=0;i<s.size();i++)
    {
        if(e[now].vis[s[i]-'a']==0) e[now].vis[s[i]-'a']=++cnt;
        now=e[now].vis[s[i]-'a'];
    }
    e[now].end++;
}
inline void build()
{
    queue<int> q;
    for(int i=0;i<26;i++)
    {
        if(e[0].vis[i]!=0) q.push(e[0].vis[i]),e[e[0].vis[i]].fail=0;
    }
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(int i=0;i<26;i++)
        {
            if(e[now].vis[i]==0)
            {
                e[now].vis[i]=e[e[now].fail].vis[i];
            }
            else
            {
                e[e[now].vis[i]].fail=e[e[now].fail].vis[i];
                q.push(e[now].vis[i]);
            }
        }
    }
}
inline int ask(string s)
{
    int now=0;
    int ans=0;
    for(int i=0;i<s.size();i++)
    {
        now=e[now].vis[s[i]-'a'];
        for(int t=now;e[t].end!=-1;t=e[t].fail)
        {
            ans+=e[t].end;
            e[t].end=-1;
        }
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    memset(e,0,sizeof(e));
    for(int i=1;i<=n;i++)
    {
        string s;
        cin>>s;
        add(s);
    }
    e[0].fail=0;
    e[0].end=-1;
    build();
    string ss;
    cin>>ss;
    cout<<ask(ss)<<endl;
}
