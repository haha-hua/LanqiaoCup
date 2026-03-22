/*
 * 用途：状态压缩 DP（几何/骨牌覆盖）
 * 时间复杂度：O(n * m * 2^m)
 * 应用：骨牌铺设、网格覆盖等问题
 * DP 定义：dp[列][状态] = 前 i 列已铺设，第 i 列状态为 state 的方案数
 * 状态转移：枚举当前列状态，检查与前一列的兼容性
 */
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

long long dp[12][1 << 11]; // dp[列][状态]
bool st[1 << 11];          // 存储状态是否合法（连续0为偶数）
vector<int> head[1 << 11]; // 存储每个状态的合法前驱状态
int n, m;

int main()
{
    while (cin >> n >> m && (n || m))
    {
        // 1. 预处理当前列合法的空隙状态
        for (int i = 0; i < (1 << n); i++)
        {
            int cnt = 0; // 记录连续 0 的个数
            bool isValid = true;
            for (int j = 0; j < n; j++)
            {
                if ((i >> j) & 1)
                {
                    if (cnt & 1)
                    {
                        isValid = false;
                        break;
                    } // 奇数个0，寄了
                    cnt = 0;
                }
                else
                    cnt++;
            }
            if (cnt & 1)
                isValid = false;
            st[i] = isValid;
        }

        // 2. 预处理状态之间的转移关系
        for (int i = 0; i < (1 << n); i++)
        {
            head[i].clear();
            for (int j = 0; j < (1 << n); j++)
            {
                if ((i & j) == 0 && st[i | j])
                {
                    head[i].push_back(j);
                }
            }
        }

        // 3. DP过程
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1; // 初始状态：第0列前面没有伸过来的，方案数为1

        for (int i = 1; i <= m; i++)
        { // 遍历列
            for (int j = 0; j < (1 << n); j++)
            { // 遍历当前列状态
                for (int pre : head[j])
                { // 遍历所有合法的前驱状态
                    dp[i][j] += dp[i - 1][pre];
                }
            }
        }

        // 结果：第 m 列没有伸向 m+1 列的方块
        cout << dp[m][0] << endl;
    }
    return 0;
}