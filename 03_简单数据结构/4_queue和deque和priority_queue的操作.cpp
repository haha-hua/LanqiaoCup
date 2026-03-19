/*
 * 用途：queue（队列）、deque（双端队列）、priority_queue（优先队列）的基本操作
 * 时间复杂度：queue/deque 基本操作 O(1)；priority_queue push/pop O(log n)
 * 常用方法：push, pop, front, back, empty, size （优先队列支持自定义比较器）
 * 输入：演示数据
 * 输出：队列操作结果
 */
#include<iostream>
#include<queue>
#include<deque>

using namespace std;

int main()
{   
    queue<int> que;  //队列，先进先出（FIFO）的数据结构，提供了push()、pop()、front()、back()等操作，可以用来存储和操作一组数据
    que.push(1); //在队尾添加元素1
    que.push(2); //在队尾添加元素2，队列现在是{1,2}，1在前面
    que.front(); //访问队首元素，返回1，但不删除
    que.pop(); //删除队首元素，队列现在是{2}，1被删除
    que.empty(); //判断队列是否为空，返回false
    que.size(); //返回队列中元素的个数，返回1

    deque<int> deq;  //双端队列，既可以在两端添加和删除元素的队列，提供了push_back()、push_front()、pop_back()、pop_front()、front()、back()等操作，可以用来存储和操作一组数据
    deq.push_back(1); //在队尾添加元素1
    deq.push_front(0); //在队首添加元素0，队列现在是{0,1}，0在前面
    deq.front(); //访问队首元素，返回0，但不删除
    deq.back(); //访问队尾元素，返回1，但不删除
    deq.pop_back(); //删除队尾元素，队列现在是{0}，1被删除
    deq.pop_front(); //删除队首元素，队列现在是空的{}，0被删除
    deq.empty(); //判断双端队列是否为空，返回true
    deq.size(); //返回双端队列中元素的个数，返回0

    priority_queue<int,vector<int>,greater<int>> pq; 
    //优先队列，按照元素的优先级来访问和删除元素的队列
    //提供了push()、pop()、top()等操作，可以用来存储和操作一组数据，默认是大根堆
    //如果需要小根堆可以传入greater<int>作为第三个模板参数

    pq.push(2); //在优先队列中添加元素2
    pq.push(1); //在优先队列中添加元素1，优先队列现在是{1,2}，1在前面
    pq.top(); //访问优先队列中优先级最高的元素，返回1，但不删除
    pq.pop(); //删除优先队列中优先级最高的元素，优先队列现在是{2}，1被删除
    pq.empty(); //判断优先队列是否为空，返回false
    pq.size(); //返回优先队列中元素的个数，返回1


    return 0;
}