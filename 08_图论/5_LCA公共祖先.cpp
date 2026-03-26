// LCA（最近公共祖先）算法模板 - 倍增法
// 适用场景：在树结构中快速查询任意两点的最近公共祖先
// 算法特点：预处理时间复杂度 O(N log N)，单次查询时间复杂度 O(log N)
// 算法原理：通过倍增预处理每个节点的2^i级祖先，查询时先调整深度再同时上跳
// 参考题目：P3379 【模板】最近公共祖先（LCA） — https://www.luogu.com.cn/problem/P3379

#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;


const int N = 500005;
const int Limit = 21;

int n,m,root;
int count_e,head[N];
struct Edge
{
	int to;
	int nxt;
}edges[N * 2];

//LCA需要的数组，up[u][i]表示u的第2^i个祖先，depth[u]表示u的深度
//如果还需要其他的信息，可以在这个结构体中添加
int up[N][Limit],depth[N];

void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
	return ;
}

void dfs(int u,int fa)
{
    //初始化u的深度和父亲
	depth[u] = depth[fa] + 1;
	up[u][0] = fa;
	
    //预处理u的第2^i个祖先
	for(int i = 1; i < Limit; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
	//遍历u的所有邻边，继续dfs
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		dfs(v,u);
	}
	
	return ;
}

//求u和v的LCA
int getLCA(int u,int v)
{
	if(depth[u] < depth[v]) swap(u,v);
	
    //先将u提升到和v同一深度
	for(int i = Limit - 1; i >= 0; --i)
	{
		if(depth[up[u][i]] >= depth[v])
		{
			u = up[u][i];
		}
	}
	
	if(u == v) return u;
	
    //再同时提升u和v，直到它们的父亲相同
	for(int i = Limit - 1; i >= 0; --i)
	{
		if(up[u][i] != up[v][i])
		{
			u = up[u][i];
			v = up[v][i];
		}
	}
	
    //最后返回它们的父亲
	return up[u][0];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(head,-1,sizeof(head));
	cin >> n >> m >> root;
	
	int u,v;
	for(int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		if(u == v) continue;
		addEdge(u,v);
		addEdge(v,u);
	}
	
	dfs(root,0);
	
	for(int i = 1; i <= m; ++i)
	{
		cin >> u >> v;
		cout << getLCA(u,v) << '\n';
	}
	
	
	return 0;
}