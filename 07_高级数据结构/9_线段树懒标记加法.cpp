/*
 * 用途：线段树懒标记（加法操作）
 * 时间复杂度：O(log n)
 * 应用：区间更新、区间查询
 * 方法：懒标记延迟更新，避免重复操作
 * 参考题目：P3372 【模板】线段树 1 - https://www.luogu.com.cn/problem/P3372
 */


#include<iostream>

using namespace std;

const int N = 100005;
using ll = long long;

int n, m;
struct Node
{
	int l;
	int r;
	ll sum;
	ll z_add;

}tree[N * 4];       //空间需要开到4N

ll arr[N];          //原数组

//向上更新父节点的sum值
void pushup(int p)
{
	tree[p].sum = tree[p * 2].sum + tree[p * 2 + 1].sum;
	return;
}

//向下还欠的值，也就是z_add
void pushdown(int p)
{
	if (tree[p].z_add != 0)
	{
		tree[p * 2].sum += (tree[p * 2].r - tree[p * 2].l + 1) * tree[p].z_add;
		tree[p * 2 + 1].sum += (tree[p * 2 + 1].r - tree[p * 2 + 1].l + 1) * tree[p].z_add;

		tree[p * 2].z_add += tree[p].z_add;
		tree[p * 2 + 1].z_add += tree[p].z_add;

		tree[p].z_add = 0;
	}

	return;
}

//建树，p是当前节点编号，l和r是当前节点负责的区间
void build(int p, int l, int r)
{
	tree[p] = { l,r,arr[l],0 };
	if (l == r) return;

	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);

    //建树完成后向上更新父节点的sum值
	pushup(p);
	return ;
}

//区间添加val到 [l,r] 区间上，即 arr[l] += val, arr[l+1] += val, ..., arr[r] += val
void add(int p, int l, int r, ll val)
{
    //如果当前节点负责的区间 [tree[p].l, tree[p].r] 完全包含在 [l,r] 区间内，那么就直接更新当前节点的sum值和z_add值，并返回
	if (l <= tree[p].l && tree[p].r <= r)
	{
		tree[p].sum += (tree[p].r - tree[p].l + 1) * val;
		tree[p].z_add += val;
		return;
	}

    //还欠的值先向下传递给子节点，保证子节点的sum值是正确的
	pushdown(p);

	int mid = (tree[p].l + tree[p].r) / 2;

    //易错点:add()参数一定需要传l,r
    //如果 [l,r] 区间和当前节点负责的区间 [tree[p].l, tree[p].r] 有交集，那么就继续向下传递给子节点
	if (l <= mid) add(p * 2, l, r, val);
	if (r > mid) add(p * 2 + 1, l, r, val);

	pushup(p);
	return;
}

ll query(int p, int l, int r)
{
    //如果当前节点负责的区间 [tree[p].l, tree[p].r] 完全包含在 [l,r] 区间内，那么就直接返回当前节点的sum值
	if (l <= tree[p].l && tree[p].r <= r) return tree[p].sum;

    //还欠的值先向下传递给子节点，保证子节点的sum值是正确的
	pushdown(p);

	int mid = (tree[p].l + tree[p].r) / 2;

	ll sum = 0;

    //易错点:query()参数一定需要传l,r
    //如果 [l,r] 区间和当前节点负责的区间 [tree[p].l, tree[p].r] 有交集，那么就继续向下传递给子节点，并累加子节点的sum值
	if (l <= mid) sum += query(p * 2, l, r);
	if (r > mid) sum += query(p * 2 + 1, l, r);
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
		
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> arr[i];

	build(1, 1, n);

	int op, l, r;
	ll val;

	for (int i = 1; i <= m; ++i)
	{
		cin >> op >> l >> r;
		if (op == 1)
		{
			cin >> val;
			add(1, l, r, val);
		}
		if (op == 2)
		{
			cout << query(1, l, r) << '\n';
		}
	}

	return 0;
}