//题目链接:https://www.luogu.com.cn/problem/P9235(P9235 [蓝桥杯 2023 省 A] 网络稳定性)

/*
由题目可以看到需要求AB之间的最小边权的最大值，那么我们肯定先选最大的。
但是发现查询是1e5次，必须是O(1)或者O(logN)的查询，就想到LCA。
但是这个是图不是树，我们只需要知道最大的就行，那么就是构建最大生成树，然后剩下的就是LCA维护最小边权就AC了。
*/

#include<iostream>
#include<cstring>
#include<algorithm> 

using namespace std;

const int N = 1e5 + 5;
const int M = 6e5 + 5; 
const int Limit = 18;
const int INF = 0x3f3f3f3f; 

int n,m,q,count_e,head[N];
struct Edge1
{
	int to;
	int nxt;
	int w;
}edges[M];

struct Edge2
{
	int u;
	int v;
	int w;
	
	bool operator<(const Edge2& other) const
	{
		return w > other.w;
	}
	
}adj[M];

int parent[N],up[N][Limit],depth[N],d[N][Limit];

int findfa(int id)
{
	if(id == parent[id]) return id;
	return parent[id] = findfa(parent[id]);
}

void addEdge(int u,int v,int w)
{
	edges[count_e] = {v,head[u],w};
	head[u] = count_e++;
	return ;
}

void dfs(int u,int fa,int w)
{
	depth[u] = depth[fa] + 1;
	up[u][0] = fa;
	d[u][0] = w;
	
	for(int i = 1; i < Limit; ++i)
	{
		int mid = up[u][i - 1];
		d[u][i] = min(d[u][i - 1],d[mid][i - 1]); 
		up[u][i] = up[mid][i - 1];
	}
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		 
		dfs(v,u,edges[k].w);
	}
	
	return ;
}

int getLCA(int u,int v)
{
	if(depth[u] < depth[v]) swap(u,v);
	
	int mind = INF;
	
	for(int i = Limit - 1; i >= 0; --i)
	{
		if(depth[up[u][i]] >= depth[v])
		{
			mind = min(mind,d[u][i]);
			u = up[u][i];
		}
	}
	
	if(u == v) return mind;
	
	for(int i = Limit - 1; i >= 0; --i)
	{
		if(up[u][i] != up[v][i])
		{
			mind = min(mind,d[u][i]);
			mind = min(mind,d[v][i]);
			
			u = up[u][i];
			v = up[v][i];
		}
	}
	
	mind = min(mind,d[u][0]);
	mind = min(mind,d[v][0]);
	return mind;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(head,-1,sizeof(head)); 
	memset(d,INF,sizeof(d));
	
	cin >> n >> m >> q;
	for(int i = 1; i <= m; ++i) cin >> adj[i].u >> adj[i].v >> adj[i].w;
	
	sort(adj + 1,adj + 1 + m);
	
	for(int i = 1; i <= n; ++i) parent[i] = i;
	
	for(int i = 1; i <= m; ++i)
	{
		int fa1 = findfa(adj[i].u);
		int fa2 = findfa(adj[i].v);
		
		if(fa1 != fa2)
		{
			addEdge(adj[i].u,adj[i].v,adj[i].w);
			addEdge(adj[i].v,adj[i].u,adj[i].w);
			
			parent[fa1] = fa2;
		}
	}
	
	for(int i = 1; i <= n; ++i)
	{
		if(parent[i] == i)
		{
			dfs(i,0,0);
		}
	}
	
	int u,v;
	while(q-- > 0)
	{
		cin >> u >> v;
		
		if(findfa(u) != findfa(v)) cout << -1 << '\n';
		else cout << getLCA(u,v) << '\n';
	}
	
	return 0;
} 