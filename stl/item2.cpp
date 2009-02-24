#include <iostream>
#include <vector>

class Widget {
};

template <typename T>
SpecialAllocator {
    operator() () { return new T; }
};

typedef std::vector<Widget, SpecialAllocator<Widget> > WidgetContainer;
typedef WidgetContainer::iterator WCIterator;

int func()
{
    WidgetContainer cw;
    Widget bestWidget;

    WCIterator i = find(cw.begin(), cw.end(), bestWidget);
}

// ����ʹ��typedef
// �����Ҫ��������ķ�װ��������class
