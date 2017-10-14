#include <iostream>
#include <vector>
#include <algorithm>

static void init(std::vector<int> &values)
{
    values.push_back(1);
    values.push_back(2);
    values.push_back(4);
    values.push_back(4);
    values.push_back(5);
}

static void print(int i)
{
    std::cout<<i<<std::endl;
}

static void dump(const std::vector<int> &values)
{
    std::for_each(values.begin(), values.end(), print);
}

void remove_elements()
{
    std::vector<int> values;

    init(values);
    values.erase(std::remove(values.begin(), values.end(), 5), values.end());
    dump(values);
}

int main()
{
    remove_elements();
    return 0;
}


