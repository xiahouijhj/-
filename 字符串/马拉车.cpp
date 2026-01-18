#include <bits/stdc++.h>
using namespace std;
const int N=2e7+10;
char a[N],s[N];
int nxt[N];
int main()
{
	memset(nxt,0,sizeof(nxt));
	scanf("%s",a);
	int len=strlen(a);
	//cout<<len; 
	for(int i=0;i<len;i++)
	{
		s[i*2]='#';
		s[i*2+1]=a[i];
	}
	s[len*2]='#';
	int r=0,mid=0,num=0;
	for(int i=0;i<len*2-1;i++)
	{
		if(r>i)
		{
			nxt[i]=min(r-i,nxt[mid*2-i]);
		}
		else
		{
			nxt[i]=1;
		}
		while(s[i-nxt[i]]==s[i+nxt[i]]&&i-nxt[i]>=0)
		{
			nxt[i]++;
		}
		if(r<nxt[i]+i)
		{
			mid=i;
			r=nxt[i]+i;
		}
		//cout<<nxt[i]<<" ";
		num=max(nxt[i],num);
	}
	cout<<num-1;
	return 0;
}
