#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

/**
 * @brief 一个简单的自旋锁实现，用于多线程环境下的互斥访问保护。
 * 
 * 该锁基于 std::atomic_flag 实现，通过忙等待（busy-waiting）的方式获取锁。
 * 适用于临界区代码执行时间极短的场景，以避免线程上下文切换的开销。
 * 
 * @note 此类不可拷贝也不可移动，以确保锁状态的唯一性和安全性。
 */
class SpinLock
{
private:
    std::atomic_flag _flag = ATOMIC_FLAG_INIT;

public:
    // 【修复点】显式声明默认构造函数
    // 因为删除了拷贝构造函数，编译器不再自动生成默认构造函数，必须手动声明
    SpinLock() = default;

    /**
     * @brief 获取自旋锁。
     * 
     * 如果锁当前未被持有，则立即获取并返回；
     * 如果锁已被其他线程持有，则当前线程会持续循环检查（自旋），直到锁被释放。
     * 增加了 yield 以避免过度占用 CPU 资源。
     * 
     * @param 无
     * @return 无
     */
    void lock()
    {
        while(_flag.test_and_set(std::memory_order_acquire))
        {
            // 让出当前时间片，减少 CPU 浪费和缓存行争用
            std::this_thread::yield();
        }
    }

    /**
     * @brief 释放自旋锁。
     * 
     * 将锁标志位清除，允许其他等待的线程获取锁。
     * 使用 memory_order_release 确保在解锁前的所有内存操作对其他获取锁的线程可见。
     * 
     * @param 无
     * @return 无
     */
    void unlock()
    {
        _flag.clear(std::memory_order_release);
    }

    // 禁止拷贝和移动
    SpinLock(const SpinLock&) = delete;
    SpinLock& operator=(const SpinLock&) = delete;
};

// RAII 锁守卫，确保异常安全和自动解锁
class SpinLockGuard {
private:
    SpinLock& _lock;
public:
    explicit SpinLockGuard(SpinLock& lock) : _lock(lock) {
        _lock.lock();
    }

    ~SpinLockGuard() {
        _lock.unlock();
    }

    // 禁止拷贝
    SpinLockGuard(const SpinLockGuard&) = delete;
    SpinLockGuard& operator=(const SpinLockGuard&) = delete;
};

SpinLock spin_lock;
int cnt = 0;

void add(int n) {
    for (int i = 0; i < n; ++i) {
        // 使用 RAII 守卫，确保锁一定会被释放，即使未来临界区代码变复杂或抛出异常
        SpinLockGuard guard(spin_lock);
        cnt++;
    }
}

int main() {
    const int thread_num = 4;
    const int per_thread = 1000000;

    std::vector<std::thread> threads;
    for (int i = 0; i < thread_num; ++i) {
        threads.emplace_back(add, per_thread);
    }

    for (auto& th : threads) {
        th.join();
    }

    std::cout << "最终计数：" << cnt << std::endl;
    std::cout << "预期计数：" << thread_num * per_thread << std::endl;

    return 0;
}

// using namespace std;

// atomic<bool> ready(false);
// int data =0;
// void producer()
// {
//     data=42;
//     ready.store(true,memory_order_release);//发布数据
// }

// void consumer()
// {
//     while(!ready.load(memory_order_acquire)){}
//     cout<<"data:"<<data<<endl;
// }

// atomic<int> cnt(0);

// void add()
// {
//     for (size_t i = 0; i < 10000000; i++)
//     {
//         int old = cnt.load();
//         while(!cnt.compare_exchange_weak(old, old+1)){}
//     }
// }

// atomic<int> cnt(0);

// void add()
// {
//     for (size_t i = 0; i < 10000000; i++)
//     {
//         cnt++;
//     }
// }

// int main()
// {
//     thread t1(add);
//     thread t2(add);
//     t1.join();
//     t2.join();
//     cout << cnt << endl;
//     return 0;
// }

// class Singleton
// {
// private:
//     Singleton() {cout<<"单例对象创建"<<endl;}
//     ~Singleton() { cout << "单例对象销毁" << endl; }
//     Singleton(const Singleton&) = delete;
//     Singleton& operator=(const Singleton&) = delete;

//     static once_flag s_once_flag;
//     static Singleton* s_instance;
// public:
//     static Singleton* getInstance()
//     {
//         call_once(s_once_flag, [](){
//             s_instance = new Singleton();
//         });
//         return s_instance;
//     }
// };

// 静态成员初始化
// once_flag Singleton::s_once_flag;
// Singleton* Singleton::s_instance = nullptr;

// once_flag g_once_flag;

// void init_resource()
// {
//     cout << "资源初始化完成（只执行一次）" << endl;
//     // 模拟资源初始化
//     this_thread::sleep_for(chrono::milliseconds(100));
// }

// void worker(int id)
// {
//     cout << "线程" << id << "开始运行" << endl;
//     // 只有第一个到达这里的线程会执行init_resource
//     call_once(g_once_flag, init_resource);
//     cout << "线程" << id << "继续执行" << endl;
// }

// int main()
// {
//     thread threads[5];
//     for (int i = 0; i < 5; ++i) {
//         threads[i] = thread(worker, i);
//     }
//     for (auto& th : threads) {
//         th.join();
//     }
//     return 0;
// }

// #include <iostream>
// #include <atomic>
// #include <thread>
// #include <chrono>
// #include <mutex>

// using namespace std;
// mutex m1,m2,m3,m4,m5;
// int i=0;
// void func1()
// {
//     m1.lock();
//     m2.lock();
//     m3.lock();
//     m4.lock();
//     m5.lock();
//     cout<<i<<endl;
//     m1.unlock();
//     m2.unlock();
//     m3.unlock();
//     m4.unlock();
//     m5.unlock();
// }

// void func2()
// {
//     m5.lock();
//     m4.lock();
//     m3.lock();
//     m2.lock();
//     m1.lock();
//     cout<<i<<endl;
//     m5.unlock();
//     m4.unlock();
//     m3.unlock();
//     m2.unlock();
//     m1.unlock();
// }

// int main()
// {
//     while(1)
//     {
//         thread t1(func1);
//         thread t2(func2);
//         thread t3(func1);
//         thread t4(func2);
//         thread t5(func1);
//         thread t6(func2);
//         t1.join();
//         t2.join();
//         t3.join();
//         t4.join();
//         t5.join();
//         t6.join();
//         i++;
//     }
// }