#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>

template <class T>
struct print : public std::unary_function<T, void>
{
    print(std::ostream& out) : os(out), count(0) {}
    void operator() (T x) { os << x << ' '; ++count; }
    std::ostream& os;
    int count;
};

int main(int,char**)
{
    using namespace std;

    ifstream dataFile("ints.dat");
    /*
    list<int> data(istream_iterator<int>(dataFile), // ���棡����ɵĲ���
            istream_iterator<int>());               // ���������������
    */
    list<int> data((istream_iterator<int>(dataFile)),
            istream_iterator<int>());

    std::for_each(data.begin(), data.end(), print<int>(std::cout));
    std::cout << std::endl;

    return 0;
}

