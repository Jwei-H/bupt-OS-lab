#ifndef FIFO_H
#define FIFO_H

#include <queue> // 引入队列容器
#include <set>   // 引入集合容器（用于记录内存中的页面）

// FIFO算法实现函数
int FIFO(std::queue<int> q, int size)
{
    int hit_count = 0;                             // 命中次数计数器
    std::set<int> memory;                          // 内存中的页面集合，用于记录当前内存中存储了哪些页面
    std::queue<int> fifo_memory;                   // FIFO算法中使用的辅助队列，用于记录页面进入内存的顺序

    // 遍历页面访问序列
    while (!q.empty())
    {
        int page = q.front() / 10;                 // 提取当前访问的页面号
        q.pop();                                   // 弹出已处理的页面访问事件

        // 如果页面已存在于内存中，增加命中次数并继续下一次页面访问
        if (memory.find(page) != memory.end())
        {
            hit_count++;                           // 命中次数加一
            continue;                              // 继续下一次页面访问
        }

        // 如果内存未满，将页面加入内存中
        if (memory.size() < size)
        {
            memory.insert(page);                   // 将页面加入内存中
            fifo_memory.push(page);                // 将页面加入FIFO算法的辅助队列中，记录页面的进入顺序
        }
        else // 如果内存已满，需要进行页面置换
        {
            int evicted_page = fifo_memory.front();      // 获取FIFO算法中最早进入内存的页面
            fifo_memory.pop();                           // 将最早进入内存的页面从FIFO辅助队列中移除
            memory.erase(evicted_page);                  // 将最早进入内存的页面从内存中移除
            memory.insert(page);                         // 将当前页面加入内存中
            fifo_memory.push(page);                      // 将当前页面加入FIFO算法的辅助队列中，记录页面的进入顺序
        }
    }

    return hit_count;  // 返回命中次数
}

#endif // FIFO_H
