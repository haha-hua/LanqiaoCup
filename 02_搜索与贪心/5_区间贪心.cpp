/*
 * 用途：区间贪心（按右端点排序）
 * 时间复杂度：O(n log n) 排序 + O(n) 贪心
 * 参考题目：P1803 线段覆盖 - https://www.luogu.com.cn/problem/P1803
 * 输入：n 个比赛的开始和结束时间
 * 输出：最多能参加多少场不重叠的比赛
 */
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1000005;

int n;
//比赛的开始时间和结束时间
struct Node
{
	int st;
	int et; 
	
    //重载<运算符，按照结束时间排序，如果结束时间相同，按照开始时间排序
	bool operator<(const Node& other) const
	{
		if(et != other.et) return et < other.et;
		return st < other.st;
	}
	
}arr[N];


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> arr[i].st >> arr[i].et;
	
	sort(arr + 1,arr + 1 + n);
	
	int cnt = 0;
	int cur_time = 0;
	
    //贪心：按照结束时间排序，优先安排结束时间早的比赛，这样可以为后续的比赛留下更多的时间，增加安排更多参加比赛的可能性
	for(int i = 1; i <= n; ++i)
	{
		if(cur_time <= arr[i].st)
		{
			cur_time = arr[i].et;
			++cnt;
		}
	}
	
	cout << cnt << endl;
	
	return 0;
}