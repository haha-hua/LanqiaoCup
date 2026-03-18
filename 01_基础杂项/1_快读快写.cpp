#include <bits/stdc++.h>

using namespace std;

// 快读函数：读取一个整数
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

// 快写函数：输出一个整数
inline void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    ios::sync_with_stdio(false);        // 解绑C++和C的输入输出流
    cin.tie(0);                         // 解绑cin和cout的输入输出流
    cout.tie(0);                        // 解绑cout和cin的输入输出流

    // 示例使用
    cout << "请输入一个整数：" << endl;
    int num = read();
    cout << "你输入的整数是：" << endl;
    write(num);
    putchar('\n');  // 输出换行

    return 0;
}