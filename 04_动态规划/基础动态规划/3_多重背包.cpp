/*
 * 用途：多重背包问题模板
 * 时间复杂度：O(nm log s)，s 为物品的数量上界（二进制优化）
 * 状态定义：dp[j] = 容量为 j 时的最大价值
 * 关键优化：用二进制分组将 s 件物品转化为 log s 个虚拟物品
 * 参考题目：YBT 1269 庆功会 - https://ybt.ssoier.cn/problem_show.php?pid=1269
 */
#include<iostream>

using namespace std;

int n,m;
int v[501],w[501],s[501],dp[6006]; //价格、价值、数量、dp数组

int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> v[i] >> w[i] >> s[i];
	
	for(int i = 1; i <= n; ++i)
	{
        //多重背包：从后往前遍历，保证每个物品只能使用 s[i] 次
		for(int j = m; j >= v[i]; --j)
		{
            //枚举使用 k 件物品 i 的情况，k 从 0 到 s[i]，同时保证 k * v[i] 不超过当前容量 j
			for(int k = 0; k <= s[i] && k <= j / v[i]; ++k)
			{
				dp[j] = max(dp[j],dp[j - k * v[i]] + k * w[i]);
			}
		}
	}
	
	cout << dp[m] << endl; 
	return 0;
}