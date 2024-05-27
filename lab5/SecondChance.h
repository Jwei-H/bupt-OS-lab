#ifndef SECONDCHANCE_H
#define SECONDCHANCE_H

#include <queue> // 引入队列容器
#include <set>   // 引入集合容器（用于记录内存中的页面）

// 第二次机会算法实现函数
int SecondChance(std::queue<int> q, int size)
{
    double hit_rate;
    int hit_count = 0;             // 命中次数计数器
    int total_count = 0;           // 总的访问次数计数器
    std::set<int> memory;          // 内存中的页面集合，用于记录当前内存中存储了哪些页面
    std::queue<int> second_chance; // 第二次机会算法中使用的辅助队列，用于记录页面进入内存的顺序

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
            memory.insert(page);      // 将页面加入内存中
            second_chance.push(page); // 将页面加入第二次机会算法的辅助队列中，记录页面的进入顺序
        }
        else // 如果内存已满，需要进行页面置换
        {
            // 从第二次机会算法的辅助队列中查找第一个未被访问过的页面
            while (true)
            {
                int candidate_page = second_chance.front(); // 获取第二次机会算法中最早进入内存的页面
                second_chance.pop();                        // 将最早进入内存的页面从辅助队列中移除

                // 如果该页面已经被访问过（即第二次机会），将其重新加入辅助队列尾部，并标记为未被访问过
                if (memory.find(candidate_page) != memory.end())
                {
                    second_chance.push(candidate_page); // 将页面重新加入辅助队列尾部
                    memory.erase(candidate_page);       // 将页面标记为未被访问过
                }
                else // 如果该页面未被访问过，执行页面置换操作
                {
                    memory.erase(candidate_page); // 将最早进入内存的页面从内存中移除
                    memory.insert(page);          // 将当前页面加入内存中
                    second_chance.push(page);     // 将当前页面加入辅助队列中，记录页面的进入顺序
                    break;                        // 跳出循环，完成页面置换操作
                }
            }
        }
    }

    // 计算命中率
    hit_rate = (double)hit_count / total_count * 100;
    return hit_count; // 返回命中次数
}

#endif // SECONDCHANCE_H
