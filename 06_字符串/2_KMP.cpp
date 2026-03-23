//题目链接:https://www.luogu.com.cn/problem/P3375(P3375 【模板】KMP)

#include<iostream>
#include<vector>

using namespace std;

string s1,s2;
vector<int> res;

int nxt[1000005];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> s1 >> s2;
	

	nxt[0] = 0;
	//i是位置,j是已经匹配的长度
    for(int i = 1,j = 0; i < s2.length(); ++i)
	{
		while(j && s2[i] != s2[j]) j = nxt[j - 1];  //如果不匹配，回退到上一个匹配位置,j - 1就是位置
		if(s2[i] == s2[j]) ++j;
		nxt[i] = j;
	}
	
	//i是位置,j是已经匹配的长度
	for(int i = 0,j = 0; i < s1.length(); ++i)
	{
		while(j && s1[i] != s2[j]) j = nxt[j - 1];
		//如果匹配，++j,j就表示已经匹配的长度了
        if(s1[i] == s2[j]) ++j;
		if(j == s2.length())
		{
			res.push_back(i - s2.length() + 1);
			j = nxt[j - 1];//j - 1表示位置，j表示长度，所以j - 1就是位置
		}
	}
	
	for(int val : res) cout << val + 1 << '\n';         //输出位置，题目要求从1开始，所以+1
	for(int i = 0; i < s2.length(); ++i) cout << nxt[i] << ' ';
	cout << '\n';
	return 0;
}