/*
 * 用途：vector（动态数组）的基本操作与应用
 * 时间复杂度：访问 O(1)，尾部插入/删除 O(1) 均摊，中间操作 O(n)
 * 常用方法：push_back, pop_back, size, clear, erase, insert, begin, end
 * 输入：演示数据
 * 输出：各种操作的结果
 */
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main()
{
    //vector<int> arr;  //动态数组，初始大小为0，可以根据需要自动调整大小，就是普通数组的升级版，提供了很多方便的函数，比如push_back()、size()、clear()等，可以用来存储和操作一组数据


    vector<int> arr(5);  //初始化大小为5，元素默认值为0，可以通过下标访问和修改元素，比如arr[0] = 1; arr[1] = 2;等

    //元素访问
    arr[0] = 1;
    arr.front() = 1;  //访问第一个元素，等价于arr[0]
    arr.back() = 5;   //访问最后一个元素，等价于arr[arr.size() - 1]

    //容量相关

    arr.size();  //返回当前元素个数
    arr.empty(); //判断是否为空
    arr.clear(); //清空所有元素，size变为0，但capacity不变
    arr.reserve(10); //预留至少10个元素的空间，capacity变为至少10，但size不变,可以减少后续添加元素时的内存重新分配次数，提高效率

    //迭代器
    vector<int>::iterator it = arr.begin(); //返回指向第一个元素的迭代器
    vector<int>::iterator it_end = arr.end(); //返回指向最后一个元素后一个位置的迭代器

    for(it = arr.begin(); it != arr.end(); ++it) //使用迭代器遍历元素
    {
        cout << *it << " "; //通过解引用访问元素值
    }

    //配合algorithm算法
    sort(arr.begin(), arr.end()); //对元素进行排序，使用默认的升序排序，可以传入自定义的比较函数来实现其他排序方式
    upper_bound(arr.begin(), arr.end(), 3); //返回第一个大于3的元素的位置，前提是arr已经排序
    //1，2，3，4，5  upper_bound返回4的位置
    lower_bound(arr.begin(), arr.end(), 3); //返回第一个不小于3的元素的位置，前提是arr已经排序
    //1，2，3，4，5  lower_bound返回3的位置
    //去重
    sort(arr.begin(), arr.end()); //先排序
    arr.erase(unique(arr.begin(), arr.end()), arr.end()); //unique将相邻的重复元素移到末尾，并返回新末尾的迭代器，erase删除末尾的重复元素

    return 0;
}