/*
c++ -I path/to/boost_1_61_0 example.cpp -o example \
   ~/boost/stage/lib/libboost_regex-gcc34-mt-d-1_36.a

g++ boost_test_regex.cpp -o boost_test_regex -lboost_regex

./boost_test_regex < jayne.txt
*/
#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
    std::string line;
    boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

    while (std::cin)
    {
        std::getline(std::cin, line);
        boost::smatch matches;
        if (boost::regex_match(line, matches, pat))
            std::cout << matches[2] << std::endl;
    }
}
