//https://www.luogu.com.cn/problem/B4016

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
