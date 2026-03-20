/*
 * 用途：货币方案数（完全背包计数版）
 * 时间复杂度：O(nm)，求凑出金额 m 的方案总数
 * 状态定义：dp[j] = 凑出金额 j 的方案数
 * 转移：dp[j] += dp[j-w[i]]（完全背包转移）
 * 参考题目：YBT 1273 货币系统 - https://ybt.ssoier.cn/problem_show.php?pid=1273
 */
#include<iostream>

using namespace std;

int n,m;
long long w[21],dp[4005];

int main()
{
	cin >> n >> m;
	
	for(int i = 1; i <= n; ++i) cin >> w[i];
	
	dp[0] = 1;
    //枚举钱的面值w[i]
	for(int i = 1; i <= n; ++i)
	{
        //枚举当前金额j，从w[i]开始，保证每个面值可以使用多次
        //相当于完全背包：dp[j] += dp[j - w[i]]，表示使用面值w[i]的方案数等于不使用面值w[i]的方案数加上使用面值w[i]的方案数
        for(int j = w[i]; j <= m; ++j)
		{
			dp[j] += dp[j - w[i]];
		}
	}
	
	cout << dp[m] << endl;
	
	return 0;
}