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

// 尽量使用typedef
// 如果需要更大火力的封装，就是用class
