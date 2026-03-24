/*
 * 用途：线段树懒标记（加法和乘法）
 * 时间复杂度：O(log n)
 * 应用：区间加法和乘法操作
 * 方法：懒标记组合，注意先乘后加
 * 参考题目：P3373 【模板】线段树 2 - https://www.luogu.com.cn/problem/P3373
 */


#include<iostream>

using namespace std;

using ll = long long;
const int N = 100005;

struct Node
{
	int l;
	int r;
	ll sum;
	ll z_add;
	ll z_mult;
};

int n,q;
ll MOD;
ll arr[N];
Node tree[N * 4];


void pushup(int p)
{
	tree[p].sum = (tree[p * 2].sum + tree[p * 2 + 1].sum) % MOD;
	return ;
}

void pushdown(int p)
{
	if(tree[p].z_mult != 1 || tree[p].z_add != 0)
	{
        //这里需要先乘再加，因为乘法会影响加法的结果
        //乘法就是乘以tree[p].z_mult，乘法的结果需要对MOD取模
        //加法就是加上tree[p].z_add * (tree[son].r - tree[son].l + 1)，加法的结果需要对MOD取模
		tree[p * 2].sum = (tree[p * 2].sum * tree[p].z_mult + tree[p].z_add * (tree[p * 2].r - tree[p * 2].l + 1)) % MOD;
		tree[p * 2 + 1].sum = (tree[p * 2 + 1].sum * tree[p].z_mult + tree[p].z_add * (tree[p * 2 + 1].r - tree[p * 2 + 1].l + 1)) % MOD;
		
		tree[p * 2].z_mult = tree[p * 2].z_mult * tree[p].z_mult % MOD;
		tree[p * 2 + 1].z_mult = tree[p * 2 + 1].z_mult * tree[p].z_mult % MOD;
		
		tree[p * 2].z_add = (tree[p * 2].z_add * tree[p].z_mult + tree[p].z_add) % MOD;
		tree[p * 2 + 1].z_add = (tree[p * 2 + 1].z_add * tree[p].z_mult + tree[p].z_add) % MOD;
		
		tree[p].z_mult = 1;
		tree[p].z_add = 0;
	}
	
	return ;
}

void build(int p,int l,int r)
{
	tree[p] = {l,r,arr[l] % MOD,0,1};
	if(l == r) return ;
	
	int mid = (l + r) / 2;
	build(p * 2,l,mid);
	build(p * 2 + 1,mid + 1,r);
	pushup(p);
	return ;
}

void add(int p,int l,int r,ll val)
{
	if(l <= tree[p].l && tree[p].r <= r)
	{
		tree[p].sum = (tree[p].sum + (tree[p].r - tree[p].l + 1) * val % MOD) % MOD;
		tree[p].z_add = (tree[p].z_add + val) % MOD;
		return ;
	}
	
	pushdown(p);
	
	int mid = (tree[p].l + tree[p].r) / 2;
	
	if(l <= mid) add(p * 2,l,r,val);
	if(r > mid) add(p * 2 + 1,l,r,val);
	
	pushup(p);
	return ;
}

void multi(int p,int l,int r,ll val)
{
	if(l <= tree[p].l && tree[p].r <= r)
	{
		tree[p].sum = tree[p].sum * val % MOD;
		tree[p].z_mult = tree[p].z_mult * val % MOD;
		tree[p].z_add = tree[p].z_add * val % MOD;		//乘法会影响加法的结果，所以加法的z_add值也需要乘以val  
		return ;
	}
	
	pushdown(p);
	
	int mid = (tree[p].l + tree[p].r) / 2;
	
	if(l <= mid) multi(p * 2,l,r,val);
	if(r > mid) multi(p * 2 + 1,l,r,val);
	
	pushup(p);
	return ;
}

ll query(int p,int l,int r)
{
	if(l <= tree[p].l && tree[p].r <= r) return tree[p].sum;
	
	pushdown(p);
	
	int mid = (tree[p].l + tree[p].r) / 2;
	ll sum = 0;
	if(l <= mid) sum = query(p * 2,l,r) % MOD;
	if(r > mid) sum += query(p * 2 + 1,l,r);
	
	return sum % MOD;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> q >> MOD; 
	
	for(int i = 1; i <= n; ++i) cin >> arr[i];	
	
	build(1,1,n);
	
	int op,l,r;
	ll val;
	for(int i = 1; i <= q; ++i)
	{
		cin >> op >> l >> r;
		if(op == 1)
		{
			cin >> val;
			val %= MOD;
			multi(1,l,r,val);
		}
		if(op == 2)
		{
			cin >> val;
			val %= MOD;
			add(1,l,r,val);
		}
		if(op == 3)
		{
			cout << query(1,l,r) % MOD << '\n';
		}
	}
	
	return 0;
}