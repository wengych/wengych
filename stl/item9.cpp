#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <list>
#include <set>
#include <map>

bool badValue(int x)
{
    if (x == 100)
        return false;
    return true;
}

int main()
{
    // 想把容器中所有值为1963的对象都去掉
    // 删除badValue
    std::vector<int> vec;
    vec.erase(std::remove(vec.begin(), vec.end(), 1963), vec.end());
    vec.erase(std::remove_if(vec.begin(), vec.end(), badValue),
            vec.end());
    
    std::deque<int> dq;
    dq.erase(std::remove(dq.begin(), dq.end(), 1963), dq.end());
    dq.erase(std::remove_if(dq.begin(), dq.end(), badValue),
            dq.end());

    std::list<int> lst;
    lst.remove(1963);
    lst.remove_if(badValue);

    std::set<int> set;
    std::set<int> goodValues;

    set.erase(1963);
    // 容易编码
    remove_copy_if(set.begin(), set.end(),
            std::inserter(goodValues,
                goodValues.end()),
            badValue);
    set.swap(goodValues);
    // 更高效
    for (std::set<int>::iterator it = set.begin();
        it != set.end();)
    {
        if (badValue(*it)) {
            // logFile << "Eraseing " << *it << '\n';
            set.erase(it++);
        }
        else ++it;
    }

    return 0;
}

