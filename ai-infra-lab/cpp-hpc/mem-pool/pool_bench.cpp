#include <iostream>
#include <vector>
#include <memory_resource>
#include <chrono>

// 每个小块大小，模拟通信缓冲区
constexpr size_t BLOCK_SIZE = 256;
// 单次批量分配数量
constexpr size_t ALLOC_PER_ROUND = 10000;
// 循环轮次
constexpr size_t ROUNDS = 500;

// 测试1：原生 new / delete
void bench_raw_new_delete() {
    std::vector<char*> ptrs;
    ptrs.reserve(ALLOC_PER_ROUND);
    for (size_t r = 0; r < ROUNDS; r++) {
        ptrs.clear();
        for (size_t i = 0; i < ALLOC_PER_ROUND; i++) {
            char* p = new char[BLOCK_SIZE];
            ptrs.push_back(p);
        }
        for (char* p : ptrs) {
            delete[] p;
        }
    }
}

// 测试2：标准库pmr内存池
void bench_pmr_pool() {
    // 内存池：固定小块缓存，减少malloc调用
    std::pmr::pool_options opts;
    opts.max_blocks_per_chunk = ALLOC_PER_ROUND * 2;
    opts.largest_required_pool_block = BLOCK_SIZE;
    std::pmr::unsynchronized_pool_resource pool(opts);

    std::vector<char*, std::pmr::polymorphic_allocator<char*>> ptrs(&pool);
    ptrs.reserve(ALLOC_PER_ROUND);

    for (size_t r = 0; r < ROUNDS; r++) {
        ptrs.clear();
        for (size_t i = 0; i < ALLOC_PER_ROUND; i++) {
            char* p = static_cast<char*>(pool.allocate(BLOCK_SIZE));
            ptrs.push_back(p);
        }
        for (char* p : ptrs) {
            pool.deallocate(p, BLOCK_SIZE);
        }
    }
}

int main() {
    using Clock = std::chrono::high_resolution_clock;

    // 1. raw new delete
    auto t1 = Clock::now();
    bench_raw_new_delete();
    auto t2 = Clock::now();
    auto dur_raw = std::chrono::duration<double>(t2 - t1).count();

    // 2. pmr pool
    auto t3 = Clock::now();
    bench_pmr_pool();
    auto t4 = Clock::now();
    auto dur_pmr = std::chrono::duration<double>(t4 - t3).count();

    std::cout << "raw new/delete time: " << dur_raw << " s\n";
    std::cout << "std::pmr pool time:  " << dur_pmr << " s\n";
    return 0;
}
