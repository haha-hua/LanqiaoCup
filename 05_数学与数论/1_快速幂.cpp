/*
 * 用途：快速幂（快速幂取模）
 * 时间复杂度：O(log b)
 * 应用：计算 a^b mod m，处理大数幂运算
 * 方法：二进制拆分，递推计算
 * 参考题目：YBT 1616 A 的 B 次方 - https://ybt.ssoier.cn/problem_show.php?pid=1616
 */
#include<iostream>


using namespace std;

using ll = long long;

ll a,b,m;

//快速幂：计算 a^n mod m，使用二分法将指数 n 分解为二进制形式，减少乘法次数，提高效率
//时间复杂度：O(log n)
ll quickPow(ll a,ll n)
{
	ll sum = 1;
	a %= m;
	
	while(n)
	{
		if(n & 1) sum = sum * a % m;
		a = a * a % m;
		n >>= 1;
	}
	return sum;
}

int main()
{
	
	cin >> a >> b >> m;
	cout << quickPow(a,b) << endl;
	
	return 0;
}