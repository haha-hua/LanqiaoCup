/*
 * 用途：二维01背包问题（两个容量限制）
 * 时间复杂度：O(nm*k)，n 个物品，两个容量分别为 m 和 k
 * 状态定义：dp[i][j] = 两个容量分别为 i 和 j 时的最大价值
 * 应用场景：潜水员问题（要求两个容量都满足约束）
 * 参考题目：YBT 1271 潜水员 - https://ybt.ssoier.cn/problem_show.php?pid=1271
 */
#include<iostream>
#include<cstring>

using namespace std;

int n,m,k;
int dp[25][85];
int y[1001],d[1001],w[1001];


int main()
{
	cin >> m >> n;
	cin >> k;
	
	memset(dp,0x3f3f3f3f,sizeof(dp));
	dp[0][0] = 0;
	
	for(int i = 1; i <= k; ++i) cin >> y[i] >> d[i] >> w[i];
	
    //枚举每个物品 i
	for(int i = 1; i <= k; ++i)
	{
        //枚举当前氧气含量j
		for(int j = m; j >= 0; --j)
		{
            //枚举当前氮气含量k
			for(int k = n; k >= 0; --k)
			{
                //计算下一个状态的氧气和氮气含量，注意不能超过 m 和 n 的限制
				int tmp_y = min(m,j + y[i]);
				int tmp_d = min(n,k + d[i]);
				
				dp[tmp_y][tmp_d] = min(dp[tmp_y][tmp_d],dp[j][k] + w[i]);
			}
		}
	}
	cout << dp[m][n] << endl;
	return 0;
}