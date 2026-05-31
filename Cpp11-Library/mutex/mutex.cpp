#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

timed_mutex mtx;

void fireworks(int i)
{
    while (!mtx.try_lock_for(chrono::milliseconds(1000)))
    {
        cout << "-";
    }

    cout << i;
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "*\n";
    mtx.unlock();
}

mutex m1, m2;

void taskA()
{
    lock(m1, m2); // 同时锁两个，不会死锁
    // 临界区
    m1.unlock();
    m2.unlock();
}

void taskB()
{
    lock(m2, m1); // 颠倒顺序也没事，std::lock内部规避死锁
}

int main()
{
    thread threads[2];
    for (int i = 0; i < 2; i++)
    {
        threads[i] = thread(fireworks, i);
    }
    for (auto &th : threads)
    {
        th.join();
    }
    return 0;
}

// #include <iostream>
// #include <thread>
// #include <mutex>

// using namespace std;

// recursive_mutex rmtx;
// void funcB()
// {
//     rmtx.lock();
//     cout<<"funcB"<<endl;
//     rmtx.unlock();
// }
// void fucnA()
// {
//     rmtx.lock();
//     cout<<"funcA"<<endl;
//     funcB();
//     rmtx.unlock();
// }

// int main()
// {
//     thread t1(fucnA);
//     thread t2(funcB);
//     t1.join();
//     t2.join();
// }

// // mutex mtx;
// // int g_cnt = 0;
// // void add()
// // {
// //     for (int i = 0; i < 100000; i++)
// //     {
// //         lock_guard<mutex> lg(mtx);
// //         g_cnt++;
// //     }
// // }

// // void print_id(int id)
// // {
// //     mtx.lock();
// //     lock_guard<mutex> lck(mtx, adopt_lock);
// //     cout << "thread #" << id << endl;
// // }

// // int main()
// // {
// //     // thread t1(print_id,1);
// //     // thread t2(print_id,2);
// //     // t1.join();
// //     // t2.join();
// // }
// template <class _Fn, class... _Args,
//           enable_if_t<!is_same_v<_Remove_cvref_t<_Fn>, thread>, int> = 0>
// _NODISCARD_CTOR explicit thread(_Fn &&_Fx, _Args &&..._Ax)
// {
//     _Start(_STD forward<_Fn>(_Fx), _STD forward<_Args>(_Ax)...);
// }
// template <class _Fn, class... _Args>
// void _Start(_Fn &&_Fx, _Args &&..._Ax)
// {
//     // 从下⾯可以看到，线程要调⽤系统库的线程，最终还是要把参数包打包成⼀个结构体对象再传给线程，所以线程中拿到的参数包值是我们传的参数包值的拷⻉，所以要⽤ref才传参才能解决问题
//     using _Tuple = tuple<decay_t<_Fn>,
//                          decay_t<_Args>...>;
//     auto _Decay_copied = _STD make_unique<_Tuple>(_STD
//                                                       forward<_Fn>(_Fx),
//                                                   _STD forward<_Args>(_Ax)...);
//     constexpr auto _Invoker_proc = _Get_invoke<_Tuple>(make_index_sequence<1 + sizeof...(_Args)>{});
//     // pointer or reference to potentially throwing function passed to
//     // extern C function under -EHc. Undefined behavior may occur
//     // if this function throws an exception. (/Wall)
//     _Thr._Hnd = reinterpret_cast<void *>(_CSTD _beginthreadex(nullptr, 0,
//                                                               _Invoker_proc, _Decay_copied.get(), 0, &_Thr._Id));
//     if (_Thr._Hnd)
//     { // ownership transferred to the thread
//         (void)_Decay_copied.release();
//     }
//     else
//     { // failed to start thread
//         _Thr._Id = 0;
//         _Throw_Cpp_error(_RESOURCE_UNAVAILABLE_TRY_AGAIN);
//     }
// }