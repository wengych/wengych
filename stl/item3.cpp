#include <iostream>
#include <vector>

class Widget {
public:
    // ...
    Widget(const Widget&);                  // �������캯��
    widget& operator=(const Widget&);       // ������ֵ������
    // ...
};

typedef std::vector<Widget> WidgetContainer;
typedef WidgetContainer::iterator WCIterator;

void func()
{
    WidgetContainer cw;
    class SpecialWidget : public Widget { };

    SpecialWidget sw;
    cw.push_back(sw);       // sw���������������vw
                            // ������ʱ�������ⲿ�ֶ�ʧ��
                            // ����ָ������������Ƕ���������������������
}

// STL����ʹ���˿������������ṩ�˸������÷�
