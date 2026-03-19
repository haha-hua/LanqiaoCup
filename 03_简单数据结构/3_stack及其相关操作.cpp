/*
 * 用途：stack（栈）的基本操作与应用
 * 时间复杂度：push, pop, top, empty, size 都是 O(1)
 * 常用方法：push, pop, top, empty, size
 * 输入：演示数据
 * 输出：栈操作结果（LIFO）
 */
#include<iostream>
#include<stack>

using namespace std;


int main()
{
    stack<int> st;  //栈，后进先出（LIFO）的数据结构，提供了push()、pop()、top()等操作，可以用来存储和操作一组数据

    st.push(1); //在栈顶添加元素1
    st.push(2); //在栈顶添加元素2，栈现在是{1,2}，2在顶端
    st.top(); //访问栈顶元素，返回2，但不删除
    st.pop(); //删除栈顶元素，栈现在是{1}，2被删除
    st.empty(); //判断栈是否为空，返回false
    st.size(); //返回栈中元素的个数，返回1



    return 0;
}