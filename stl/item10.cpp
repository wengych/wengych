#include <list>

class Widget {
};

template <typename T>                       // һ���û�����ķ�����
class SpecialAllocator {                    // ģ��
};

typedef SpecialAllocator<Widget> SAW;

void func()
{
    std::list<Widget, SAW> L1;
    std::list<Widget, SAW> L2;

    L1.splice(L1.begin(), L2);              // ��L2�Ľڵ��Ƶ�L1ǰ��
}
