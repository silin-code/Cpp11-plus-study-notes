#include <iostream>
#include <json/json.h>

int main()
{
    Json::Value root;
    root["name"] = "Bits";
    root["age"] = 18;
    Json::StreamWriterBuilder writer;
    std::string JsonStr = Json::writeString(writer, root);
    std::cout << "root \r\n"
              << JsonStr << std::endl;

    return 0;
}