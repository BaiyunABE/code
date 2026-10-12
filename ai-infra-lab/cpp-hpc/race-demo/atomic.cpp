#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> cnt{0};

void add_task() {
    for(int i = 0; i < 100000; i++){
        cnt++;
    }
}

int main() {
    std::vector<std::thread> ths;
    for(int i = 0; i < 8; i++){
        ths.emplace_back(add_task);
    }
    for(auto& t : ths) t.join();
    std::cout << "result: " << cnt << std::endl;
    return 0;
}
