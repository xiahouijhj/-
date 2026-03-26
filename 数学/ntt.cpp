#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
const int MAXN=3*1e6+10;
int n,m,limit=1,L,r[MAXN];
const long long N=1010101;
const long long inf=0x3f3f3f3f;
const long long p=998244353, g=3, gi=332748118;
// mod = 998244353、1004535809、469762049
// Gi = 332748118, 334845270, 156587350
ll Len;

inline ll read() {
	ll sum = 0, ff = 1; char c = getchar();
	while(c<'0' || c>'9') { if(c=='-') ff = -1; c = getchar(); }
	while(c>='0'&&c<='9') { sum = sum * 10 + c - '0'; c = getchar(); }
	return sum * ff;
}

inline ll ksm(ll aa,ll bb) {
	ll sum = 1;
	while(bb) {
		if(bb&1) sum = sum * aa %p;
		bb >>= 1; aa = aa * aa %p;
	}
	return sum;
}

inline ll init(ll wo) {
	ll len = 1, L = 0; while(len<wo) len<<=1, L++;
	for(ll i=0;i<len;i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(L-1));
	return len;
}

void NTT(ll *A,ll len,ll cl) {
	for(ll i=0;i<len;i++) if(i<r[i]) swap(A[i],A[r[i]]);
	for(ll k=1;k<len;k<<=1) {
		ll g1 = ksm((cl==1)?g:gi, (p-1)/(k<<1));
		for(ll j=0;j<len;j+=(k<<1)) {
			ll gk = 1;
			for(ll i=0;i<k;i++,gk=gk*g1%p) {
				ll x = A[i+j], y = gk*A[i+j+k] %p;
				A[i+j] = (x+y) %p; A[i+j+k] = (x-y+p) %p;
			}
		}
	}
	if(cl==1) return ;
	ll inv = ksm(len,p-2);
	for(ll i=0;i<len;i++) A[i] = A[i] * inv %p;
}

void PMUL(ll *F,ll *G,ll len) {
	NTT(F, len, 1);
	NTT(G, len, 1);
	for(ll i=0;i<len;i++) F[i] = F[i] * G[i] %p;
	NTT(F, len, -1);
}

