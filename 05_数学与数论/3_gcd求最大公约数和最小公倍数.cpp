/*
 * 用途：最大公约数和最小公倍数（欧几里得算法）
 * 时间复杂度：O(log min(a,b))
 * 应用：gcd 和 lcm 计算
 * 方法：辗转相除法
 * 参考题目：YBT 1627 最大公约数 - https://ybt.ssoier.cn/problem_show.php?pid=1627
 */
#include<iostream>
#include<algorithm>

using namespace std;

int gcd(int a,int b)
{
	if(b == 0) return a;
	return gcd(b, a % b);
} 

int main()
{
    //C++17 标准库提供了 __gcd 函数，可以直接使用来计算两个数的最大公约数
	cout << __gcd(2,4) << endl;	
	
    //手写 gcd 函数：使用欧几里得算法，递归地计算 a 和 b 的最大公约数，时间复杂度为 O(log(min(a,b)))
	cout << gcd(2,4) << endl;
	
	//如果出现a,b都是为高精度数的情况
    //用Stein算法（Binary GCD Algorithm）来计算最大公约数，效率更高一些，时间复杂度也是 O(log(min(a,b)))
	
    //1.当a,b都是偶数时，gcd(a,b) = 2 * gcd(a/2, b/2)
    //2.当a是偶数，b是奇数时，gcd(a,b) = gcd(a/2, b)
    //3.当a是奇数，b是偶数时，gcd(a,b) = gcd(a, b/2)
    //4.当a,b都是奇数时，gcd(a,b) = gcd(|a-b|/2, min(a,b))
    //5.当a或b为0时，gcd(a,b) = max(a,b)



    //最小公倍数LCM(a,b) = a * b / GCD(a,b)
    //可以通过最大公约数来计算最小公倍数，时间复杂度为 O(log(min(a,b)))
    cout << 2 * 4 / __gcd(2,4) << endl; //使用标准库函数计算最小公倍数
    cout << 2 * 4 / gcd(2,4) << endl; //使用手写的 gcd 函数计算最小公倍数
        
	return 0;
}