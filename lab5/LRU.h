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

#endif // LRU_H
