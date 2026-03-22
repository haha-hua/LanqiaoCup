/*
 * 用途：组合数学（组合计数）
 * 时间复杂度：O(n^2) 预处理，O(1) 查询
 * 应用：计算组合数 C(n,m)，含模运算
 * 方法：杨辉三角 / 阶乘预处理
 * 参考题目：YBT 1650 组合 - https://ybt.ssoier.cn/problem_show.php?pid=1650
 */

#include<iostream>

using namespace std;

const int P = 1e9 + 7;
const int N = 200005;
using ll = long long;

//递推求解组合数 C(n,m) = C(n-1,m-1) + C(n-1,m)，边界条件 C(n,0) = C(n,n) = 1
//时间复杂度 O(n^2)，适合 n 较小的情况
int c[2005][2005];

//预处理阶乘和逆元阶乘，使用快速幂计算逆元，时间复杂度 O(n log P)
ll fact[N], infact[N];

ll quickPow(ll a,ll n)
{
	ll sum = 1;
	a %= P;
	while(n)
	{
		if(n & 1) sum = sum * a  % P;
		a = a * a % P;
		n >>= 1;
	}
	return sum;
}

void init()
{
	fact[0] = 1;
	for(int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % P;
	
	infact[N - 1] = quickPow(fact[N - 1],P - 2);
	
	for(int i = N - 2; i >= 0; --i) infact[i] = infact[i + 1] * (i + 1) % P;
	
	return ;
}

ll getC(int n,int m)
{
	return fact[n] * infact[m] % P * infact[n - m] % P;
}

int main()
{
	int n = 100;
	
    //初始化
	c[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
        //边界条件 C(n,0) = 1
		c[i][0] = 1;
		for(int j = 1; j <= i; ++j)
		{
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P;
		}
	}
	
	
	
	return 0;
}