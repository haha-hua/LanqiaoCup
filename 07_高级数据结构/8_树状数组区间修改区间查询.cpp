/*
 * 用途：树状数组（区间修改，区间查询）
 * 时间复杂度：O(log n)
 * 应用：区间更新、区间查询
 * 方法：维护两个树状数组（差分数组的前缀和）
 * 参考题目：P3372 【模板】线段树 1 - https://www.luogu.com.cn/problem/P3372
 */


#include<iostream>


using namespace std;

using ll = long long;
const int N = 100005;

int n,m;
ll tree1[N],tree2[N];


int lowbit(int x)
{
	return x & -x;
}

//添加val 到树状数组 tree 的 pos 位置
void add(ll* tree,int pos,ll val)
{
	while(pos <= n)
	{
		tree[pos] += val;
		pos += lowbit(pos);
	}
	
	return ;
}

//查询树状数组 tree 的前缀和，即 tree[1] + tree[2] + ... + tree[pos]
ll query(ll* tree,int pos)
{
	ll sum = 0;
	while(pos > 0)
	{
		sum += tree[pos];
		pos -= lowbit(pos);
	}	
	return sum;
}

//区间添加 val 到 [x,y] 区间
void rangeAdd(int x,int y,ll val)
{
	add(tree1,x,val);
	add(tree1,y + 1,-val);
	
	add(tree2,x,val * x);
	add(tree2,y + 1,-val * (y + 1));
	
	return ;
}

//查询前缀和，即 arr[1] + arr[2] + ... + arr[x] = S[x]
ll preSum(int x)
{
	return (x + 1) * query(tree1,x) - query(tree2,x);
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	ll op,x,y,val; 
	for(int i = 1; i <= n; ++i)
	{
		cin >> val;
		rangeAdd(i,i,val);
	}
	
	for(int i = 1; i <= m; ++i)
	{
		cin >> op >> x >> y;
		if(op == 1)
		{
			cin >> val;
            //将 val 添加到区间 [x,y] 上，即 arr[x] += val, arr[x+1] += val, ..., arr[y] += val
			rangeAdd(x,y,val);
		}
		if(op == 2)
		{
            //查询区间 [x,y] 的和，即 S[y] - S[x-1]
			cout << preSum(y) - preSum(x - 1) << '\n';
		}
	}
	
	return 0;
}