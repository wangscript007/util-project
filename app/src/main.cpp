#include <iostream>
#include <thread>
#include <chrono>
#include "log4cxxhelper.h"


void test()
{
    Log4cxxHelper::init("log4cxx.properties", 3000);

    LOG_DEBUG("stdout", "int: %d, double: %f, string: %s", 123, 56.3, "this is test log!!!");
    LOG_INFO("All", "int: %d, double: %f, string: %s", 189, 16.308, "this is test log!!!");

    for (size_t i = 0; i < 500000; ++i)
    {
        LOG_DEBUG("stdout", "int: %d, double: %f, string: %s", 1 + i, 56.3, "this is test log!!!");
        LOG_INFO("All", "int: %d, double: %f, string: %s", 1 + i, 16.308, "this is test log!!!");
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return;
}

int main(int argc, char** argv)
{
    std::cout << "Hello utility!!!" << std::endl;

    test();

    getchar();
    return 0;
}
