void get_mu(long long n)
{
    mu[1]=1;
    for(long long i=2;i<=n;i++)
    {
        if(!vis[i]){mu[i]=-1;prim[++cnt]=i;}
        for(long long j=1;j<=cnt&&i*prim[j]<=n;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]==0)break;
            else mu[i*prim[j]]=-mu[i];
        }
    }
    for(long long i=1;i<=n;i++)sum[i]=sum[i-1]+mu[i];
}
