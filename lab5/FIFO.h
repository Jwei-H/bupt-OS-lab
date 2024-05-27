#ifndef FIFO_H
#define FIFO_H

#include <queue> // 引入队列容器
#include <set>   // 引入集合容器（用于记录内存中的页面）

// FIFO算法实现函数
// 参数：
//   q: 存储页面访问序列的队列
//   size: 内存中可以存储的页面数量
//   hit_rate: 用于存储命中率
// 返回值：
//   返回命中次数（即页面在内存中已存在时的访问次数）
int FIFO(std::queue<int> q, int size)
{
    double hit_rate;
    int hit_count = 0;    // 命中次数计数器
    int total_count = 0;  // 总的访问次数计数器
    std::set<int> memory; // 内存中的页面集合，用于记录当前内存中存储了哪些页面

    // 遍历页面访问序列
    while (!q.empty())
    {
        int page = q.front() / 10; // 提取当前访问的页面号
        q.pop();                   // 弹出已处理的页面访问事件
        total_count++;             // 增加总的访问次数

        // 如果页面已存在于内存中，增加命中次数并继续下一次页面访问
        if (memory.find(page) != memory.end())
        {
            hit_count++; // 命中次数加一
            continue;    // 继续下一次页面访问
        }

        // 如果内存未满，将页面加入内存中
        if (memory.size() < size)
        {
            memory.insert(page); // 将页面加入内存中
        }
        else // 如果内存已满，需要进行页面置换
        {
            int evicted_page = *memory.begin(); // 获取FIFO算法中最先进入内存的页面
            memory.erase(evicted_page);         // 将最先进入内存的页面从内存中移除
            memory.insert(page);                // 将当前页面加入内存中
        }
    }

    // 计算命中率
    hit_rate = (double)hit_count / total_count * 100;
    return hit_count; // 返回命中次数
}

#endif // FIFO_H
