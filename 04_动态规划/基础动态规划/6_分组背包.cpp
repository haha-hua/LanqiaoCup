/*
 * 用途：分组背包问题（每组只能选一个或不选）
 * 时间复杂度：O(n*m*k)，n 组，m 为容量，k 为每组平均大小
 * 状态定义：dp[j] = 容量为 j 时的最大价值
 * 转移：外层按组，内层正序遍历容量，每组内部选择最优
 * 参考题目：YBT 1272 分组背包 - https://ybt.ssoier.cn/problem_show.php?pid=1272
 */
#include<iostream>
#include<vector>

using namespace std;

int m,n,T;
int dp[201];
vector<int> w[11];
vector<int> c[11];

int main()
{
	cin >> m >> n >> T;
	
	int w_val,c_val,id;
	for(int i = 1; i <= n; ++i)
	{
		cin >> w_val >> c_val >> id;
		w[id].push_back(w_val);
		c[id].push_back(c_val);
	}
	
	//枚举组数i
	for(int i = 1; i <= T; ++i)
	{
        //枚举当前容量j
		for(int j = m; j >= 0; --j)
		{
            //枚举组内的每个物品k，保证每组只能选择一个物品
			for(int k = 0; k < w[i].size(); ++k)
			{
				if(j >= w[i][k])
				{
					dp[j] = max(dp[j],dp[j - w[i][k]] + c[i][k]);
				}
			}
		}
	}

	

	cout << dp[m] << endl;
	return 0;
}