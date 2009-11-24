#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

void print(int& a, const int b)
{
	a += b;
}

struct printx :
	binary_function<int, int, int>
{
	int operator() (int a, int b) const
	{
		cout << a + b << endl;
		return a + b;
	}
};

int main(int , char **)
{
	list<int> my_list;

	// for_each(my_list.begin(), my_list.end(), bind2nd(print, 3));
	// �����޷�ͨ��
	// ԭ��
	// for_each����Ҫʹ��functor��bind2nd�Ķ���Ҳ����Ҫʹ��functor�����Ǻ���
	// �����Ҫʹ��bind2nd����ô����Ҫ��binary_function�̳�
	// for_each���������޸�Ԫ�أ�������Ҫ���Ǵﲻ���ġ�

	vector<int> my;
	my.push_back(0);
	my.push_back(1);
	my.push_back(2);

	copy(my.begin(), my.end(), ostream_iterator<int>(cout, " "));
	cout << "\n---" << endl;

	for_each(my.begin(), my.end(), bind2nd(printx(), 3));
	cout << "\n---" << endl;
	copy(my.begin(), my.end(), ostream_iterator<int>(cout, " "));
	cout << "\n---" << endl;

	transform(my.begin(), my.end(), my.begin(), bind2nd(printx(), 3));
	cout << "\n---" << endl;
	copy(my.begin(), my.end(), ostream_iterator<int>(cout, " "));
	cout << "\n---" << endl;

	return 0;
}
