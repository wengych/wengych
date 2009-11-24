#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

class Widget
{
};

typedef list<Widget*> WidgetPtrs;
typedef WidgetPtrs::iterator WidgetIterator;

bool isInteresting(const Widget *pw)
{
	return true;
}

int main(int , char **)
{
	WidgetPtrs widgetPtrs;

	WidgetIterator it = find_if(widgetPtrs.begin(), widgetPtrs.end(),
		not1(ptr_fun(isInteresting)));
	if (it != widgetPtrs.end())
	{
		cout << "find it";
	}

	return 0;
}
