#include <list>

class Widget {
};

template <typename T>                       // 一共用户定义的分配器
class SpecialAllocator {                    // 模板
};

typedef SpecialAllocator<Widget> SAW;

void func()
{
    std::list<Widget, SAW> L1;
    std::list<Widget, SAW> L2;

    L1.splice(L1.begin(), L2);              // 把L2的节点移到L1前端
}
