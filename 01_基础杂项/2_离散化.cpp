#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * 离散化模板 (Discretization)
 * 适用场景：值域大(10^9)但个数少(10^5)，需要将值映射为 1~m 的连续整数。
 */

// 1. 定义存储离散化数值的容器
vector<int> all_values;

// 2. 离散化预处理函数
// 时间复杂度：O(N log N)
void discretize() 
{
    // a. 排序：为了去重和后续二分查找
    sort(all_values.begin(), all_values.end());
    
    // b. 去重：unique 把重复项移到末尾并返回新终点迭代器，erase 将其物理删除
    all_values.erase(unique(all_values.begin(), all_values.end()), all_values.end());
}

// 3. 查询原值映射后的排名 (1-indexed)
// 时间复杂度：O(log N)
int get_rank(int x) 
{
    // lower_bound 返回第一个大于等于 x 的位置
    return lower_bound(all_values.begin(), all_values.end(), x) - all_values.begin() + 1;
}

// 4. 根据排名查回原值
int get_val(int rank) 
{
    return all_values[rank - 1];
}


int main() 
{
    int n = 5;
    int arr[] = {100, 50, 1000000, 50, 200}; // 原始数据
    
    // a. 将所有需要离散化的值加入容器
    for(int i = 0; i < n; i++) {
        all_values.push_back(arr[i]);
    }
    
    // b. 执行离散化
    discretize();
    
    // c. 输出映射结果
    // 映射后：50->1, 100->2, 200->3, 1000000->4
    cout << "Value Mapping Result:" << endl;
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " -> " << get_rank(arr[i]) << endl;
    }
    
    // d. 查回原值示例
    cout << "Rank 4 is: " << get_val(4) << endl; // 应输出 1000000

    return 0;
}