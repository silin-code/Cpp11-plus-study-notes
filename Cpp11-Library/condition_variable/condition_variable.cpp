#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

constexpr int BUFFER_SIZE = 5; /// 缓冲区大小
queue<int> buffer;             // 缓冲区

mutex mtx;
condition_variable not_full;  // 缓冲区非满
condition_variable not_empty; // 缓冲区非空
bool production_finished = false;

void producer(int id)
{
    for (int i = 0; i < 10; i++)
    {
        unique_lock<mutex> lck(mtx);

        // 缓冲区非满
        not_full.wait(lck, []()
                      { return buffer.size() < BUFFER_SIZE; });

        // produce data
        int data = id * 100 + i;
        buffer.push(data);
        cout << "produce:" << data << ",buffersize:" << buffer.size() << endl;

        // 通知消费者线程
        not_empty.notify_one();

        // move to next step
        lck.unlock();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(int id)
{
    for (;;)
    {
        unique_lock<mutex> lck(mtx);

        // 缓冲区非空
        not_empty.wait(lck, []()
                       { return buffer.size() > 0 || production_finished; });

        if (buffer.empty() && production_finished)
        {
            break;
        }

        // consume data
        int data = buffer.front();
        buffer.pop();
        cout << "consume:" << data << ",buffersize:" << buffer.size() << endl;

        // 通知生产者线程
        not_full.notify_one();

        lck.unlock();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main()
{
    thread producers[2];
    thread consumers[3];

    for (int i = 0; i < 2; i++)
    {
        producers[i] = thread(producer, i);
    }

    for (int i = 0; i < 3; i++)
    {
        consumers[i] = thread(consumer, i);
    }

    for (int i = 0; i < 2; i++)
    {
        producers[i].join();
    }
    // 设置生产完成标志
    {
        unique_lock<mutex> lck(mtx);
        production_finished = true;
    }
    not_empty.notify_all();
    // 等待所有消费者线程完成
    for (int i = 0; i < 3; i++)
    {
        consumers[i].join();
    }

    cout << "task done" << endl;
    return 0;
}
// int main()
// {
//     mutex mtx;
//     condition_variable cv;
//     const int n = 100;
//     bool flag = true; // true让偶数线程执行,false让奇数线程执行

//     thread t1([&]()
//               {
//         int i=0;
//         while(i<n)
//         {
//             unique_lock<mutex> lck(mtx);
//             cv.wait(lck,[&](){return flag;});
//             cout<<"偶数线程:"<<i<<endl;
//             i+=2;
//             flag=false;//切换到奇数线程
//             cv.notify_one();//通知奇数线程
//         } });

//     thread t2([&]()
//               {
//     int j=1;
//     while(j<n)
//     {
//         unique_lock<mutex> lck(mtx);
//         cv.wait(lck,[&](){return !flag;});
//         cout<<"奇数线程:"<<j<<endl;
//         j+=2;
//         flag=true;//切换到偶数线程
//         cv.notify_one();//通知偶数线程

//     } });

//     t1.join();
//     t2.join();
// }

// mutex mtx;
// condition_variable cv;
// bool ready = false;

// void worker()
// {
//     //模拟耗时任务
//     this_thread::sleep_for(chrono::seconds(2));

//     //修改条件加锁
//     lock_guard<mutex> lck(mtx);
//     ready = true;
//     cout << "task done" << endl;

//     //通知等待线程
//     cv.notify_one();
// }

// void waiter()
// {
//     unique_lock<mutex> lck(mtx);

//     // while(!ready)
//     // {
//     //     cv.wait(lck);
//     // }

//     cv.wait(lck,[](){return ready;});
//     cout << "task done" << endl;
// }

// int main()
// {
//     thread t1(worker);
//     thread t2(waiter);
//     t1.join();
//     t2.join();
//     return 0;
// }

// bool task_done = false;
// mutex mtx;

// void worker()
// {
//     //模拟耗时任务
//     this_thread::sleep_for(chrono::seconds(2));
//     lock_guard<mutex> lck(mtx);
//     task_done = true;
//     cout << "task done" << endl;
// }

// void waiter()
// {
//     for(;;)
//     {
//         lock_guard<mutex> lck(mtx);
//         if(task_done)
//         {
//             break;
//         }
//         //不加sleep会沾满CPU
//         //加sleep会延迟响应
//     }
//     cout << "task done" << endl;
// }

// int main()
// {
//     thread t1(worker);
//     thread t2(waiter);
//     t1.join();
//     t2.join();
//     return 0;
// }