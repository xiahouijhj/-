inline int add(int a,int b)
{
    return ((a%mod)+(b%mod));
}
inline int c(int a,int b)
{
    return ((a%mod)*(b%mod))%mod;
}
inline int jian(int a,int b)
{
    return (((a%mod)-(b%mod))%mod+mod)%mod;
}
inline int fast(int x,int k)
{
    int ans=1;
    while(k)
    {
        if(k&1) ans=c(ans,x);
        x=c(x,x);
        k=k>>1;
    }
    return ans;
}
