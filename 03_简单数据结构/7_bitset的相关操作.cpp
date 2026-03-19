/*
 * 用途：bitset（位集合）的初始化、位操作与应用
 * 时间复杂度：各种位操作 O(n) 或 O(n/64)，比 bool 数组更高效
 * 常用操作：[]访问、set/reset/flip、count、any/none、to_string、to_ulong
 * 应用场景：状态压缩、素数筛选、快速布尔存储等
 * 输入：演示数据
 * 输出：位操作结果
 */
#include<iostream>
#include<bitset>

using namespace std;


int main()
{
    //初始化
    bitset<8> b1; //默认构造函数，创建一个全0的bitset，大小为8
    bitset<8> b2(5); //用整数5初始化bitset，二进制表示为00000101
    bitset<8> b3("10101010"); //用字符串初始化bitset

    //位操作
    b1.set(0); //将第0位设置为1，b1现在是00000001
    b1.set(3); //将第3位设置为1，b1现在是00001001
    b1.reset(0); //将第0位重置为0，b1现在是00001000
    b1.flip(3); //将第3位取反，b1现在是00000000
    b1.test(3); //测试第3位是否为1，返回false

    b1.flip(); //将所有位取反，b1现在是11111111
    b1.count(); //返回bitset中1的个数，返回8
    b1.size(); //返回bitset的大小，返回8
    b1.to_string(); //将bitset转换为字符串，返回"11111111"

    //支持所有的位运算
    bitset<8> b4 = b2 & b3; //按位与，b4现在是00000000
    bitset<8> b5 = b2 | b3; //按位或，b5现在是10101010
    bitset<8> b6 = b2 ^ b3; //按位异或，b6现在是10101010

    cout << b1 << endl; //输出bitset，输出11111111
    cout << b4 << endl; //输出bitset，输出00000000
    cout << b5 << endl; //输出bitset，输出10101010
    cout << b6 << endl; //输出bitset，输出10101010

    return 0;
}