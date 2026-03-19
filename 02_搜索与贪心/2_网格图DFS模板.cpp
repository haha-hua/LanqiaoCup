/*
 * 用途：网格图深搜（四方向）
 * 时间复杂度：O(nm)，每个格子最多访问一次
 * 参考题目：P1162 填涂颜色 - https://www.luogu.com.cn/problem/P1162
 * 输入：网格大小 n，以及网格数据
 * 输出：根据题意处理结果
 */
#include<iostream>

using namespace std;

const int N = 35;

int n;
int ap[N][N];
bool vis[N][N];                             //标记是否访问过

int dir[4][2] = {0,1,1,0,0,-1,-1,0};        //上下左右四个方向

void dfs(int x,int y)
{
	vis[x][y] = true;
	
	for(int i = 0; i < 4; ++i)      //尝试四个方向
	{
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		
        //过滤不合法的坐标：越界、障碍物、已经访问过的点
		if(nx < 1 || ny < 1 || nx > n || ny > n) continue;
		if(ap[nx][ny] != 0 || vis[nx][ny] == true) continue;
		
		dfs(nx,ny);
	}
	
	
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			cin >> ap[i][j];
		}
	}
	
    //染色：从边界开始DFS，将所有与边界相连的0标记为访问过，剩下未访问过的0就是被包围的区域
	for(int i = 1; i <= n; ++i)
	{
		if(ap[1][i] == 0 && vis[1][i] == false) dfs(1,i);
		if(ap[i][1] == 0 && vis[i][1] == false) dfs(i,1);
		if(ap[n][i] == 0 && vis[n][i] == false) dfs(n,i);
		if(ap[i][n] == 0 && vis[i][n] == false) dfs(i,n);  
	}
	
//	cout << -1 << endl;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			if(vis[i][j] == false && ap[i][j] == 0) ap[i][j] = 2; 
		}
	}
	
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			cout << ap[i][j] << ' ';
		}
		cout << endl;
	}
	
	return 0;
}