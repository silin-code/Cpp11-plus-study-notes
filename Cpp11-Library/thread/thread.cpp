#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <memory>
#include <windows.h>
#include <vector>

void print_num(int num)
{
    for(int i=0;i<num;i++)
    {
        std::cout<<"普通函数线程:"<<i<<std::endl;
    }
}

class Task{
    public:
    void print_string(const std::string& s)
    {
        for(int i=0;i<3;i++)
        {
            std::cout<<"类成员函数线程:"<<s<<std::endl;
        }
    }
};
void bad_detach_example(){
    int local_var=10;
    std::thread t([&local_var](){
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout<<local_var<<std::endl;
    });
    t.detach();
}

void modify_calue(int& x)
{
    x=100;
}

void process_data(std::unique_ptr<int> ptr)
{
    std::cout<<*ptr<<std::endl;
}

void thread_func(int id)
{
    std::cout<<"thread "<<id<<" is running"<<std::endl;
}

void safe_thread_func()
{
    try{
        throw std::runtime_error("error");
    }
    catch(const std::exception& e)
    {
        std::cout<<"thread exception:"<<e.what()<<std::endl;
    }
}

thread_local int counter =0;//每个线程都有自己的count

void increment()
{
    for(int i=0;i<3;i++)
    {
        counter++;
        std::cout<<"thread "<<std::this_thread::get_id()<<" counter:"<<counter<<std::endl;
    }
}
int main()
{
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout<<"main thread ID:"<<std::this_thread::get_id()<<std::endl;

    // std::cout<<"main thread ID:"<<std::this_thread::get_id()<<std::endl;
    // //休眠1s
    // std::cout<<"sleep begin"<<std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::cout<<"sleep end"<<std::endl;

    // //休眠到下一个整秒
    // auto now = std::chrono::system_clock::now();
    // auto next_second = now + std::chrono::seconds(1);

    // std::cout<<"sleep begin"<<std::endl;
    // std::this_thread::sleep_until(next_second);
    // std::cout<<"sleep end"<<std::endl;
    // std::thread t1(thread_func,1);
    // std::thread t2= std::move(t1);//t1逝去所有权，变成空线程
    // //t1.join();//t1不关连任何线程

    // //移动赋值
    // std::thread t3;
    // t3 = std::move(t2);//t2逝去所有权
    // t3.join();
    // std::vector<std::thread> threads;
    // for(int i=0;i<3;i++)
    // {
    //     threads.emplace_back(thread_func,i);//直接构造线程对象
    //     //threads.push_back(std::thread(thread_func,i));
    // }

    // //等待线程所有线程完成
    // for(auto & t:threads)
    // {
    //     if(t.joinable())//必须检查是否可以join
    //     {
    //         t.join();
    //     }
    // }
    //  // auto ptr =std::make_unique<int>(42);
    // //std::thread t(process_data,ptr)//编译错误:unique_ptr不能被拷贝
    // std::thread t(process_data,std::move(ptr));
    // t.join();
    // int a=10;
    // //std::thread t(modify_value,a)//无法将int转化成int&
    // std::thread t(modify_calue,std::ref(a));
    // t.join();
    // std::cout<<a<<std::endl;

    // //普通函数
    // std::thread t1(print_num,5);

    // //lambda表达式
    // std::thread t2([](){
    //     for(int i=0;i<3;i++)
    //     {
    //         std::cout<<"lambda线程:"<<i<<std::endl;
    //     }
    // });

    // //类成员函数
    // Task task;
    // std::thread t3(&Task::print_string,&task,"hello world");

    // //等待所有线程完毕
    // t1.join();
    // t2.join();
    // t3.join();
}