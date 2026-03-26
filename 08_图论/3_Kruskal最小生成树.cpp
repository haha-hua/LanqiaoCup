// Kruskal最小生成树算法模板
// 适用场景：求解无向连通图的最小生成树
// 算法特点：基于贪心思想，使用并查集维护连通性，时间复杂度 O(E log E)
// 算法步骤：将所有边按权重排序，依次选择不形成环的最小权重边
// 参考题目：P3366 【模板】最小生成树 — https://www.luogu.com.cn/problem/P3366

#include<iostream>
#include<queue>

using namespace std;

const int N = 5005;
const int M = 400006;

int n,m;
int parent[N];

struct Edge
{
	int u;
	int v;
	int w;
	
	bool operator<(const Edge& other) const
	{
		return w > other.w;
	}
	
}edges[M];

int findfa(int id)
{
	if(id == parent[id]) return id;
	return parent[id] = findfa(parent[id]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;	
	for(int i = 1; i <= n; ++i) parent[i] = i;
	
	priority_queue<Edge> que;
	int u,v,w;
	for(int i = 1; i <= m; ++i)
	{
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
		que.push(edges[i]);
	}
	
	int cnt = 0,ans = 0;
	while(cnt != n - 1 && que.empty() == false)
	{
		Edge cur = que.top();
		que.pop();
		
		int fa1 = findfa(cur.u);
		int fa2 = findfa(cur.v);
		
		if(fa1 == fa2) continue;
		++cnt;
		parent[fa1] = fa2;
		ans += cur.w;
	}
	
	if(cnt != n - 1) cout << "orz\n";
	else cout << ans << endl;
	
	return 0;
}