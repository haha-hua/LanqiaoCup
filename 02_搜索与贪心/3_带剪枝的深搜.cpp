/*
 * 用途：带剪枝的深度搜索
 * 时间复杂度：取决于剪枝效率，最坏 O(指数)
 * 参考题目：P9241 蓝桥杯 2023 省 B 飞机降落 - https://www.luogu.com.cn/problem/P9241
 * 输入：飞机的起飞时间、降落时间和需要的停留时间
 * 输出：判断是否可行排序
 */
#include<iostream>

using namespace std;

//飞机的起飞时间、降落时间和需要的时间
struct Plane
{
	int st;
	int dt;
	int needt;
}plane[11];

int n;
bool found;
bool vis[11];

void DFS(int pos,int cur_time)      //pos表示当前正在安排第几架飞机，cur_time表示当前的时间，也就是前面安排的飞机的降落时间
{
	if(found) return ;
	if(pos == n + 1)        //找到了满足条件的全排列
	{
		found = true;
		return ;
	}
	
	for(int i = 1; i <= n; ++i)
	{
        //过滤不合法的情况：已经安排过的飞机、当前时间超过飞机的降落时间
		if(vis[i] == true) continue;
		if(cur_time > plane[i].st + plane[i].dt) continue;
		
		vis[i] = true;  //标记
		DFS(pos + 1,max(cur_time,plane[i].st) + plane[i].needt);
		vis[i] = false;//回溯
 	}
	
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int T;
	
	cin >> T;
	while(T-- > 0)
	{
		cin >> n;
		for(int i = 1; i <= n; ++i) cin >> plane[i].st >> plane[i].dt >> plane[i].needt;        //输入
		
		found = false;          //重置全局变量
		DFS(1,0);               //尝试所有可能，也就是全排列，找到一个满足条件的就可以了
		if(found == false) cout << "NO\n";
		else cout << "YES\n";
	}
	
	
	
	return 0;
}