/*
 * 用途：带权并查集（3对关系维护）
 * 时间复杂度：O(α(n))
 * 应用：食物链问题、维护元素间的相对关系
 * 方法：利用模运算维护三类关系（同类、被吃、吃）
 * 参考题目：P2024 [NOI2001] 食物链 - https://www.luogu.com.cn/problem/P2024
 */


#include<iostream>


using namespace std;

const int N = 150005;

int n,k;
int parent[N],sz[N];

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
	
	parent[fa2] = fa1;
	sz[fa1] += sz[fa2];
	return ;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> k;
	
    //因为有三种关系：x eat y, x == y, y eat x，所以每个元素需要三个编号，分别表示它自己、它吃的东西、吃它的东西
	for(int i = 1; i <= 3 * n; ++i)
	{
		parent[i] = i;
		sz[i] = 1;
	}
	
	int p,x,y,ans = 0;
	for(int i = 1; i <= k; ++i)
	{
		cin >> p >> x >> y;
		if(x > n || y > n)
		{
			++ans;
			continue;
		}
		if(p == 1)
		{
            //如果 x eat y 或 x == y 或 y eat x
			if(findfa(x + n) == findfa(y) || findfa(x) == findfa(y + n))
			{
				++ans;
				continue;
			}
			
			merge(x,y);             //x == y
			merge(x + n,y + n);     //x的eat的东西 == y的eat的东西
			merge(x + 2 * n,y + 2 * n);     //吃x的东西 == 吃y的东西
		}
		else if(p == 2)
		{
			//如果 x eat y 或 x == y 或 y eat x
			if(x == y || findfa(x) == findfa(y) || findfa(y + n) == findfa(x))
			{
				++ans;
				continue;
			}
			merge(x + n,y);         //x eat y
			merge(x,y + 2 * n);     //x == 吃y的东西
			merge(x + 2 * n,y + n); //y的食物会吃x
		}
	}
		
	cout << ans << endl;
	return 0;
}