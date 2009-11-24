#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>

const int SOME_MAGIC_NUMBER = 10;
class Widget {};
typedef std::vector<Widget*> WidgetPointers;
typedef WidgetPointers::iterator WPIterator;

typedef boost::shared_ptr<Widget> WidgetPtr;
typedef std::vector<WidgetPtr> WidgetPtrs;

// template <typename T>
struct DeleteObject
//     : public unary_function<const T*, void>
{
    template <typename T>
    void operator() (const T* ptr) const
    {
        delete ptr;
    }
};

void Init(WidgetPointers& vwp)
{
    for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
        vwp.push_back(new Widget);
}

void Release(WidgetPointers& vwp)
{
    /*
    for (WPIterator it = vwp.begin(),
        it != vwp.end(),
        ++it)
    {
        delete *it;
    }
    */

    std::for_each(vwp.begin(), vwp.end(), DeleteObject());
}

int main(int, char**)
{
    return 0;
}

