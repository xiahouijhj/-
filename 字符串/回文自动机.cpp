#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
string s;
int n;
int cnt=2;
struct Node
{
	int sum;
	int len;
	Node* vis[26];
	Node* fail;
}e[maxn];
Node* last;
inline void init()
{
	e[0].fail=&e[1];e[1].fail=&e[0];
	for(int i=0;i<26;i++) e[0].vis[i]=e[1].vis[i]=&e[0];
	e[0].len=0,e[1].len=-1;
	e[0].sum=e[1].sum=0;
	last=&e[0];
}
inline Node* New(int len)
{
	e[cnt].len=len;
	e[cnt].fail=&e[0];
	for(int i=0;i<26;i++) e[cnt].vis[i]=&e[0];
	return &e[cnt++];
}
inline Node* find(Node *now,int pos)
{
	while(s[pos]!=s[pos-now->len-1]) now=now->fail;
	return now;
}
inline void insert(int pos)
{
	Node* cur=find(last,pos);
	// cout<<pos<<' '<<s[pos]<<endl;

	if(cur->vis[s[pos]-'a']==&e[0])
	{
		Node* now=New(cur->len+2);
		Node* xia=find(cur->fail,pos);
		now->fail=xia->vis[s[pos]-'a'];
		now->sum=(xia->vis[s[pos]-'a']->sum)+1;
		cur->vis[s[pos]-'a']=now;
	}
	last=cur->vis[s[pos]-'a'];
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
		s[i]=(s[i]-97+k)%26+97;
		insert(i);
		k=last->sum;
		cout<<last->sum<<' ';
	}
}
