#include <QCoreApplication>


#ifndef __cplusplus 201103L
#error "没有使用c++2.0"
#endif

#include <iostream>
#include <vector>
using namespace  std;


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

// 可以实现递归继承；如Tuple的实现

/* 2. nullptr
 *
 * void f(int)
 * void f(void*)
 * void f(NULL)    -> f(int)
 * void f(nullptr) -> f(void*)
 *
 */

// 3.initialize_list , 对stl库，包括数据结构和算法在内的诸多实现都产生了重要的影响，
// 现在很多数据结构和算法的输入全部都是initialize_list类型了。
void myprint1(std::initializer_list<int> vals)
{
    for(auto i=vals.begin(); i != vals.end(); ++i){
        std::cout << *i << "  ";
    }
    std::cout << endl;
}

/* const 必须写的场景。是否加const十分重要；
 * const complex c1(2,1);
 * cout << c1.real();  编译器提示出错，那么意味这real 没有使用const修饰，如果real不更改real，
 * 那么必须const 修饰。 上面的const是函数签名的一部分，必须加。real（）可以有两个，一个有const，一个没有const
 * 主要考虑是否处理COW（copy on write）。
 *
 * class complex{
 * public:
 *     double real() const { return real; }  #可以认为const在这里修饰{}，{}中不会改变实例任何值。
 * private:
 *     double real;
 * }
 *
 * 因为类里变量有的是实例，有的是指针，所以特别需要注意copy构造和=赋值函数。
 * 当类里变量为实例时，我们可以使用默认的编译器提供的copy构造和=赋值函数。
 * 但类里变量为指针时，我们一定要注意copy构造和=赋值函数是否应该自己实现深copy，否则会导致两个类实例
 * 中的指针变量指向同一个内存区域，引起错误，切记。
 *
 * 类总体分为两类：类里变量无指针，类里变量有指针，从而导致类的三大函数：copy构造、copy赋值函数和析构函数
 * 具有不同的对待方式：
 * 1、无指针的： 可以直接使用编译器提供的默认copy构造、copy赋值函数和析构函数
 * 2、有指针的： 必须自己实现copy构造、copy赋值函数和析构函数，以便于实现指针指向内容的处理。如果用编译器
 * 默认提供的，那么出现的问题就是copy构造生成的类实例和原本的实例中的类里变量指针指向了同一块内存，从而导致
 * 异常问题。（除非你故意就要这么做）
 *
 * 类设计的三大方式：组合、继承、委托。
 * 其中依托与委托设计，有一项特别需要指出的就是PIMPL设计模式（handle/body）。
 *
 * 设计模式（构造） prototype模式：
 * prototype父类： 实现对子类的管理
 *             接口：
 *             addprototype（管理参数） ，如（类编号，this）
 *             findandclone（管理参数） ，如（类编号）
 *             clone()；  子类需要实现这个接口
 * prototype子类： 实现子类创建
 *             static  prototype子类  l1;
 *             接口：
 *             默认构造函数()： 调用addprototype（管理参数）
 *             私有构造函数（类编号）： 主要为了给clone使用，必须和默认构造区分开
 *             clone（）： return new 私有构造函数（类编号）
 *
 * 类构造函数的  参数赋值和参数对类里变量的初始化的不同。
 *
 * explict 修饰类构造函数：表明不能使用类型隐式转换；
 *
 * 模版：类模版、函数模版（调用不用指定模版参数）、类成员函数模版
 *
 * 模版的特化和偏特化：特化指模版参数都写定；偏特化指模版参数指定了1个或多个，但未全制定
 * template<>
 * struct hash<char>{...}   // 特化
 *
 * template <typename T， typename Alloc=......>
 * class c{}
 *
 * template <typename Alloc=......>
 * class c<bool, Alloc> {}        //偏特化：模版参数个数上的偏特化
 *
 * template <typename T>
 * class c<T*> {}        //偏特化：模版参数范围上的偏特化，特化为指针
 *
 * 模版模版参数：
 * template <typename T,
 *           template <typename T>
 *             class container
 *          >
 * class xcls
 * {
 *  private:
 *      container<T> c;
 *  public:
 *      ......
 * }
 *
 * template <typename T>
 * using lst = List<T, allocator<T>>;
 *
 * xcls<string, lst> mylst2;
 *
 * 特别注意： 所有的模版和模版函数都必须写在一个文件内，其实也就是类声明和类定义都必须在一个.h文件内
 *
 * 仿函数：也就是操作符重载，重载（）操作符
 *
 * 虚函数产生的多态和对象的内存模型紧密相关，就是因为c++的对象模型中一旦有虚函数定义，就必然在对象模型的
 * 最开始有一个虚函数表指针，指向了虚函数地址表格。父类有一个自己的虚函数表指针（vptr），子类将完全继承
 * 父类的对象模型，并用一个子类自己的虚函数表指针覆盖掉父类的虚函数表指针(vptr)，指向一个根据子类实际
 * 情况创建的子类对应的虚函数表（里面包含子类重写的虚函数地址，也包括未重写的父类虚函数地址），总之对象
 * 模型中只会有一个虚函数表指针。程序碰到指针时（虚函数必须是指针调用，不能是实例调用），通过查询对象
 * 模型固定的虚函数表指针，实现多态。
 * （侯杰-面向对象-下-关于vptr和vtbl17描述了这个问题）
 *
 * operator new和operator delete的重载，可以用来实现内存池，但是一定要小心使用。  全局重载new，delete要十分小心；
 *
 *
 *
 *
 */



#include <templatetemplatepar.h>
#include <list>

#include <anothertemplatepar.h>

template <typename T>
using lst = std::list<T,allocator<T>>;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector<std::string>  tmp {"1","2","3","4","6"};
    auto i = find(tmp.begin(), tmp.end(),"1");
    if(i != tmp.end())
        cout << *i << endl;
    myprint("dfsdfsdf","gffg","sfdsfsdf","df6344sfsd");
    myprint1({1,2,3,4,5,6});


    std::cout << "templatetemplatepar" << std::endl;
    // 模版参数的模版类
    templatetemplatepar<int,lst> pp;  //管理方变更

    pp.Init({1,2,3,4,5});
    pp.MyPrint();

    std::cout << "anothertemplatepar" << std::endl;

    anothertemplatepar<int, std::vector<int>> an;  //管理方变更
    an.Init({1,2,3,4,4});
    an.MyPrint();

    return 0;

}
