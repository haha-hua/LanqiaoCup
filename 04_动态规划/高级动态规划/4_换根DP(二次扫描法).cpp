/*
 * 用途：换根 DP（二次扫描法）
 * 时间复杂度：O(n)
 * 应用：计算以每个点为根的子树性质
 * DP 定义：第一遍自下而上计算，第二遍自上而下传递信息
 * 状态转移：换根时，从父节点传递信息到子节点
 */
#include<iostream>
#include<cstring>

using namespace std;

using ll = long long;
const int N = 1000005;

int n,count_e,head[N];
struct Edge
{
	int to;
	int nxt;
}edges[N * 2];
ll sz[N];
ll s[N];
ll maxn,ans_u;

void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
	return ;
}

ll dfs1(int u,int fa,int depth)
{
	s[1] += depth;
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		
		sz[u] += dfs1(v,u,depth + 1);	
	}
	return sz[u] + 1;
}

void dfs2(int u,int fa)
{
	if(s[u] > maxn) maxn = s[u],ans_u = u;
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		
		s[v] = s[u] + (n - sz[v]) - sz[v];
		dfs2(v,u);
	} 
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(head,-1,sizeof(head));
		
	cin >> n;
	
	int u,v;
	for(int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		addEdge(u,v);
		addEdge(v,u);
	}
	
	dfs1(1,0,1);
	
	ans_u = 1;
	maxn = s[1];
	dfs2(1,0);
	
	cout << ans_u << endl;
	
	return 0;
}