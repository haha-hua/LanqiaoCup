/*
 * 用途：树状数组（单点修改，区间查询）
 * 时间复杂度：O(log n)
 * 应用：单点更新、区间求和
 * 方法：利用二进制分解实现高效前缀和
 * 参考题目：P3374 【模板】树状数组 - https://www.luogu.com.cn/problem/P3374
 */

#include<iostream>

using namespace std;

using ll = long long;
const int N = 500005;

int n,m;
ll tree[N];

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
	ll x,y;
	for(int i = 1; i <= n; ++i)
	{
		cin >> x;
		add(i,x);
	}
	
	int op;
	for(int i = 1; i <= m; ++i)
	{
		cin >> op >> x >> y;
		if(op == 1) add(x,y);
		if(op == 2) cout << query(y) - query(x - 1) << '\n';
	}
	
	return 0;
}