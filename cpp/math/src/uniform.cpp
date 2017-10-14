#include "uniform.hpp"

//#include "random.h"
#include <stdlib.h>

Uniform::Uniform(double a, double b) : m_a(a), m_b(b)
{
}

double Uniform::next() 
{
    int v = random();
    double temp = (double)v / 0x7fffffff;
    return m_a + temp * (m_b - m_a);
}
