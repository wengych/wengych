#include <iostream>
#include <vector>

class Widget {
public:
    // ...
    Widget(const Widget&);                  // 拷贝构造函数
    widget& operator=(const Widget&);       // 拷贝赋值操作符
    // ...
};

typedef std::vector<Widget> WidgetContainer;
typedef WidgetContainer::iterator WCIterator;

void func()
{
    WidgetContainer cw;
    class SpecialWidget : public Widget { };

    SpecialWidget sw;
    cw.push_back(sw);       // sw被当作基类对象拷入vw
                            // 当拷贝时它的特殊部分丢失了
                            // 建立指针的容器而不是对象的容器来处理此类问题
}

// STL容器使用了拷贝，但是它提供了更灵活的用法
