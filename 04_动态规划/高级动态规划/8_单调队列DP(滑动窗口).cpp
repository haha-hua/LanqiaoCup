/*
 * 用途：单调队列优化 DP（滑动窗口最值）
 * 时间复杂度：O(n)
 * 应用：滑动窗口最大/最小值、DP 转移优化
 * DP 定义：dp[i] = 在窗口内的最优选择
 * 优化：双端队列维护单调性，O(n) 时间内全部计算
 * 参考题目：YBT 1597 单调队列DP - https://ybt.ssoier.cn/problem_show.php?pid=1597
 */
#include<iostream>
#include<deque>

using namespace std;

const int N = 1000005;
int n,k;
int arr[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> k;
	
	for(int i = 1; i <= n; ++i) cin >> arr[i];
	
	deque<int> que;
	
	for(int i = 1; i <= n; ++i)
	{
		while(que.empty() == false && i - que.front() >= k) que.pop_front();
		while(que.empty() == false && arr[i] <= arr[que.back()]) que.pop_back();
		que.push_back(i);
		if(i >= k) cout << arr[que.front()] << ' ';
	}
	
	cout << '\n';
	
	que.clear();
	for(int i = 1; i <= n; ++i)
	{
		while(que.empty() == false && i - que.front() >= k) que.pop_front();
		while(que.empty() == false && arr[i] >= arr[que.back()]) que.pop_back();
		que.push_back(i);
		if(i >= k) cout << arr[que.front()] << ' ';
 	}
	
	return 0;
}