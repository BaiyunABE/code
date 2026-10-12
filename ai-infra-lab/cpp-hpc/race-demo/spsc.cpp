#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

template<typename T, size_t CAP>
class SPSCQueue {
private:
    T buf_[CAP];
    std::atomic<size_t> head_{0}; // 读指针
    std::atomic<size_t> tail_{0}; // 写指针

public:
    // 生产者入队
    bool push(const T& val) {
        size_t t = tail_.load(std::memory_order_relaxed);
        size_t h = head_.load(std::memory_order_acquire);
        if ((t + 1) % CAP == h) {
            return false; // 队列满
        }
        buf_[t] = val;
        tail_.store((t + 1) % CAP, std::memory_order_release);
        return true;
    }

    // 消费者出队
    bool pop(T& out) {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t t = tail_.load(std::memory_order_acquire);
        if (h == t) {
            return false; // 队列为空
        }
        out = buf_[h];
        head_.store((h + 1) % CAP, std::memory_order_release);
        return true;
    }
};

constexpr size_t QUEUE_CAP = 1024;
constexpr int TASK_NUM = 2000000;

SPSCQueue<int, QUEUE_CAP> q;

// 单生产者
void producer() {
    for (int i = 0; i < TASK_NUM; ++i) {
        while (!q.push(i)); // 满则自旋重试
    }
}

// 单消费者
void consumer(long long& sum) {
    long long s = 0;
    int val;
    for (int i = 0; i < TASK_NUM; ++i) {
        while (!q.pop(val)); // 空则自旋重试
        s += val;
    }
    sum = s;
}

int main() {
    long long total = 0;
    std::thread prod(producer);
    std::thread cons(consumer, std::ref(total));
    prod.join();
    cons.join();
    std::cout << "sum = " << total << std::endl;
    return 0;
}
