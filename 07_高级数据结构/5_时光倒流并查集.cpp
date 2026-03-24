/*
 * 用途：时光倒流并查集（逆序处理删除操作）
 * 时间复杂度：O(m·α(n))
 * 应用：动态连通性问题的离线处理
 * 方法：将删除操作转化为添加操作，逆序处理
 * 参考题目：YBT 1386 打击犯罪 - https://ybt.ssoier.cn/problem_show.php?pid=1386
 */

#include<iostream>
#include<vector>

using namespace std;

int n,m;
vector<vector<int>> edge;
vector<int> parent;
vector<int> sz;

int findFa(int id)
{
	if(id == parent[id]) return id;
	return parent[id] = findFa(parent[id]);
}

void merge(int u,int v)
{
	int fa1 = findFa(u);
	int fa2 = findFa(v);
	
	if(fa1 == fa2) return ;
	
	if(sz[fa1] < sz[fa2]) swap(fa1,fa2);
	sz[fa1] += sz[fa2];
	parent[fa2] = fa1;

	return ; 

}


int main()
{
	cin >> n;
	edge.resize(n + 1,vector<int>());
	for(int i = 0; i <= n; ++i) 
	{
		parent.push_back(i);
		sz.push_back(1);
	}
	
	for(int i = 1; i <= n; ++i)
	{
		cin >> m;
		int id;
		for(int j = 1; j <= m; ++j)
		{
			cin >> id;
			edge[i].push_back(id);
		}
	}
	
    //从最大编号开始加入并查集，加入后检查当前连通块的大小，如果超过 n / 2 就说明找到了最大的编号，输出并退出
	for(int i = n; i >= 1; --i)
	{
		for(int j = 0; j < edge[i].size(); ++j)
		{
            //如果点的编号i大于edge[i][j],表名edge[i][j]还没有处理(也就是不能加入并查集)
			if(edge[i][j] < i) continue;
			merge(i,edge[i][j]);
		}
		//如果当前连通块的大小超过 n / 2，说明找到了最大的编号，输出并退出
		if(sz[findFa(i)] > n / 2)
		{
			cout << i << endl;
			return 0;
		}
	}
	
	return 0;	
}