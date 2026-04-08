void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++t;
	int child=0;
	for(int i=head[u];i!=0;i=e[i].next)
	{
		int a=e[i].to;
        //if(a==fa) continue;
		if(!dfn[a])
		{
			tarjan(a,fa);
			low[u]=min(low[u],low[a]);
			if(low[a]>=dfn[u]&&u!=fa) cut[u]=1;
			if(u==fa) child++;
		}
		low[u]=min(low[u],dfn[a]);
	}
	if(child>=2&&u==fa)
	{
		cut[u]=1;
	}
}
