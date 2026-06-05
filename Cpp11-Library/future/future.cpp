#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

int square(int x)
{
    this_thread::sleep_for(chrono::seconds(1));
    return x * x;
}

int main()
{
    //显式指定新开线程
    future<int> fu = async(launch::async,square,10);\

    cout<<"主线程执行"<<'\n';

    cout<<"线程执行结果："<<fu.get()<<'\n';
    
    return 0;
}

// int add(int a,int b)
// {
//     return a+b;
// }

// int main()
// {
//     //包装函数,模版参数是函数签名
//     packaged_task<int(int,int)> task(add);

//     future<int> fu =task.get_future();

//     //启动线程
//     thread t(move(task),10,20);//package不可拷贝只能移动

//     cout<<fu.get()<<endl;

//     t.join();
//     return 0;
// }

// mutex mtx;
// int main()
// {
//     promise<int> pro;
//     shared_future<int> sfu = pro.get_future().share(); // 转换为shared_future

//     vector<thread> threads;
//     for (int i = 0; i < 3; i++)
//     {
//         threads.emplace_back([sfu]()
//                              {
//                                 unique_lock<mutex> lock(mtx);
//                                 cout << "线程：" << this_thread::get_id() << ":" << sfu.get() << '\n';
//                              });
//     }
//     this_thread::sleep_for(chrono::seconds(1));
//     pro.set_value(42);
//     for (auto &t : threads)
//     {
//         t.join();
//     }
//     return 0;
// }

// void worker(promise<int> pro)
// {
//     try{
//         int result = 100+200;
//         pro.set_value(result);
//     }
//     catch(...)
//     {
//         pro.set_exception(current_exception());
//     }
// }

// int main()
// {
//     promise<int> pro;
//     future<int> fu = pro.get_future();//获取对应future

//     thread t(worker,move(pro));//不可拷贝，只能移动

//     cout<<fu.get()<<endl;

//     t.join();
//     return 0;
// }

// int main()
// {
//     //假设已经通过promise/async获取了future<int> fu
//     future<int> fu =async(launch::async ,[](){return 100;});

//     if(fu.valid())
//     {
//         auto status = fu.wait_for(chrono::seconds(1));
//         if(status == future_status::ready)
//         {
//             cout<<"结果："<<fu.get()<<endl;
//         }
//         else{
//             cout<<"结果未就绪"<<endl;
//         }
//     }

//     return 0;
// }