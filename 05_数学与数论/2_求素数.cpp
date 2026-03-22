/*
 * 用途：求素数（埃拉托斯特尼筛法）
 * 时间复杂度：O(n log log n)
 * 应用：筛出范围内所有素数
 * 方法：标记合数，保留素数
 * 参考题目：P3912 素数个数 - https://www.luogu.com.cn/problem/P3912
 */
#include<iostream>
#include<vector> 

using namespace std;

const int N = 50005;
bool vis[N];
vector<int> primes; 

//埃氏筛：预处理素数列表，标记非素数
//时间复杂度：O(n log log n)
int main()
{
	vis[0] = vis[1] = true;
    //从2开始筛选，找到素数后标记其倍数为非素数
	for(int i = 2; i < N; ++i)
	{
        //如果 i 没有被标记为非素数，则它是一个素数，加入 primes 列表
		if(vis[i] == false) primes.push_back(i);
        
		for(int j = 0; j < primes.size() && i * primes[j] < N; ++j)
		{
            //标记 i 的倍数为非素数，注意要从 i * primes[j] 开始，避免重复标记
			vis[primes[j] * i] = true;
			
            //如果 i 能被 primes[j] 整除，说明 i 的最小质因数是 primes[j]，后续的倍数会在更早的循环中被标记，所以可以直接跳出
			if(i % primes[j] == 0) break;
		}
	}
	
	
	return 0;
}