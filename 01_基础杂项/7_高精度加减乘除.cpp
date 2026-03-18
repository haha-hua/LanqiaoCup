#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

using ll = long long;


const ll BASE = 1e9;    //每个元素存储9位数字，这样可以减少数组的长度，提高效率
class BigInt
{
private:
	vector<ll> d;
	
    //去除前导零，保持数值的正确性和简洁性
	void clean()
	{
		while(d.size() > 1 && d.back() == 0) d.pop_back();
	}
	
public:
	
    //初始化
	BigInt(ll x)
	{
		if(x == 0) d.push_back(0);
		while(x)
		{
			d.push_back(x % BASE);
			x /= BASE;
		}
		
	}
		
	BigInt()
	{
		d.push_back(0);
	}
	
    //加法
	void add(const BigInt& other)
	{
        //先将当前数和other的差分数组对齐;
        //如果当前数的差分数组长度小于other的差分数组长度
        //就在当前数的差分数组末尾补0，直到两者长度相同
		while(d.size() < other.d.size()) d.push_back(0);
		for(int i = 0; i < other.d.size(); ++i) d[i] += other.d[i];
		
        //处理进位：从低位到高位，如果某一位的值大于等于BASE，就将该位减去BASE，并将进位加到下一位
		ll res = 0;
		for(int i = 0; i < d.size(); ++i)
		{
			d[i] += res;
			res = d[i] / BASE;
			d[i] %= BASE;
		}
		
		while(res)
		{
			d.push_back(res % BASE);
			res /= BASE;
		}
		
		return ;
	}
	
    //乘法
	void multi(const ll& k)
	{
		if(k == 0)
		{
			d.clear();
			d.push_back(0);
			return ;
		}

		ll res = 0;
		for(int i = 0; i < d.size(); ++i)
		{
			d[i] = d[i] * k + res;
			res = d[i] / BASE;
			d[i] %= BASE;
		}
		
		while(res)
		{
			d.push_back(res % BASE);
			res /= BASE;
		}
		
		return ;
	}
	
    //减法，保证大数减小数，结果非负
	void subtra(const BigInt& other)
	{
		for(int i = 0; i < other.d.size(); ++i) d[i] -= other.d[i];
		
		for(int i = 0; i < d.size(); ++i)
		{
			if(d[i] < 0)
			{
				d[i] += BASE;
				--d[i + 1];
			}
		}
		
		clean();
		
		return ;
	}
	
    //除法
	void division(const ll& k)
	{
		ll res = 0;
		for(int i = d.size() - 1; i >= 0; --i)
		{
			ll cur = (d[i] + res * BASE);
			d[i] = cur / k;
			res = cur % k;
		}
		
		clean();
		
		return ;
	}
	
	void print()
	{
		cout << d.back();
        //输出高位，注意高位可能不足9位，所以需要使用setfill和setw来补零
		for(int i = d.size() - 2; i >= 0; --i) cout << setfill('0') << setw(9) << d[i];
		cout << endl;
		return ;
	}
	
};


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	BigInt a(1);
	BigInt b(2);
	
	a.add(b);
	a.print();
	a.subtra(b);
	a.print();
	a.multi(3);
	a.print();
	a.division(2);
	a.print();
	
	return 0;
} 