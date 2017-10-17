#include "test.h"

#include <iostream>
#include <string>
CTest::CTest(int x): _x(x) 
{
}

void CTest::print() 
{
    std::string hello("Hello");
    std::cout<<hello<<std::endl;
    std::cout<<_x<<std::endl;
}
