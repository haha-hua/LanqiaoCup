/*
 * 用途：树上分组背包 DP
 * 时间复杂度：O(n * m^2)
 * 应用：树上物品分派、路径选择问题
 * DP 定义：dp[i][j] = 以点 i 为根、背包容量 j 的最大权值
 * 状态转移：分组背包，枚举子树选择数量组合
 */
#include<iostream>
#include<cstring>

using namespace std;

const int N = 305;


int n,m;
int count_e;
int head[N];
struct Edge
{
	int to;
	int nxt;
}edges[N * 2];

int w[N];
int dp[N][N];

void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
	
	return ;
}


void dfs(int u,int fa)
{
	dp[u][1] = w[u];
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		
		dfs(v,u);
		
        //当前u选i门课，v选k门课
		for(int i = m + 1; i >= 1; --i)
		{
			for(int k = 0; k < i; ++k)
			{
                //选i门课，v选k门课
				dp[u][i] = max(dp[u][i],dp[u][i - k] + dp[v][k]);
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
	
	cin >> n >> m;
	
	int u;
	for(int i = 1; i <= n; ++i)
	{
		cin >> u >> w[i];
		addEdge(i,u);
		addEdge(u,i);
	}
	
	dfs(0,0);
	
	cout << dp[0][m + 1] << endl;
	return 0;
}