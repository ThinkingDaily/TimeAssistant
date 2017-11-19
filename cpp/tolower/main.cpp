/*
g++ -o test test.cpp
./test
    hello
    HeLlo
    hello
*/a
#include <algorithm>
#include <string>
#include <iostream>

static std::string get_lower_string(const std::string &str);
static void lower_string(std::string &str);

std::string get_lower_string(const std::string &str)
{
    std::string ret(str);
    lower_string(ret);
    return ret;
}

void lower_string(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

int main()
{
    std::string a("HeLlo");

    std::string b(get_lower_string(a));
    std::cout<<b<<std::endl;
    std::cout<<a<<std::endl;

    lower_string(a);
    std::cout<<a<<std::endl;

    return 0;
}