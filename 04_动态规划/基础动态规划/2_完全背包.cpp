/*
 * 用途：完全背包问题模板
 * 时间复杂度：O(nm)，每件物品可用无限次
 * 状态定义：dp[j] = 容量为 j 时的最大价值
 * 转移方程：dp[j] = max(dp[j], dp[j-w[i]]+c[i])（正序遍历）
 * 参考题目：YBT 1268 完全背包问题 - https://ybt.ssoier.cn/problem_show.php?pid=1268
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
        //完全背包：从前往后遍历，保证每个物品可以使用多次
		for(int j = w[i]; j <= m; ++j)
		{
			dp[j] = max(dp[j],dp[j - w[i]] + c[i]);
		}
	}
	
	cout << "max=" << dp[m] << endl;
	return 0;
}