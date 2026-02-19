#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
string s;
int n;
int cnt=2;
struct Node
{
	int sum;//以i结尾的回文字符串的个数
	int len;
	int vis[26];
	int fail;
}e[maxn];
int last;
inline void init()
{
	e[0].fail=1;e[1].fail=0;
	for(int i=0;i<26;i++) e[0].vis[i]=e[1].vis[i]=0;
	e[0].len=0,e[1].len=-1;
	e[0].sum=e[1].sum=0;
	last=0;
}
inline int New(int len)
{
	e[cnt].len=len;
	e[cnt].fail=0;
	for(int i=0;i<26;i++) e[cnt].vis[i]=0;
	return cnt++;
}
inline int find(int now,int pos)
{
	while(s[pos]!=s[pos-e[now].len-1]) now=e[now].fail;
	return now;
}
inline void insert(int pos)
{
	int cur=find(last,pos);
	// cout<<pos<<' '<<s[pos]<<endl;

	if(e[cur].vis[s[pos]-'a']==0)
	{
		int now=New(e[cur].len+2);
	    int xia=find(e[cur].fail,pos);
		e[now].fail=e[xia].vis[s[pos]-'a'];
		e[now].sum=(e[e[xia].vis[s[pos]-'a']].sum)+1;
		e[cur].vis[s[pos]-'a']=now;
	}
	last=e[cur].vis[s[pos]-'a'];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>s;
	int n=s.size();
	int k=0;
	s=' '+s;
	init();
	for(int i=1;i<=n;i++)
	{
		insert(i);
	}
}
