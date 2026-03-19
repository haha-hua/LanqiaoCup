/*
 * 用途：map（有序映射）、unordered_map（哈希映射）、multimap（多值映射）的基本操作
 * 时间复杂度：map 查询/插入/删除 O(log n)；unordered_map 平均 O(1) 最坏 O(n)；multimap 同 map
 * 常用方法：insert, find, erase, count, [], at, begin, end
 * 输入：键值对数据
 * 输出：映射操作结果
 */
#include<map>
#include<unordered_map>

using namespace std;


int main()
{
    map<int,int> mp;
    //map是红黑树实现的有序关联容器，提供了键值对的存储和操作，按照键的顺序进行存储和访问。

    mp.emplace(1, 100); //在map中添加键值对(1,100)，如果键1已经存在，那么就不会添加
    mp[2] = 200; //在map中添加键值对(2,200)，如果键2已经存在，那么就会更新它的值为200

    //时间复杂度：O(log n)
    mp.find(1); //在map中查找键1，返回一个迭代器指向键值对(1,100)，如果键1不存在，那么就返回mp.end()

    mp.erase(1); //在map中删除键1，时间复杂度为O(log n)，如果键1不存在，那么就不会删除


    unordered_map<int,int> ump;
    //unordered_map是哈希表实现的无序关联容器

    ump.emplace(1, 100); //在unordered_map中添加键值对(1,100)，如果键1已经存在，那么就不会添加
    ump[2] = 200; //在unordered_map中添加键值对(2,200)，如果键2已经存在，那么就会更新它的值为200

    //时间复杂度：平均O(1)，最坏O(n)
    ump.find(1); //在unordered_map中查找键1，返回一个迭代器指向键值对(1,100)，如果键1不存在，那么就返回ump.end()

    ump.erase(1); //在unordered_map中删除键1，平均时间复杂度为O(1)，最坏时间复杂度为O(n)，如果键1不存在，那么就不会删除


    multimap<int,int> mmp;
    //multimap是红黑树实现的有序关联容器，提供了键值对的存储和操作，按照键的顺序进行存储和访问，但是允许键重复。

    mmp.emplace(1, 100); //在multimap中添加键值对(1,100)，即使键1已经存在，也会添加一个新的键值对(1,100)
    mmp.emplace(1, 200); //在multimap中添加键值对(1,200)，即使键1已经存在，也会添加一个新的键值对(1,200)

    //时间复杂度：O(log n)
    mmp.find(1); //在multimap中查找键1，返回一个迭代器指向第一个键值对(1,100)，如果键1不存在，那么就返回mmp.end()
    mmp.erase(1); //在multimap中删除键1，时间复杂度为O(log n)，会删除所有键为1的键值对，如果键1不存在，那么就不会删除

    return 0;
}