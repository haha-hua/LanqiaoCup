/*
 * 用途：最长上升子序列（LIS）及其方案还原
 * 时间复杂度：O(nlogn)
 * 参考题目：P8736 [蓝桥杯 2020 国 B] 游园安排 - https://www.luogu.com.cn/problem/P8736
 * 输入：包含多个首字母大写、其余字母小写的人名的字符串
 * 输出：长度最长且字典序最小的上升子序列（人名序列）
 */
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int N = 1e6 + 5;

int n;
string str[N];
int dp[N];          //dp[i]表示以str[i]结尾的最长上升子序列的长度

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	string s;
	cin >> s; 
	//构建数组
	for(int i = 0; i < s.size();)
	{
		if(s[i] >= 'A' && s[i] <= 'Z')
		{
			++n;
			str[n] += s[i];
			++i;
			while(i < s.size() && s[i] >= 'a' && s[i] <= 'z')
			{
				str[n] += s[i];
				++i; 
			}
		}
	}
	
    //求最长上升子序列
	vector<string> tmp;
	for(int i = 1; i <= n; ++i)
	{
		vector<string>::iterator it = lower_bound(tmp.begin(),tmp.end(),str[i]);
		dp[i] = it - tmp.begin() + 1;
		
		if(it == tmp.end()) tmp.push_back(str[i]);
		else *it = str[i];
	}
	
	int L = tmp.size();
	string last_val = "";	
	vector<string> ans;

	
    //贪心求解字典序最小的最长上升子序列
    for(int i = n; i >= 1; --i)
	{
		if(L == dp[i])
		{
			if(ans.empty() || last_val > str[i])
			{
				last_val = str[i];
				ans.push_back(str[i]);
				--L;
			}
		}
	}
	
    //倒序输出答案 
	for(int i = ans.size() - 1; i >= 0; --i) cout << ans[i];
	
	return 0;
}