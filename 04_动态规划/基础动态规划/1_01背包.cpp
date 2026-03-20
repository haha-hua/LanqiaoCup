/*
 * 用途：01背包问题模板
 * 时间复杂度：O(nm)，n 为物品数，m 为背包容量
 * 状态定义：dp[j] = 容量为 j 时的最大价值
 * 转移方程：dp[j] = max(dp[j], dp[j-w[i]]+c[i])
 * 参考题目：YBT 1267 01背包问题 - https://ybt.ssoier.cn/problem_show.php?pid=1267
 */
#include<iostream>

using namespace std;

int n,m;
int w[31],c[31],dp[205];


int main()
{
	cin >> m >> n;
	for(int i = 1; i <= n; ++i) cin >> w[i] >> c[i];	
	
	for(int i = 1; i <= n; ++i)
	{
        //01背包：从后往前遍历，保证每个物品只能使用一次
		for(int j = m; j >= w[i]; --j)
		{
			dp[j] = max(dp[j],dp[j - w[i]] + c[i]);
		}
	}
	
	cout << dp[m] << endl;
	return 0;
}