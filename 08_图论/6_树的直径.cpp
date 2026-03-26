// 树的直径算法模板
// 适用场景：求解无根树中最长路径的长度（边数或权重和）
// 算法特点：两次DFS/BFS，时间复杂度 O(N)
// 算法原理：从任意点出发找到最远点u，再从u出发找到最远点v，u到v的路径即为直径
// 参考题目：B4016 树的直径 — https://www.luogu.com.cn/problem/B4016

#include<iostream>
#include<cstring>

using namespace std;

const int N = 100005;

int n;
int count_e,head[N];
struct Edge
{
	int to;
	int nxt;
}edges[N * 2];


void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
	return ;
}

int ans_u = 0,max_depth = 0;
void dfs(int u,int fa,int depth)
{
	if(max_depth < depth)
	{
		ans_u = u;
		max_depth = depth;
	}
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		dfs(v,u,depth + 1);
	} 
	
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(head,-1,sizeof head);
	cin >> n;
	int u,v;
	for(int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		addEdge(u,v);
		addEdge(v,u);
	}
	
	dfs(1,0,1);
	
	dfs(ans_u,0,1);
	
	cout << max_depth - 1 << endl;
	return 0;
}