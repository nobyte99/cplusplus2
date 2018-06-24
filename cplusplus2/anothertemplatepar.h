#ifndef ANOTHERTEMPLATEPAR_H
#define ANOTHERTEMPLATEPAR_H
// 另一个能够达到上边templatetemplatepar的内存管理需求的类，但是不是模版参数的模版，仅仅是2个模版参数,
#include <list>
#include <iostream>



template <typename T, typename container = std::list<T>>
class anothertemplatepar
{
public:
    explicit anothertemplatepar();
    void Init(std::initializer_list<T> lst);
    void MyPrint();

private:
    container objDispather;
};

template <typename T, typename container>
anothertemplatepar<T,container>::anothertemplatepar()
{
    objDispather.clear();
}

template <typename T, typename container>
void anothertemplatepar<T,container>::Init(std::initializer_list<T> lst)
{
    objDispather = lst;
}

template <typename T, typename container>
void anothertemplatepar<T,container>::MyPrint()
{
    for(auto i = this->objDispather.begin(); i != objDispather.end(); i++){
        std::cout << *i << std::endl;
    }
}



#endif // ANOTHERTEMPLATEPAR_H
