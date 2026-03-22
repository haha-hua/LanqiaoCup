/*
 * 用途：树形 DP（没有上司的舞会）
 * 时间复杂度：O(n)
 * 应用：树上独立集、树上选择问题
 * DP 定义：dp[i][0] = 不选点 i，dp[i][1] = 选点 i
 * 状态转移：考虑选与不选当前点，递归求解子树
 */
#include<iostream>
#include<cstring>

using namespace std;

const int N = 6005;

int n;
int count_e;
int w[N],head[N];
struct Edge
{
	int to;
	int nxt;
}edges[N * 2];

int dp[N][2];

void addEdge(int u,int v)
{
	edges[count_e] = {v,head[u]};
	head[u] = count_e++;
	
	return ;
}

void dfs(int u,int fa)
{
	dp[u][1] = w[u];
	dp[u][0] = 0;
	
	for(int k = head[u]; k != -1; k = edges[k].nxt)
	{
		int v = edges[k].to;
		if(v == fa) continue;
		
		dfs(v,u);
        //不选u，选v或者不选v
		dp[u][0] = max(dp[u][0],dp[u][0] + max(dp[v][0],dp[v][1]));
		//选u，不选v
        dp[u][1] = max(dp[u][1],dp[u][1] + dp[v][0]);
	}
	
	return ;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(head,-1,sizeof(head));
	memset(dp,-0x3f3f3f3f,sizeof(dp));
	
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> w[i];
	
	int u,v;
	for(int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		addEdge(u,v);
		addEdge(v,u);
	}
	
	dfs(1,0);
	
	cout << max(dp[1][0],dp[1][1]) << endl;
	return 0;
}