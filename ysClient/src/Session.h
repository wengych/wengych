#ifndef YS_SESSION_H_
#define YS_SESSION_H_

#include <vector>

typedef std::vector<void*> BusVector;
typedef BusVector::iterator BusIterator;

class Session
{
public:
    Session();
    ~Session();

    void in_bus_add(void*);

protected:
    BusVector vec_in_bus;
    void* main_bus;
};

#endif // YS_SESSION_H_
