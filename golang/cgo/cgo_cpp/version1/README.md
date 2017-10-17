golang调用C++的库。
这里test.h, test.cpp是一个class，然后用test_api.h,.c封装成C API。
main.c用于测试test_api；main.go通过cgo调动test_api。
