#include <cstdio>
#include <iostream>

class Foo {
public:
    explicit Foo(int v): start(0x1234), value(v), end(0x5678) {
    }
    
    operator int() {
        std::cout << "int()" << std::endl;
        return value * 3;
    }

    Foo operator+(const Foo& other) {
        return Foo(value + other.value);
    }

private:
    int start;
    int value;
    int end;
};

void print(int n)
{
	printf("n: %d\n", n);
}

struct Point3D {
    int x;
    int y;
    int z;
};

int main()
{
    Foo foo2(2);
    Foo foo3(30);
    Foo foo5 = foo2 + foo3;
    printf("foo5: 0x%x\n", foo5);
    printf("foo5: %d\n", (int)foo5);
    print(foo5);

    Point3D point = {3, 4, 5};
    printf("point: %d\n", point);

    return 0;
}
