#include<iostream>

using namespace std;


//__int128是GCC和Clang编译器提供的一个扩展类型，表示一个128位的整数，可以存储非常大的整数值，范围大约在-2^127到2^127-1之间。
//它通常用于需要处理大整数的场景，比如大数运算、加密算法等。
//需要自己写print函数，其他用法和普通整数一样
void print(__int128 x)
{
    if(x < 10)
    {
        cout << int(x);
        return ;
    }

    print(x / 10);
    cout << int(x % 10);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    __int128 a, b;
    long long x;
    cin >> x;
    a = x;
    cin >> x;
    b = x;  

    print(a + b);



    return 0;
}