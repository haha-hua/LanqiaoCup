/*
 * 用途：01 字典树（异或最值）
 * 时间复杂度：O(31)
 * 应用：最大异或对、异或最值问题
 * 方法：贪心选择与当前位不同的路径
 * 参考题目：P10471 最大异或对 The XOR Largest Pair - https://www.luogu.com.cn/problem/P10471
 */


#include<iostream>

using namespace std;

const int N = 100005;

int n,tot;
int arr[N],tree[N * 31][2];


void insert(int x)
{
	int p = 0;
	for(int i = 30; i >= 0; --i)
	{
		int j = (x >> i) & 1;
		if(tree[p][j] == 0) tree[p][j] = ++tot;
		p = tree[p][j];
	}
	
	return ;
}

int query(int x)
{
	int ans = 0;
	int p = 0;
	
	for(int i = 30; i >= 0; --i)
	{
		int j = (x >> i) & 1;
		if(tree[p][!j] != 0)
		{
			ans += (1 << i);
			p = tree[p][!j];
		}
		else p = tree[p][j];
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; ++i)
	{
		cin >> arr[i];
		insert(arr[i]);
	}
	
	int maxn = 0;
	for(int i = 1; i <= n; ++i) maxn = max(maxn,query(arr[i]));
	
	cout << maxn << endl;
	return 0;
}