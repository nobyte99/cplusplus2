#ifndef TEMPLATETEMPLATEPAR_H
#define TEMPLATETEMPLATEPAR_H
#include <iostream>
#include <initializer_list>


template <typename T,
          template <typename T>
          class container
          >
class templatetemplatepar
{
public:
    explicit templatetemplatepar();
    void Init(std::initializer_list<T> lst);
    MyPrint();

private:
    container<T> objDispather;
};


template<typename T, template <typename> class container>
templatetemplatepar<T,container>::templatetemplatepar()
{
    objDispather.clear();
}

template<typename T, template <typename> class container>
void templatetemplatepar<T,container>::Init(std::initializer_list<T> lst)
{
    objDispather = lst;
}

template<typename T, template <typename> class container>
templatetemplatepar<T,container>::MyPrint()
{
    // c++2.0, range-based for
    for( auto &i : objDispather){
        std::cout << i << std::endl;
    }
}


#endif // TEMPLATETEMPLATEPAR_H
