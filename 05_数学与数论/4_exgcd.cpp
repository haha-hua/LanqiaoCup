/*
 * 用途：扩展欧几里得算法（解线性丢番图方程）
 * 时间复杂度：O(log min(a,b))
 * 应用：求 ax + by = gcd(a,b) 的整数解、模逆元计算
 * 方法：递推追踪 gcd 过程中的系数
 * 参考题目：YBT 1632 同余方程 - https://ybt.ssoier.cn/problem_show.php?pid=1632
 */
#include<iostream>

using namespace std;

int exgcd(int a,int b,int& x,int& y)
{
	if(b == 0)
	{
		x = 1,y = 0;
		return a;
	}
	
	int x1,y1,d;
	d = exgcd(b,a % b,x1,y1);
	
	x = y1;
	y = x1 - (a / b) * y1;
	return d;
}

int main()
{
	//to solve ax + by = gcd(a,b)   x = ?,y = ?     
    //这个是裴蜀定理: ax + by = gcd(a,b) 有整数解当且仅当 gcd(a,b) 能整除 c(即c % gcd(a,b) == 0)
    //其中 c 是等式右边的常数项，在这里是 gcd(a,b) 本身，所以一定有解
	
	int a,b;
	int x0,y0,d;
	
	
	d = exgcd(a,b,x0,y0);
	
	cout << "gcd = " << d << endl;
    cout << "x = " << x0 << ", y = " << y0 << endl;
	
	return 0;
}