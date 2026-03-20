/*
 * 用途：混合背包问题（01背包、完全背包、多重背包的混合）
 * 时间复杂度：O(nm log s)
 * 状态定义：dp[j] = 容量为 j 时的最大价值
 * 关键：根据数量 s 判断背包类型（1 为 01，无限为完全，其他为多重）
 * 参考题目：YBT 1270 混合背包 - https://ybt.ssoier.cn/problem_show.php?pid=1270
 */
#include<iostream>

using namespace std;

int n,m;
int w[31],c[31],s[31];
int dp[201];

int main()
{
	cin >> m >> n;
	for(int i = 1; i <= n; ++i) cin >> w[i] >> c[i] >> s[i];
	
	for(int i = 1; i <= n; ++i)
	{
		//混合背包：根据 s[i] 的值来判断是 01 背包、完全背包还是多重背包
		if(s[i] == 0)
		{
			//01背包：从后往前遍历，保证每个物品只能使用一次
			for(int j = w[i]; j <= m; ++j)
			{
				dp[j] = max(dp[j],dp[j - w[i]] + c[i]);
			}
		}
		else
		{
			//多重背包：从后往前遍历，保证每个物品只能使用 s[i] 次
			for(int j = m; j >= w[i]; --j)
			{
				for(int k = 0; k <= s[i] && k <= j / w[i]; ++k)
				{
					dp[j] = max(dp[j],dp[j - k * w[i]] + k * c[i]);
				}
			}
		}
	}
	
	cout << dp[m] << endl;
	return 0;
} 