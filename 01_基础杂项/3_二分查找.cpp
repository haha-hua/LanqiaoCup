#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100005;

int n,c;
int x[N];

//这里就是检查当前的值是否满足条件，有两个结果true和false
//但是!!有些题目的二分的check可以是一个数值或者说是三个数(-1,0,1)
bool check(int s)
{
	int cnt = 1;
	int pre_d = x[1];
	
	for(int i = 2; i <= n; ++i)
	{
		if(x[i] - pre_d >= s)
		{
			++cnt;
			pre_d = x[i];
		}
	}
	
	return cnt >= c ? true : false;     //在这里我们也可以直接返回cnt
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> c;
	
	for(int i = 1; i <= n; ++i) cin >> x[i];
	
    //先排序，二分需要满足单调性，往左减小，往右增大，所以可以二分
	sort(x + 1,x + 1 + n);
	
	int l = 1,r = x[n];
	int ans = -1;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(check(mid) == true)  
		{
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	
	cout << (ans == -1 ? 0 : ans) << endl;
	return 0;
}