/*
 * 用途：字典树（Trie）基础
 * 时间复杂度：O(len)
 * 应用：字符串存储与查询
 * 方法：利用公共前缀减少存储空间
 * 参考题目：P8306 【模板】字典树 / Trie - https://www.luogu.com.cn/problem/P8306
 */


#include<iostream>
#include<cstring>

using namespace std;

const int N = 3000005;  //总节点数，等于所有字符串长度之和 + 1（根节点）

int mp[200];

int tot;
int tree[N][63];        //字典树，每个节点有63条边，分别对应小写字母、大写字母和数字
int cnt[N];             //cnt[i]表示第i个节点代表的字符串出现的次数


//映射函数，将字符映射到0-62之间的整数，方便在tree数组中存储和查询
void init()
{
	for(char ch = 'a'; ch <= 'z'; ++ch) mp[ch] = ch - 'a';
	
	for(char ch = 'A'; ch <= 'Z'; ++ch) mp[ch] = ch - 'A' + 26;
	
	for(char ch = '0'; ch <= '9'; ++ch) mp[ch] = ch - '0' + 52;
	
//	for(char ch = 'a'; ch <= 'z'; ++ch) cout << mp[ch] << ' ';
//	cout << endl;
//	for(char ch = 'A'; ch <= 'Z'; ++ch) cout << mp[ch] << ' ';
//	cout << endl;
//	for(char ch = '0'; ch <= '9'; ++ch) cout << mp[ch] << ' ';
//	cout << endl;
	
	return ;
}

//插入字符串s到字典树中，并将代表字符串s的节点的cnt值加1
void insert(const string& s)
{
	int p = 0;
	
	for(int i = 0; i < s.length(); ++i)
	{
		int id = mp[s[i]];
        //如果当前节点p没有id这条边，那么就创建一个新节点，并将p的id这条边指向新节点
		if(tree[p][id] == 0) tree[p][id] = ++tot;
		p = tree[p][id];
		++cnt[p];   //代表字符串s的节点的cnt值加1
	}
	
	return ;
}

//查询字符串s在字典树中出现的次数，如果s在字典树中不存在，那么就返回0
int query(const string& s)
{
	int p = 0;
	
	for(int i = 0; i < s.length(); ++i)
	{
		int id= mp[s[i]];
		p = tree[p][id];        //如果当前节点p没有id这条边，那么就说明字符串s在字典树中不存在，直接返回0
		if(p == 0 || cnt[p] == 0) return 0;
	}
	
	return cnt[p];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	init();
	
	int T,n,q;
	string s;
	
	cin >> T;
	while(T-- > 0)
	{
		cin >> n >> q;
		for(int i = 1; i <= n; ++i)
		{
			cin >> s;
			insert(s);
		}
		
		while(q-- > 0)
		{
			cin >> s;	
			cout << query(s) << '\n';
		}
		
        //初始化tot和tree数组和cnt数组，为下一组测试数据做准备
        //清空tree数组和cnt数组时，只需要清空已经使用过的节点即可，不需要清空整个数组，这样可以节省时间
		for(int i = 0; i <= tot; ++i)
		{
			for(int j = 0; j < 63; ++j)
			{
				tree[i][j] = 0;
			}
			cnt[i] = 0;
		}
		tot = 0;
	}
	
	
	return 0;
}