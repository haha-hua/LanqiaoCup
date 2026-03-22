/*
 * 用途：数位 DP（按位分析）
 * 时间复杂度：O(log n * 状态数)
 * 应用：计算范围内满足条件的数字个数
 * DP 定义：dp[位置][状态] = 的满足条件的数字个数
 * 状态转移：逐位枚举 0-9，同时追踪是否贴近上界（tight）
 * 参考题目：P2657 Storm Chasing - https://www.luogu.com.cn/problem/P2657
 */
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int n;
int arr[11];
int dp[11][11];

//数位DP：求区间内满足相邻两位数差至少为2的整数个数
//pos：当前处理的位数，pre：上一位的数字，pre_zero：前面是否全为0，limit：当前位是否受上界限制
int dfs(int pos,int pre,bool pre_zero,bool limit)
{
	if(pos == n + 1)
	{
		return 1;
	}
	
	if(dp[pre][n - pos + 1] != 0 && pre_zero == false && limit == false) return dp[pre][n - pos + 1];
	
	int up = limit ? arr[pos] : 9;
	
	int res = 0;
	for(int i = 0; i <= up; ++i)
	{
		if(pre_zero == true)
		{
            //如果前面是0，那么第一位随便选，后面就要满足相邻两位数差至少为2了
			res += dfs(pos + 1,i, pre_zero && i == 0,limit && i == up);
		}
		else if(abs(i - pre) >= 2)
		{
            //如果前面不是0，那么当前位要满足和上一位的数字差至少为2了
			res += dfs(pos + 1,i,pre_zero && i == 0,limit && i == up);
		}
	}
	
    //如果当前位不受上界限制，并且前面不是全0，那么就可以将结果存入dp数组中，避免重复计算，提高效率
	if(limit == false && pre_zero == false) dp[pre][n - pos + 1] = res;
	return res;
}

int solve(int x)
{
	n = 0;
	while(x)
	{
		arr[++n] = x % 10;
		x /= 10;
	}
	reverse(arr + 1,arr + 1 + n);
	return dfs(1,0,true,true);
}

int main()
{
	int a,b;
	
	cin >> a >> b;
	
	int ans_a = solve(a - 1);
	int ans_b = solve(b);
		
	cout << ans_b - ans_a << endl;
//	cout << ans_a << endl << ans_b << endl;
	return 0;
}