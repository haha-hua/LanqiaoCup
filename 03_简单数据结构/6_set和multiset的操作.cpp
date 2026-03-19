/*
 * 用途：set（有序集合）与 multiset（多值集合）的基本操作
 * 时间复杂度：查询/插入/删除 O(log n)；自动按升序排序
 * 常用方法：insert, erase, find, count, begin, end, lower_bound, upper_bound
 * 输入：元素数据
 * 输出：集合操作结果
 */
#include<iostream>
#include<set>

using namespace std;

int main()
{   
    set<int> s;  //集合，存储唯一元素的有序容器，提供了insert()、erase()、find()等操作，可以用来存储和操作一组数据

    s.insert(1); //在集合中添加元素1
    s.insert(2); //在集合中添加元素2，集合现在是{1,2}，1在前面
    s.find(1); //在集合中查找元素1，返回一个迭代器指向元素1，如果元素1不存在，那么就返回s.end()
    s.erase(1); //在集合中删除元素1，如果元素1不存在，那么就不会删除

    s.size(); //返回集合中元素的个数，返回1
    s.empty(); //判断集合是否为空，返回false


    multiset<int> ms;  //多重集合，存储元素的有序容器，允许重复元素，提供了insert()、erase()、find()等操作，可以用来存储和操作一组数据

    ms.insert(1); //在多重集合中添加元素1
    ms.insert(1); //在多重集合中添加元素1，集合现在是{1,1}，两个1都在前面
    ms.find(1); //在多重集合中查找元素1，返回一个迭代器指向第一个元素1，如果元素1不存在，那么就返回ms.end()
    ms.erase(1); //在多重集合中删除元素1，删除所有元素1，如果元素1不存在，那么就不会删除

    ms.size(); //返回多重集合中元素的个数，返回0
    ms.empty(); //判断多重集合是否为空，返回true


    return 0;
}