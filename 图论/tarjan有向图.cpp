inline void tarjan(int x)
{
    low[x]=dfn[x]=++t;
    sta[++hh]=x;vis[x]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(vis[v])
        {
            low[x]=min(low[x],low[v]);
        }
    }
    if(dfn[x]==low[x])
    {
        int y;
        while(y=sta[hh--])
        {
            sd[y]=x;
            vis[y]=0;
            if(x==y) break;
        }
    }
}
