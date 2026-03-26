// 树上点差分算法模板
// 适用场景：处理树上路径的批量修改和查询问题
// 算法特点：结合LCA实现，单次修改 O(1)，最终统计 O(N)
// 差分原理：对路径(u,v)上的所有点+1，等价于 d[u]++, d[v]++, d[lca]--, d[parent[lca]]--
// 参考题目：P3128 [USACO15DEC] Max Flow P — https://www.luogu.com.cn/problem/P3128

#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int N = 5e4 + 5;
const int Limit = 16;

int n,m;
int count_e,head[N];
struct Edge
{
	int to;
	int nxt;
}edges[N * 2];

int up[N][Limit],depth[N],d[N];

void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
	return ;
}

void dfs(int u,int fa)
{
	depth[u] = depth[fa] + 1;
	up[u][0] = fa;
	
	for(int i = 1; i < Limit; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		dfs(v,u);
	}
	
	return ;
}


int getLCA(int u,int v)
{
	if(depth[u] < depth[v]) swap(u,v);
	
	for(int i = Limit - 1; i >= 0; --i)
	{
		if(depth[up[u][i]] >= depth[v])
		{
			u = up[u][i];
		}
	}
	if(u == v) return u;
	
	for(int i = Limit - 1; i >= 0; --i)
	{
		if(up[u][i] != up[v][i])
		{
			u = up[u][i];
			v = up[v][i];
		}
	}
	
	return up[u][0];
}

int ans;

int dfs1(int u,int fa)
{
	int sum = 0;
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		sum += dfs1(v,u);
	} 
	
	ans = max(ans,sum + d[u]);
	
	return sum + d[u];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	cout << log2(N) << endl;
	memset(head,-1,sizeof head);
	cin >> n >> m;
	int u,v;
	for(int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		addEdge(u,v);
		addEdge(v,u);
	}
	
	dfs(1,0);
	
	int lca;
	for(int i = 1; i <= m; ++i)
	{
		cin >> u >> v;
		lca = getLCA(u,v);
		++d[u];
		++d[v];
		--d[lca];
		--d[up[lca][0]];
	}
	
	dfs1(1,0);
	
	cout << ans << endl;
	
	return 0;
}