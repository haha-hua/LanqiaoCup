/*
 * 用途：状态压缩 DP（行走问题）
 * 时间复杂度：O(n * 2^n * n) 或 O(2^n * n^2)
 * 应用：TSP、棋盘覆盖、行走计数等
 * DP 定义：dp[mask][i] = 访问集合 mask 中的点，现在在点 i
 * 状态转移：从 mask 状态扩展到 mask | (1<<j) 状态
 */
#include<iostream>
#include<cstring>

using namespace std;

const int N = 21;
using ll = long long;

int n;
ll ap[N][N];
ll dp[1 << N][21];


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			cin >> ap[i][j];
		}
	}
	
	memset(dp,0x3f,sizeof(dp));
	dp[1][0] = 0;
	
	for(int state = 1; state < (1 << n); ++state)
	{
		for(int i = 0; i < n; ++i)
		{
			if((state >> i) & 1)
			{
				for(int j = 0; j < n; ++j)
				{
					int old_state = state ^ (1 << i);
					if((old_state >> j) & 1)
					{
						dp[state][i] = min(dp[state][i],dp[old_state][j] + ap[j][i]);
					}
				}
			}
		}
	}
	
	cout << dp[(1 << n) - 1][n - 1] << endl;
	return 0;
}