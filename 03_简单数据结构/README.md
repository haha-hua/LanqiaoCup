# 03_简单数据结构

本目录包含 C++ STL 中常用的基础数据结构模板与使用示例。

## 文件列表与解析

- [1_vector及其相关操作.cpp](03_简单数据结构/1_vector及其相关操作.cpp)
  - 描述：动态数组 vector 的初始化、访问、插入、删除、遍历等基本操作。
  - 时间复杂度：访问 O(1)，尾部插入/删除 O(1) 均摊，中间操作 O(n)。
  - 常用方法：push_back、pop_back、size、clear、erase、insert 等。

- [2_list及其数组模拟链表.cpp](03_简单数据结构/2_list及其数组模拟链表.cpp)
  - 描述：双向链表 list 的实现与数组模拟链表（静态链表）两种方式。
  - 时间复杂度：访问 O(n)，中间插入/删除 O(1)（已定位）。
  - 使用场景：需要频繁在中间插入/删除且不需要随机访问时。

- [3_stack及其相关操作.cpp](03_简单数据结构/3_stack及其相关操作.cpp)
  - 描述：栈（后进先出）的基本操作：push、pop、top、empty、size 等。
  - 时间复杂度：所有操作 O(1)。
  - 应用场景：括号匹配、表达式求值、回溯问题等。

- [4_queue和deque和priority_queue的操作.cpp](03_简单数据结构/4_queue和deque和priority_queue的操作.cpp)
  - 描述：队列（先进先出）、双端队列、优先队列的使用方法。
  - 时间复杂度：queue 和 deque 基本操作 O(1)；priority_queue 插入/删除 O(log n)。
  - 使用场景：BFS、任务调度、Huffman 编码等。

- [5_map和unordered_map和multimap的操作.cpp](03_简单数据结构/5_map和unordered_map和multimap的操作.cpp)
  - 描述：有序映射（map）、哈希映射（unordered_map）、多值映射（multimap）的用法。
  - 时间复杂度：map 查询/插入/删除 O(log n)；unordered_map 平均 O(1)，最坏 O(n)。
  - 使用场景：键值对存储、计数、快速查询等。

- [6_set和multiset的操作.cpp](03_简单数据结构/6_set和multiset的操作.cpp)
  - 描述：有序集合（set）、多值集合（multiset）的初始化、查询、插入、删除等操作。
  - 时间复杂度：查询/插入/删除 O(log n)。
  - 使用场景：去重、排序、快速查询最小/最大值等。

- [7_bitset的相关操作.cpp](03_简单数据结构/7_bitset的相关操作.cpp)
  - 描述：位集合 bitset 的初始化、位操作（AND、OR、XOR、翻转等）与应用。
  - 时间复杂度：各种位操作基本为 O(n) 或 O(n/64)。
  - 使用场景：状态压缩、素数筛选、快速布尔数组存储等。

## 贡献与规范

- 新增文件：请使用数字前缀保持排序（例如 `8_xxx.cpp`）。
- 文件头：建议在每个文件顶部写明用途、操作复杂度、常用方法及应用场景。
- 提交规范：PR 请描述修改点、添加示例代码与使用说明。
