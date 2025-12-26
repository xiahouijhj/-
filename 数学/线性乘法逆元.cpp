inv[1] = 1;
for(int i = 2; i < p; ++ i)
    inv[i] = (p - p / i) * inv[p % i] % p;

// O(n+logP) 离线计算多个逆元
for(int i=1;i<=k;i++) p[i]=c(p[i-1],x[i]);fp[k]=fast(p[k],mod-2);
for(int i=k-1;i>=0;i--)
{
    fp[i]=c(fp[i+1],x[i+1]);
}
for(int i=1;i<=k;i++)
{
    fx[i]=c(fp[i],p[i-1]);
}
