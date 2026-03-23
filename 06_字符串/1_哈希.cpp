//题目链接:https://www.luogu.com.cn/problem/P3370(P3370 【模板】字符串哈希)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 使用 unsigned long long 自然溢出，相当于对 2^64 取模
typedef unsigned long long ull;

const ull P1 = 131;
const ull P2 = 13331;

struct HashVal 
{
    ull h1, h2;
    // 重载比较运算符，方便放入 set 或 sort
    bool operator<(const HashVal& o) const 
    {
        if (h1 != o.h1) return h1 < o.h1;
        return h2 < o.h2;
    }
};

struct StringHash 
{
    vector<ull> h1, h2, p1, p2;

    // 预处理：构建前缀哈希数组
    StringHash(const string& s) 
    {
        int n = s.size();
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        
        for (int i = 0; i < n; ++i) 
        {
            h1[i + 1] = h1[i] * P1 + s[i];
            h2[i + 1] = h2[i] * P2 + s[i];
            p1[i + 1] = p1[i] * P1;
            p2[i + 1] = p2[i] * P2;
        }
    }

    // O(1) 获取子串 [l, r] 的哈希值 (l, r 从 1 开始)
    HashVal get(int l, int r) 
    {
        ull res1 = h1[r] - h1[l - 1] * p1[r - l + 1];
        ull res2 = h2[r] - h2[l - 1] * p2[r - l + 1];
        return {res1, res2};
    }
};