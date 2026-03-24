/*
 * 用途：并查集基础（路径压缩+按秩合并）
 * 时间复杂度：O(α(n))
 * 应用：动态连通性问题、集合合并与查询
 * 方法：路径压缩 + 按秩合并优化
 * 参考题目：P3367 【模板】并查集 - https://www.luogu.com.cn/problem/P3367
 */
#include<iostream>


using namespace std;

const int N = 200005;

int n,m;
int parent[N],sz[N];

//路径压缩
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
	//按秩合并，小树合并到大树上
	if(sz[fa1] < sz[fa2]) swap(fa1,fa2); 
	
	parent[fa2] = fa1;
	sz[fa1] += sz[fa2];
	
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) 
	{
		parent[i] = i;
		sz[i] = 1;
	}
	
	
	int z,x,y;
	for(int i = 1; i <= m; ++i)
	{
		cin >> z >> x >> y;
		if(z == 1)
		{
			merge(x,y);
		}
		else
		{
			cout << (findfa(x) == findfa(y) ? 'Y' : 'N') << '\n';
		}
	}
	
	
	
	return 0;
}