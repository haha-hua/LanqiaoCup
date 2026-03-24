/*
 * 用途：并查集判断图中是否存在环
 * 时间复杂度：O(α(n))
 * 应用：图论中的环检测问题
 * 方法：利用并查集判断两点是否已在同一集合
 * 参考题目：YBT 1347：【例4-8】格子游戏 - https://ybt.ssoier.cn/problem_show.php?pid=1347
 */

#include<iostream>


using namespace std;

const int N = 201;

int n,m;
int parent[N * N],sz[N * N];


//将二维坐标映射到一维
int getID(int x,int y)
{
	return (x - 1) * N + y;
}

//路径压缩
int findfa(int id)
{
	if(id == parent[id]) return id;
	return parent[id] = findfa(parent[id]);
}

//合并两个集合，返回是否成功合并（即是否原本不在同一集合）
bool merge(int x,int y)
{
	int fa1 = findfa(x);
	int fa2 = findfa(y);
	
	if(fa1 == fa2) return false;
	
	if(sz[fa1] < sz[fa2]) swap(fa1,fa2);
	
	parent[fa2] = fa1;
	sz[fa1] += sz[fa2];
	
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	
    //初始化并查集，每个点自成一个集合
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			int id = getID(i,j);
			parent[id] = id;
			sz[id] = 1;
		}
	}
	
	int x1,y1,x2,y2;
	char op;
	for(int i = 1; i <= m; ++i)
	{
		cin >> x1 >> y1 >> op;
		if(op == 'D') x2 = x1 + 1,y2 = y1;
		if(op == 'R') x2 = x1,y2 = y1 + 1;
		
		bool success = merge(getID(x1,y1),getID(x2,y2));
		if(success == false)
		{
            //如果合并失败，说明这两个点已经在同一个集合中，即形成了环
			cout << i << endl;
			return 0;
		}
	}
	
	cout << "draw" << endl;
	return 0;
}