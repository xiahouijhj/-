//求 (a+b)×k
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define lowbit(x) ((x)&(-(x)))
#define mid ((l+r)>>1)
#define lson rt<<1, l, mid
#define rson rt<<1|1, mid+1, r
#define fors(i, a, b) for(int i = (a); i < (b); ++i)
#define all(vec) vec.begin(),vec.end()
using namespace std;
const int maxn = 3e5 + 5;
const int mod = 1e9 + 7;
int k[maxn];
int a[maxn];
int ch[maxn][2];
int n;
int kl[maxn][20], bl[maxn][20];
int kr[maxn][20], br[maxn][20];
int fl[maxn][20], fr[maxn][20];
int f[maxn][20], dep[maxn];
int val[maxn];
void calc(int u, int pa){
    f[u][0] = pa; dep[u] = dep[pa]+1; fors(i,1,20) f[u][i] = f[f[u][i-1]][i-1];
    int res = 0;
    if(ch[u][0]) calc(ch[u][0], u), res = (res+val[ch[u][0]])%mod;
    else res = (res + a[u-1])%mod;
    if(ch[u][1]) calc(ch[u][1], u), res = (res+val[ch[u][1]])%mod;
    else res = (res + a[u])%mod;
    res = (ll)k[u]*res%mod;
    val[u] = res;
    return;
}
void update(int &k1, int &b1, int k2, int b2){
    int tk = (ll)k1*k2%mod;
    int tb = ((ll)k2*b1%mod + b2)%mod;
    k1 = tk; b1 = tb; return;
}
void dfs(int u, int Fl, int Fr){
    fl[u][0] = Fl; fr[u][0] = Fr;
    //l to lca
    //从末结点出发，终点结点不计算
    if(ch[u][0]) br[u][0] = (ll)k[u]*val[ch[u][0]]%mod; else br[u][0] = (ll)k[u]*a[u-1]%mod;
    if(ch[u][1]) bl[u][0] = (ll)k[u]*val[ch[u][1]]%mod; else bl[u][0] = (ll)k[u]*a[u]%mod;
    kl[u][0] = kr[u][0] = k[u];
    fors(i,1,20){
        fl[u][i] = fl[fl[u][i-1]][i-1];//向右父亲
        fr[u][i] = fr[fr[u][i-1]][i-1];//向左父亲

        kl[u][i] = (ll)kl[u][i-1]*kl[fr[u][i-1]][i-1]%mod;//左边点计算
        bl[u][i] = ((ll)bl[u][i-1]*kl[fr[u][i-1]][i-1]%mod + bl[fr[u][i-1]][i-1])%mod;

        kr[u][i] = (ll)kr[u][i-1]*kr[fl[u][i-1]][i-1]%mod;
        br[u][i] = ((ll)br[u][i-1]*kr[fl[u][i-1]][i-1]%mod + br[fl[u][i-1]][i-1])%mod;
    }
    if(ch[u][0]) dfs(ch[u][0], Fl, u);
    if(ch[u][1]) dfs(ch[u][1], u, Fr);
    return;
}
int lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    int d = dep[u]-dep[v];
    fors(i,0,20) if(d>>i&1) u = f[u][i];
    if(u == v) return u;
    for(int i = 19; i >= 0; --i) if(f[u][i]^f[v][i]) tie(u,v) = tie(f[u][i],f[v][i]);
    return f[u][0];
}

int sol(int u, int v){
    int l = u, r = v;
    int k1 = 1, b1 = 0, k2 = 1, b2 = 0;
    int p = lca(u, v);
    for(int i = 19; i >= 0; --i){
        if(dep[fr[u][i]] >= dep[p]) {
            update(k1, b1, kl[u][i], bl[u][i]);
            u = fr[u][i];
        }
    }
    for(int i = 19; i >= 0; --i){
        if(dep[fl[v][i]] >= dep[p]){
            update(k2, b2, kr[v][i], br[v][i]);
            v = fl[v][i];
        }
    }
    int x = ((ll)k1*a[l-1]%mod + b1)%mod;
    int y = ((ll)k2*a[r]%mod + b2)%mod;
    int ans = (x+y)*(ll)k[p]%mod;
    ans = (ans + mod)%mod;
    return ans;
}
int main()
{
    scanf("%d", &n); n--;
    fors(i,0,n+1) scanf("%d", &a[i]);
    fors(i,1,n+1) scanf("%d", &k[i]);
    stack<int> st; st.push(0);
    fors(i,1,n+1){
        while(k[st.top()] >= k[i]) ch[i][0] = st.top(), st.pop();//小根堆
        ch[st.top()][1] = i; st.push(i);
    }
    calc(0, 0);
    dfs(0, 0, 0);
    int q; scanf("%d", &q);
    while(q--){
        int l, r; scanf("%d%d", &l, &r);
        if(l == r){
            printf("%d\n", a[l-1]); continue;
        }
        printf("%d\n", sol(l,r-1));
    }
	return 0;
}
