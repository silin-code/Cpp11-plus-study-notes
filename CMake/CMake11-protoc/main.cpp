#include <iostream>
#include <string>
#include "person.pb.h"

int main()
{
    // 1创建person对象
    example::Person person;
    person.set_name("张三");
    person.set_id(10086);
    person.set_email("zhangsan@qq.com");

    // 2序列化person对象
    std::string serialized_data;
    person.SerializeToString(&serialized_data);
    std::cout << "Serialized data size: " << serialized_data.size() << std::endl;
    //3反序列化person对象
    example::Person parsed_person;
    parsed_person.ParseFromString(serialized_data);
    std::cout << parsed_person.DebugString() << std::endl;


    return 0;
}