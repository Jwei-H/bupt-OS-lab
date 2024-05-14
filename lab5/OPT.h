#include <queue>
#include <vector>
#include <set>
int OPT(std::queue<int> q, int size)
{
    int hit_count = 0;
    std::vector<std::queue<int>> next_hit_time(32);
    std::vector<int> page_order;
    while (!q.empty())
    {
        int process = q.front();
        q.pop();
        int page = process / 10;
        page_order.push_back(page);
        next_hit_time[page].push(320 - q.size());
    }
    std::set<int> memory;
    for (int i = 0; i < page_order.size(); i++)
    {
        int page = page_order[i];
        if (memory.find(page) != memory.end())
        {
            hit_count++;
        }
        else
        {
            if (memory.size() < size)
            {
                memory.insert(page);
            }
            else
            {
                int max = -1;
                int max_page = -1;
                for (int temp : memory)
                {
                    if (next_hit_time[temp].empty())
                    {
                        max_page = temp;
                        break;
                    }
                    if (next_hit_time[temp].front() > max)
                    {
                        max = next_hit_time[temp].front();
                        max_page = temp;
                    }
                }
                memory.erase(max_page);
                memory.insert(page);
            }
        }
        next_hit_time[page].pop();
    }
    return hit_count;
}