#include <QCoreApplication>
#include <iostream>

#ifndef __cplusplus 201103L
#error "没有使用c++2.0"
#endif

// 1. variadic Templates
void myprint()
{
}
// 循环调用此函数，直到无参数时，调用print()终止
template <typename T, typename... Types>
void myprint(const T& firstArg, const Types&... args)
{
    std::cout << firstArg << std::endl;
    myprint(args...);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    myprint("dfsdfsdf","gffg","sfdsfsdf","dfd3434344sfsd");
    return 0;

}
