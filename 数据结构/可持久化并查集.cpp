#include <cstdio>
#include <cstdlib>
using namespace std;
int n,m,ti;

struct TREE{
	int T[200005],st[200005];//T[i]表示第i次操作后的根,st[i]表示i地方初始值
	int ls[200005 << 5],rs[200005 << 5],val[200005 << 5];//ls[i]是i节点左儿子,rs[i]是i节点右儿子
	int cnt;
	int build(int l,int r){//返回节点编号
		int rt = ++cnt;
		if(l == r){
			val[rt] = st[l];
			return rt;
		}
		int mid = l + r >> 1;
		ls[rt] = build(l,mid);
		rs[rt] = build(mid+1,r);
		return rt;
	}
	int upload(int pt,int l,int r,int id,int C){//pt是原版本这个节点的位置，这个操作是单点赋值
		int rt = ++cnt;
		ls[rt] = ls[pt];
		rs[rt] = rs[pt];
		
		if(l == r){
			val[rt] = C;
			return rt;
		}
		int mid = l + r >> 1;
		if(id <= mid){
			ls[rt] = upload(ls[pt],l,mid,id,C);
		}else{
			rs[rt] = upload(rs[pt],mid+1,r,id,C);
		}
		return rt;
	}
	int query(int rt,int l,int r,int id){//单点查询
		if(l == r){
			return val[rt];
		}
		int mid = l + r >> 1;
		if(id <= mid){
			return query(ls[rt],l,mid,id);
		}else{
			return query(rs[rt],mid+1,r,id);
		}
	}
}bin,siz;//bin存每个点的father,siz存每个点的size大小

int find(int x){
	while(bin.query(bin.T[ti],1,n,x) != x){//这里就是一直往上跳
		x = bin.query(bin.T[ti],1,n,x);
	}
	return x;
}

void merge(int x,int y){
	int a = find(x);
	int b = find(y);
	if(a == b) return;//自己给自己合并会导致size不正确，特判掉
	int X = siz.query(siz.T[ti],1,n,a),Y = siz.query(siz.T[ti],1,n,b);
	if(X <= Y){//如果a的size比b小，就接到b上
		bin.T[ti] = bin.upload(bin.T[ti],1,n,a,b);//bin[a] = b
		siz.T[ti] = siz.upload(siz.T[ti],1,n,b,X + Y);//注意相加size
	}else{
		bin.T[ti] = bin.upload(bin.T[ti],1,n,b,a);
		siz.T[ti] = siz.upload(siz.T[ti],1,n,a,X + Y);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		bin.st[i] = i;//一开始，所有点father是自己
	}
	bin.T[0] = bin.build(1,n);
	for(int i = 1;i <= n;i++){
		siz.st[i] = 1;//所有点size为1
	}
	siz.T[0] = siz.build(1,n);
	
	int opt,x,y;
	for(ti = 1;ti <= m;ti++){
		scanf("%d",&opt);
		bin.T[ti] = bin.T[ti - 1];
		siz.T[ti] = siz.T[ti - 1];//先重置一下，否则可能出锅
		if(opt == 1){
			scanf("%d%d",&x,&y);
			merge(x,y);
		}else if(opt == 2){
			scanf("%d",&x);
			bin.T[ti] = bin.T[x];
			siz.T[ti] = siz.T[x];
		}else{
			scanf("%d%d",&x,&y);
			if(find(x) == find(y)) printf("1\n");
			else printf("0\n");
		}
	}
	return 0;
}
