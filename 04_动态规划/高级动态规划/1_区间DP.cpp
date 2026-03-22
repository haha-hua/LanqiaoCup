/*
 * 用途：区间 DP（石子合并问题）
 * 时间复杂度：O(n^3)
 * 应用：区间合并、矩阵连乘、括号配对等问题
 * DP 定义：dp[i][j] = 合并区间 [i,j] 的最小/最大成本
 * 状态转移：dp[i][j] = min(dp[i][k] + dp[k+1][j] + cost(i,j))
 */
#include<iostream>
#include<cstring>

using namespace std;

const int N = 410;
const int INF = 0x3f3f3f3f;

int n,w[N];
int maxdp[N][N],mindp[N][N];
int prefixsum[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(mindp,INF,sizeof(mindp));
	memset(maxdp,-INF,sizeof(maxdp)); 
	
	cin >> n;
	for(int i = 1; i <= n; ++i)
	{
		cin >> w[i];
		w[i + n] = w[i];
	}
	
	for(int i = 1; i < 2 * n; ++i)
	{
		prefixsum[i] = prefixsum[i - 1] + w[i];
		mindp[i][i] = maxdp[i][i] = 0;
	}
	
	for(int len = 2; len <= n; ++len)
	{
		for(int i = 1; i + len - 1 < 2 * n; ++i)
		{
			int j = i + len - 1;
			//[i,j] ,[i,k] + [k + 1,j]
			for(int k = i; k < j; ++k)
			{
				maxdp[i][j] = max(maxdp[i][j],maxdp[i][k] + maxdp[k + 1][j] + 
					prefixsum[j] - prefixsum[i - 1]);
			}
		}
	}
		
	for(int len = 2; len <= n; ++len)
	{
		for(int i = 1; i + len - 1 < 2 * n; ++i)
		{
			int j = i + len - 1;
			for(int k = i; k < j; ++k)
			{
				mindp[i][j] = min(mindp[i][j],mindp[i][k] + mindp[k + 1][j] + 
					prefixsum[j] - prefixsum[i - 1]);
			}
		}
	}
	
	int ans_min = INF;
	int ans_max = -INF;
	
	for(int i = 1; i + n - 1 < 2 * n; ++i)
	{
		ans_min = min(ans_min,mindp[i][i + n - 1]);
		ans_max = max(ans_max,maxdp[i][i + n - 1]);
	}
	
	cout << ans_min << '\n' << ans_max << endl;
	return 0;
}