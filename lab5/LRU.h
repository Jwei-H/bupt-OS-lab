#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <vector>
#include <algorithm>

// 定义帧结构体
struct Frame {
    int page_number;
    int counter;
};

// 寻找最少使用的帧
int findLRU(std::vector<Frame>& frames) {
    int min_index = 0;
    int min_counter = frames[0].counter;

    for (size_t i = 1; i < frames.size(); i++) {
        if (frames[i].counter < min_counter) {
            min_index = i;
            min_counter = frames[i].counter;
        }
    }

    return min_index;
}

// LRU 算法实现
int LRU(std::queue<int> q, int frame_size) {
    std::vector<Frame> frames(frame_size, {-1, 0});
    int page_faults = 0;
    int time = 0;

    while (!q.empty()) {
        int page = q.front();
        q.pop();
        bool page_found = false;

        for (auto& frame : frames) {
            if (frame.page_number == page) {
                frame.counter = ++time;
                page_found = true;
                break;
            }
        }

        if (!page_found) {
            int lru_index = findLRU(frames);
            frames[lru_index] = {page, ++time};
            page_faults++;
        }
    }

    return page_faults;
}

#endif // LRU_H
