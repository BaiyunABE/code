#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>

// 有锁阻塞队列模板
template<typename T>
class BlockQueue {
private:
    std::queue<T> q_;
    std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    size_t cap_;
public:
    BlockQueue(size_t cap) : cap_(cap) {}

    void push(T val) {
        std::unique_lock<std::mutex> lock(mtx_);
        // 队列满，生产者等待
        not_full_.wait(lock, [this](){ return q_.size() < cap_; });
        q_.push(val);
        not_empty_.notify_one(); // 唤醒消费者
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        // 队列空，消费者等待
        not_empty_.wait(lock, [this](){ return !q_.empty(); });
        T ret = q_.front();
        q_.pop();
        not_full_.notify_one(); // 唤醒生产者
        return ret;
    }
};

const int QUEUE_CAP = 100;
const int PROD_CNT = 4;
const int CONS_CNT = 4;
const int TASK_PER_PROD = 50000;

BlockQueue<int> q(QUEUE_CAP);

void producer() {
    for(int i = 0; i < TASK_PER_PROD; i++) {
        q.push(i);
    }
}

void consumer(long long& sum) {
    long long local_sum = 0;
    for(int i = 0; i < TASK_PER_PROD; i++) {
        local_sum += q.pop();
    }
    // 加锁汇总总和
    static std::mutex sum_mtx;
    std::lock_guard<std::mutex> lock(sum_mtx);
    sum += local_sum;
}

int main() {
    std::vector<std::thread> prods, cons;
    long long total = 0;

    // 启动生产者
    for(int i = 0; i < PROD_CNT; i++) {
        prods.emplace_back(producer);
    }
    // 启动消费者
    for(int i = 0; i < CONS_CNT; i++) {
        cons.emplace_back(consumer, std::ref(total));
    }

    for(auto& t : prods) t.join();
    for(auto& t : cons) t.join();

    std::cout << "total sum: " << total << std::endl;
    return 0;
}
