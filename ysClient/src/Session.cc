#include "Session.h"
#include <ysvar.h>

Session::Session()
{
}
Session::~Session()
{
    for (BusIterator it = vec_in_bus.begin(); it != vec_in_bus.end(); ++it) {
        YSVarFree(*it);
        *it = NULL;
    }
}

void Session::in_bus_add( void* in_bus )
{
    vec_in_bus.push_back(in_bus);
}
