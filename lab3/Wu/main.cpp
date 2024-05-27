#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

// 阻塞队列类
template<typename T>
class BlockingQueue {
private:
    std::queue<T> queue_; // 内部队列
    std::mutex mutex_; // 互斥锁
    std::condition_variable cond_; // 条件变量

public:
    // 向队列中添加元素
    void push(const T& value) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(value);
        }
        cond_.notify_one(); // 通知等待的线程
    }

    // 从队列中取出元素
    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待队列非空
        cond_.wait(lock, [this] { return !queue_.empty(); });
        T value = queue_.front();
        queue_.pop();
        return value;
    }
};

// 生产者线程函数
void producerFunc(BlockingQueue<int>& queue) {
    for (int i = 0; i < 10; ++i) {
        std::cout << "produced: " << i << std::endl;
        queue.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// 消费者线程函数
void consumerFunc(BlockingQueue<int>& queue) {
    for (int i = 0; i < 10; ++i) {
        int value = queue.pop();
        std::cout << "Consumed: " << value << std::endl;
    }
}

int main() {
    BlockingQueue<int> queue;

    // 创建生产者线程和消费者线程
    std::thread producerThread(producerFunc, std::ref(queue));
    std::thread consumerThread(consumerFunc, std::ref(queue));

    // 等待线程结束
    producerThread.join();
    consumerThread.join();

    return 0;
}

