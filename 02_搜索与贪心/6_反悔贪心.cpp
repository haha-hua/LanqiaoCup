/*
 * 用途：反悔贪心（配合优先队列）
 * 时间复杂度：O(n log n)，通过堆维护可悔棋的选择
 * 参考题目：P2949 USACO09OPEN 工作调度 - https://www.luogu.com.cn/problem/P2949
 * 输入：工作的截止时间和报酬
 * 输出：在满足截止时间的约束下，最大化总报酬
 */
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

const int N = 100005;
using ll = long long;

int n;
struct Task
{
	int deadline;
	ll val;


    //重载<运算符，按照价值排序，价值高的优先安排，这样我们就可以在截止时间相同的情况下优先安排价值高的任务
	bool operator<(const Task& other) const
	{
		return val > other.val;
	}

}arr[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> arr[i].deadline >> arr[i].val;
	
    //先按照截止时间排序，截止时间相同的按照价值排序，这样我们就可以按照截止时间来安排任务，优先安排价值高的任务
	sort(arr + 1, arr + 1 + n, [](const Task& a, const Task& b) {
    return a.deadline < b.deadline;});
	
	priority_queue<Task> que;
	
	ll ans = 0;
    //反悔贪心：按照截止时间排序，优先安排截止时间早的任务，如果当前任务的截止时间大于队列中任务的数量，那么我们就可以直接安排这个任务，否则我们就需要比较当前任务的价值和队列中价值最低的任务，如果当前任务的价值更高，那么我们就可以替换掉那个任务，这样可以保证我们安排的任务的总价值最大
    //为什么按照截止时间排序？因为我们需要按照截止时间来安排任务，优先安排截止时间早的任务，这样可以为后续的任务留下更多的时间，增加安排更多任务的可能性
	for(int i = 1; i <= n; ++i)
	{
		if(arr[i].deadline > que.size())
		{
			que.push(arr[i]);
			ans += arr[i].val;
		}
		else if(arr[i].val > que.top().val)     //如果当前任务的价值比队列中价值最低的任务还高，那么我们就可以替换掉那个任务，这样可以保证我们安排的任务的总价值最大
		{
			ans += arr[i].val - que.top().val;
			que.pop();
			que.push(arr[i]);
		}
	}
	cout << ans << endl;
	return 0;
}