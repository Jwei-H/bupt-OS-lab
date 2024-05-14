#pragma once
#include <queue>
#include <vector>
#include <unordered_map>

int Clock(std::queue<int> q,int size){
    int hit_count = 0; //命中次数
    std::unordered_map<int,bool> use_bit ;//每个页面的访问位
    std::vector<int> memory(size,-1);//初始化内存为空
    int pointer = 0;//时钟指针位置

    while(!q.empty()){
        //预处理进程
        int process = q.front();
        q.pop();
        int page = process/10;
        
        bool hit = false;//记录页面是否已经在内存中
        //检查页面是否在内存中
        for(int i = 0;i < size;i++){
            if (memory[i] == page)
            {
                hit = true;
                hit_count++;
                use_bit[page] = true;  // 每次访问都改变访问位
                break;
            }
        }

        if (!hit) {
            // 使用时钟算法替换页面
            while (true) {
                int current_page = memory[pointer];
                if (current_page == -1 || !use_bit[current_page]) {
                    if (current_page != -1) {
                        use_bit.erase(current_page);  // 移除替换页面的使用位
                    }
                    memory[pointer] = page;  // 替换页面
                    use_bit[page] = true;    // 设置新页面的使用位
                    pointer = (pointer + 1) % size;  // 移动指针
                    break;
                } else {
                    use_bit[current_page] = false;  // 清除使用位
                    pointer = (pointer + 1) % size;  // 移动指针
                }
            }
        }
    }
    return hit_count;
}