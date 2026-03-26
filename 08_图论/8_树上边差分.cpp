// 树上边差分算法模板
// 适用场景：处理树上路径的边权批量修改和查询问题
// 算法特点：将边权转化为点权（子节点代表父边），结合LCA实现
// 差分原理：对路径(u,v)上的所有边+1，等价于 d[u]++, d[v]++, d[lca] -= 2
// 参考题目：P10931 闇の連鎖 — https://www.luogu.com.cn/problem/P10931

#include<iostream>
#include<cstring>

using namespace std;

const int N = 100005;
const int Limit = 18;

int n,m,count_e,head[N];
struct Edge
{
	int to;
	int nxt;
}edges[N * 2];

int up[N][18],depth[N],d[N];

void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
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

void build(int u,int fa)
{
	depth[u] = depth[fa] + 1;
	up[u][0] = fa;
	
	for(int i = 1; i < Limit; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		build(v,u);
	}
	
	return ;
}

long long ans;
int dfs(int u,int fa)
{
	int sum = d[u];
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		sum += dfs(v,u);	
	}
	
    //根节点不统计答案
	if(u == 1) return 0;
	if(sum == 0) ans += m;
	if(sum == 1) ++ans;
	
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(head,-1,sizeof(head));
	
	cin >> n >> m;
	int u,v;
	for(int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		addEdge(u,v);
		addEdge(v,u);
	}
	
	build(1,0);
	
	int lca;
	for(int i = 1; i <= m; ++i)
	{
		cin >> u >> v;
		lca = getLCA(u,v);
        //边差分
		++d[u];
		++d[v];
		d[lca] -= 2;
	}
	
    //dfs统计答案
	dfs(1,0);
	
	cout << ans << endl;
	
	return 0;
}