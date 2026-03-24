/*
 * 用途：树状数组（区间修改，单点查询）
 * 时间复杂度：O(log n)
 * 应用：区间更新、单点查询
 * 方法：差分数组 + 树状数组
 * 参考题目：P3368 【模板】树状数组 2 - https://www.luogu.com.cn/problem/P3368
 */

#include<iostream>

using namespace std;

using ll = long long;
const int N = 500005;

int n,m;
ll arr[N],tree[N];

int lowbit(int x)
{
	return x & -x;
}

void add(int pos,ll val)
{
	while(pos <= n)
	{
		tree[pos] += val;
		pos += lowbit(pos); 
	}
	return ;
}

ll query(int pos)
{
	ll sum = 0;
	while(pos > 0)
	{
		sum += tree[pos];
		pos -= lowbit(pos);
	}
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> arr[i];
	
	int op;
	ll x,y,val;
	
	for(int i = 1; i <= m; ++i)
	{
		cin >> op;
		if(op == 1) 
		{
			cin >> x >> y >> val;
			add(x,val);
			add(y + 1,-val);
		}
		if(op == 2)
		{
			cin >> x;
			cout << arr[x] + query(x) << '\n';
		}
	}
	
	
	
	return 0;
}