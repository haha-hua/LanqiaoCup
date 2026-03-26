// Tarjan缩点算法模板
// 适用场景：将有向图中的强连通分量缩成单个点，得到DAG（有向无环图）
// 算法特点：基于DFS的线性时间算法，时间复杂度 O(V + E)
// 应用场景：在缩点后的DAG上进行拓扑排序、动态规划等操作
// 参考题目：P3387 【模板】缩点 — https://www.luogu.com.cn/problem/P3387

#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

const int N = 10005;
const int M = 100005;

//构建图所需要的变量
int n,m,count_e,head[N];
struct Edge
{
	int to;
	int nxt;
}edges[M * 2];

int w[N];

//Tarjan缩点所需要的变量
int scc_cnt,timestamp;      //缩点的个数，时间戳
int low[N],dfn[N],scc_id[N];     //low数组，dfn数组，缩点的id数组
bool instk[N];                   //栈内数组
stack<int> stk;                  //栈数组

int scc_w[N];                   //缩点的权重数组    

vector<int> adj[N];              //缩点的邻接表
int in_degree[N];               //缩点的入度数组
int dp[N];                       //缩点的dp数组

void Tarjan(int u)
{
	dfn[u] = low[u] = ++timestamp;
	instk[u] = true;
	stk.push(u);
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		
		if(dfn[v] == 0)     //未访问过
		{
			Tarjan(v);
			low[u] = min(low[u],low[v]);
		}                   //访问过，在栈内，说明是回边
		else if(instk[v] == true)
		{
			low[u] = min(low[u],dfn[v]);
		}
	}
	
    //如果u是缩点的根，那么u的low值就是u的dfn值
	if(dfn[u] == low[u])
	{
		int id;
		++scc_cnt;
		do
		{
			id = stk.top();
			stk.pop();
			instk[id] = false;
			scc_id[id] = scc_cnt;
            //更新缩点的权重
			scc_w[scc_cnt] += w[id];
		}while(id != u);
	}
	
	return ;
}

void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
	return ;
}

void Topo()
{
	int ans = 0;
	queue<int> que;
	
	for(int i = 1; i <= scc_cnt; ++i)
	{
		if(in_degree[i] == 0) que.push(i);
		dp[i] = scc_w[i];
	}
	
	while(que.empty() == false)
	{
		int u = que.front();
		que.pop();
		
		ans = max(ans,dp[u]);
		for(int v : adj[u])
		{
			dp[v] = max(dp[v],dp[u] + scc_w[v]);
			if(--in_degree[v] == 0) que.push(v);
		}
	}
	
	
	cout << ans << endl;
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(head,-1,sizeof(head));
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; ++i) cin >> w[i];

	int u,v;
	for(int i = 1; i <= m; ++i)
	{
		cin >> u >> v;
		addEdge(u,v);
	}
	
	for(int i = 1; i <= n; ++i) if(dfn[i] == 0) Tarjan(i);
	
	for(int u = 1; u <= n; ++u)
	{
		for(int k = head[u]; k != -1; k = edges[k].nxt)
		{
			int v = edges[k].to;
			if(scc_id[u] != scc_id[v])
			{
				adj[scc_id[u]].push_back(scc_id[v]);
				in_degree[scc_id[v]]++;
			}
		}
	}
	
	Topo();
	
	return 0;
}