#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

struct DeferenceLess
{
	template <typename PtrType>
	bool operator() (const PtrType *pT1,
		const PtrType *pT2) const
	{
		return *pT1 < *pT2;
	}
};

struct StringPtrLess :
	public binary_function<const string*, const string*, bool>
{
	bool operator() (const string* ps1, const string* ps2) const
	{
		return *ps1 < *ps2;
	}
};

typedef set<string*, DeferenceLess> StringSet;
typedef StringSet::const_iterator StringSetIterator;

void InitSet(StringSet& ssp)
{
	ssp.insert(new string("Anteater"));
	ssp.insert(new string("Wombat"));
	ssp.insert(new string("Lemur"));
	ssp.insert(new string("Penguin"));
}

void ReleaseSet(StringSet& ssp)
{
	for (StringSetIterator it = ssp.begin();
		it != ssp.end();)
	{
		delete (*it);
		ssp.erase(it++);
	}
}

void print(string* ps)
{
	cout << *ps << endl;
}

int main(int , char **)
{
	StringSet ssp;
	InitSet(ssp);

	for_each(ssp.begin(), ssp.end(), print);
	/*
	for (StringSetIterator it = ssp.begin();
		it != ssp.end();
		++it)
		cout << *(*it) << endl;
	*/

	ReleaseSet(ssp);

	return 0;
}
