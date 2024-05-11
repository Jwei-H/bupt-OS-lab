#include <queue>
#include <set>

int LFR(std::queue<int> q, int size)
{
    int hit_count = 0;
    std::set<int> memory;
    int info[32][2]; // 记录每个页面的访问次数和最后一次访问的时间
    for (int i = 0; i < 32; i++)
    {
        info[i][0] = 0;
        info[i][1] = 0;
    }
    while (!q.empty())
    {
        int process = q.front();
        q.pop();
        int page = process / 10;
        if (memory.find(page) != memory.end())
        {
            hit_count++;
            info[page][0]++;
            info[page][1] = 320 - q.size();
        }
        else
        {
            if (memory.size() < size)
            {
                memory.insert(page);
                info[page][0] = 1;
                info[page][1] = 320 - q.size();
            }
            else
            {
                // 在选择淘汰页面时，先按照访问频率筛选出候选页面，然后在这些页面中选择最后访问时间最早的进行淘汰。
                int max = -1;
                int max_page = -1;
                for (int temp : memory)
                {
                    if (info[temp][0] > max)
                    {
                        max = info[temp][0];
                        max_page = temp;
                    }
                    else if (info[temp][0] == max)
                    {
                        if (info[temp][1] < info[max_page][1])
                        {
                            max = info[temp][0];
                            max_page = temp;
                        }
                    }
                }
                memory.erase(max_page);
                memory.insert(page);
                info[page][0] = 1;
                info[page][1] = 320 - q.size();
            }
        }
    }
    return hit_count;
};