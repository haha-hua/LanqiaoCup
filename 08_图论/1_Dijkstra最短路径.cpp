// Dijkstra单源最短路径算法模板
// 适用场景：求解带权有向图或无向图中从单个源点到其他所有点的最短路径
// 算法特点：使用优先队列优化，时间复杂度 O((V+E)logV)
// 限制条件：图中不能包含负权边
// 参考题目：P4779 【模板】单源最短路径（标准版） — https://www.luogu.com.cn/problem/P4779

#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int N = 100005;
const int INF = 0x3f3f3f3f;

int n,m,s;
int count_e,head[N];
struct Edge
{
	int to;
	int nxt;
	int w;
}edges[N * 2];

bool vis[N];
int dist[N];

void addEdge(int u,int v,int w)
{
	edges[count_e] = {v,head[u],w};
	head[u] = count_e++;
	
	return ;
}

class Cmp
{
public:
	bool operator()(const pair<int,int>& ob1,const pair<int,int>& ob2) const
	{
		return ob1.first > ob2.first;
	}	
};

void Dijkstra(int s)
{
	memset(dist,INF,sizeof(dist));
	dist[s] = 0;
	
	priority_queue<pair<int,int>,vector<pair<int,int>>,Cmp> que; 	//tot_s , id
	que.push({0,1});
	
	while(que.empty() == false)
	{
		pair<int,int> cur = que.top();
		que.pop();
		
		int u = cur.second;
		if(vis[u] == true) continue;
		vis[u] = true;
		
		for(int k = head[u]; k != -1; k = edges[k].nxt)
		{
			int v = edges[k].to;
			if(dist[v] > dist[u] + edges[k].w)
			{
				dist[v] = dist[u] + edges[k].w;
				que.push({dist[v],v});
			}
		}
		
	}
	
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(head,-1,sizeof(head));
	
	cin >> n >> m >> s;
	int u,v,w;
	for(int i = 1; i <= m; ++i)
	{
		cin >> u >> v >> w;
		addEdge(u,v,w);
	}
	
	Dijkstra(s);
	
	for(int i = 1; i <= n; ++i) cout << dist[i] << ' ';
	cout << '\n';
	return 0;
}