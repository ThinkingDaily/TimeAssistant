#ifndef __UNIFORM_HPP
#define __UNIFORM_HPP

class Uniform {
public:
    Uniform(double a, double b);
    double next();

private:
    Uniform();

private:
    double m_a;
    double m_b;
};

#endif
