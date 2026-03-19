/*
 * 用途：对半搜索（Meet in the Middle）
 * 时间复杂度：O(2^(n/2) * log(2^(n/2))) 或 O(2^(n/2) * n)
 * 参考题目：P4799 CEOI 2015 世界冰球锦标赛 - https://www.luogu.com.cn/problem/P4799
 * 输入：集合大小 n，目标和 m
 * 输出：对半搜索能达到目标的方案
 */
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

using ll = long long;

int n;
ll m; 
vector<ll> res1,res2;       //存储前半部分和后半部分的所有子集和
ll w[50];


//分治法：将n个数分成两半，分别计算前半部分和后半部分的所有子集和，存储在res1和res2中
void dfs(int pos,int end_pos,ll sum,vector<ll>& res)
{
	if(sum > m) return ;
	if(pos == end_pos + 1)
	{
		res.push_back(sum);
		return ; 
	}
	
	dfs(pos + 1,end_pos,sum + w[pos],res);
	dfs(pos + 1,end_pos,sum,res);
	
	return ;
}

int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> w[i];
	
	dfs(1,n / 2,0,res1);            
	dfs(n / 2 + 1,n,0,res2);
	
	sort(res1.begin(),res1.end());
	sort(res2.begin(),res2.end());
	
	ll cnt = 0;
	for(int i = 0; i < res1.size(); ++i)
	{
        //对于res1中的每个元素res1[i]，我们需要在res2中找到最大的元素res2[j]，使得res1[i] + res2[j] <= m
        //这相当于在res2中寻找一个元素，使得res2[j] <= m - res1[i]
        //由于res2已经排序，我们可以使用upper_bound来找到第一个大于m - res1[i]的元素的位置，减去res2.begin()就得到了满足条件的元素个数
		cnt += upper_bound(res2.begin(),res2.end(),m - res1[i]) - res2.begin();    
        //也可以手写二分来找到这个位置，效率更高一些 
	}
	cout << cnt << endl;	
	return 0;
}