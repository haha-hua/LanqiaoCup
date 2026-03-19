/*
 * 用途：全排列生成（递归回溯）
 * 时间复杂度：O(n!)
 * 参考题目：P1706 全排列问题 - https://www.luogu.com.cn/problem/P1706
 * 输入：整数 n
 * 输出：1 到 n 的所有排列
 */
#include<iostream>
#include<iomanip>

using namespace std;

int n;
int a[10];
bool vis[10];

void DFS(int pos)
{
    //终止条件
	if(pos == n + 1)
	{
		for(int i = 1; i <= n; ++i) cout << setw(5) << a[i];
		cout << '\n';
		return ;
	}
	
	//尝试所有可能
	for(int i = 1; i <= n; ++i)
	{
		if(vis[i] == true) continue;    //用过就不用了
		vis[i] = true;
		a[pos] = i;
		DFS(pos + 1);
		vis[i] = false;
	}
	
	return ;
}

int main()
{
	cin >> n;
	
	DFS(1);
	
	
	return 0;
}