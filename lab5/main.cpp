#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include "LFR.h"
#include "OPT.h"
#include "Clock.h"
#include "FIFO.h"
#include "SecondChance.h"
#include <iomanip>

std::queue<int> generate_queue();

int main()
{
    std::queue<int> q = generate_queue();

    std::cout << "size  "
              << "hit_rate_LFR  "
              << "hit_rate_OPT  "
              << "hit_rate_CLOCK  "
              << "hit_rate_FIFO  "
              << "hit_rate_SC" << std::endl;
    for (int size = 4; size < 32; size++)
    {
        std::cout << size;
        if (size < 10)
            std::cout << " ";
        std::cout << std::setw(13) << std::setprecision(4) << std::showpoint << (double)LFR(q, size) / 3.2 << "%"
                  << std::setw(13) << (double)OPT(q, size) / 3.2 << "%"
                  << std::setw(13) << (double)Clock(q, size) / 3.2 << "%"
                  << std::setw(13) << (double)FIFO(q, size) / 3.2 << "%"
                  << std::setw(13) << (double)SecondChance(q, size) / 3.2 << "%"
                  << std::endl;
    }
    return 0;
}

std::queue<int> generate_queue()
{
    unsigned seed = time(0);
    srand(seed);
    std::queue<int> q;
    for (int i = 0; i < 64; i++)
    {
        int M = rand() % 320;
        q.push(M);
        q.push((M + 1) % 320);
        M = rand() % (M + 2);
        q.push(M);
        q.push((M + 1) % 320);
        int k = (M + 2) % 320;
        M = k + rand() % (320 - k);
        q.push(M);
    }
    return q;
}