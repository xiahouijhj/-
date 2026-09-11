#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e7+10;

int z[N];//代表长度
int ext[N];//代表长度
void get_z(string s)
{
    int n=s.size();
    z[0]=0;
    int l=0,r=0;
    for(int i=1;i<n;i++)
    {
        if(i<=r)
        {
            z[i]=min(r-i+1,z[i-l]);
        }
        else
        {
            z[i]=0;
        }
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])
        {
            z[i]++;
        }
        if(i+z[i]-1>r)
        {
            l=i;
            r=i+z[i]-1;
        }
    }
}
void exkmp(string a,string b)
{
	int la = a.size(), lb = b.size();
	int p = 0, k = 0, l;
	while(p < la && p < lb && a[p] == b[p]) p++; //先算出初值用于递推
	ext[0] = p;
	for(int i = 1; i < la; i++) //下面都是一样的逻辑啦
	{
		p = k + ext[k] - 1;
		l = z[i - k];
		if(i + l <= p) ext[i] = l;
		else
		{
			int j = max((int)0, p - i + 1);
			while(i + j < la && j < lb && a[i + j] == b[j]) j++;
			ext[i] = j;
			k = i;
		}
	}
}
signed main()
{
}
