/*
 * 用途：单调栈的基本操作与应用（最大矩形问题）
 * 时间复杂度：O(n*m)，每个元素最多进栈和出栈各一次
 * 常用方法：push、pop、top、empty、size
 * 应用场景：找最大矩形、求下一个更大元素、历史最大值等
 * 输入：n行m列的矩阵，'F'表示水，其他表示陆地
 * 输出：最大水域矩形面积的3倍
 * 题目链接：https://www.luogu.com.cn/problem/P4147
 */
#include<iostream>
#include<stack>

using namespace std;

const int N = 1005;

int n,m;
int h[N];
char ap[N][N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            cin >> ap[i][j];
        }
    }

    stack<int> st;
    int ans = 0;
    
    for(int i = 1; i <= n; ++i)
    {
        //对于每一行单调栈
        for(int j = 1; j <= m; ++j) 
        {
            if(ap[i][j] == 'F') ++h[j];
            else h[j] = 0;
        }

        //m + 1是为了让栈中的元素都能被弹出，计算面积
        for(int j = 1; j <= m + 1; ++j)
        {
            //如果栈为空，或者栈不满足不单调递减了
            while(st.empty() == false && h[st.top()] > h[j])
            {
                int height = h[st.top()];
                st.pop();  

                //如果栈为空那么height就是遍历过最小的高度
                //如果不为空那么左边界就是栈顶元素，右边界就是当前元素j
                //那么宽度就是r - l + 1 - 2 = r - l - 1
                int width = st.empty() == true ? j - 1 : j - st.top() - 1;
                //计算面积
                ans = max(ans,height * width);
            }
            st.push(j);   
        }
        while(st.empty() == false) st.pop();   //清空栈，为下一行做准备
    }
    
    cout << 3 * ans << endl;

    return 0;
}