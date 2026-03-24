/*
 * 用途：并查集维护连通块信息 + 背包 DP
 * 时间复杂度：O(α(n)·n)
 * 应用：有依赖关系的背包问题
 * 方法：并查集合并连通块，DP 求解最优方案
 * 参考题目：YBT 1387 搭配购买 - https://ybt.ssoier.cn/problem_show.php?pid=1387
 */

#include<iostream>


using namespace std;

const int N = 10005;

int n,m,tot_w;
int w[N],c[N];

//并查集维护连通块的总重量和总价值
int parent[N],sz[N];
int sumw[N],sumc[N];

int dp[N];

int findfa(int id)
{
	if(id == parent[id]) return id;
	return parent[id] = findfa(parent[id]);
}

void merge(int x,int y)
{
	int fa1 = findfa(x);
	int fa2 = findfa(y);
	
	if(fa1 == fa2) return ;
	
	if(sz[fa1] < sz[fa2]) swap(fa1,fa2);
	//按秩合并，小树合并到大树上
	parent[fa2] = fa1;
	sz[fa1] += sz[fa2];
	sumc[fa1] += sumc[fa2];
	sumw[fa1] += sumw[fa2];
    //合并后更新连通块的总重量和总价值
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m >> tot_w;
    //输入每个物品的重量和价值，并初始化并查集，每个物品自成一个集合，连通块的总重量和总价值初始为物品本身的重量和价值
	for(int i = 1; i <= n; ++i)
	{
		cin >> w[i] >> c[i];
		parent[i] = i;
		sz[i] = 1;
		sumw[i] = w[i];
		sumc[i] = c[i];
 	}
	
	int x,y;
	for(int i = 1; i <= m; ++i)
	{
		cin >> x >> y;
		merge(x,y);
	}

	for(int i = 1; i <= n; ++i)
	{
        //如果 i 不是集合的代表元，说明它所在的连通块已经被处理过了，直接跳过
		if(parent[i] != i) continue;
		for(int j = tot_w; j >= sumw[i]; --j)
		{
			dp[j] = max(dp[j],dp[j - sumw[i]] + sumc[i]);
		}
	}
	
	cout << dp[tot_w] << endl;
	return 0;
}