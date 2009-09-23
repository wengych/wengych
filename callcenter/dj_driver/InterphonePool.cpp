#include "InterphonePool.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <process.h>
#include <boost/lexical_cast.hpp>
#include <string>
#include <map>
#include <algorithm>

std::string interphonepool_shared_memory_name = "interphonepool_shared_memory";
std::string interphonepool_lock_shared_memory_name = "interphonepool_lock_shared_memory";

InterphonePool::InterphonePool(void)
{

}

InterphonePool::~InterphonePool(void)
{
}

void InterphonePool::AddChannel( int id )
{
    std::string buff(boost::lexical_cast<std::string>(id));
    buff += ",a"; // a: available, u unavailable
    buff += '\n';

    using namespace boost::interprocess;

    named_mutex mutex(open_only, interphonepool_lock_shared_memory_name.c_str());
    scoped_lock<named_mutex> lock(mutex);

    shared_memory_object shared_memory(open_only, interphonepool_shared_memory_name.c_str(), read_write);
    mapped_region region(shared_memory, read_write);

    char* mem = static_cast<char*>(region.get_address());

    strcat(mem, buff.c_str());
}

void InterphonePool::ModifyChannel( int id, bool status )
{
    using namespace boost::interprocess;
    std::string str_channel_id = boost::lexical_cast<std::string>(id);

    named_mutex mutex(open_only, interphonepool_lock_shared_memory_name.c_str());
    scoped_lock<named_mutex> lock(mutex);

    shared_memory_object shared_memory(open_only, interphonepool_shared_memory_name.c_str(), read_write);
    mapped_region region(shared_memory, read_write);

    char* mem = static_cast<char*>(region.get_address());
    std::string str(mem);

    int pre_line_pos = 0;
    int next_line_pos = str.find_first_of('\n', pre_line_pos);

    while (next_line_pos != -1)
    {
        if (0 == str.compare(pre_line_pos, str_channel_id.length(), str_channel_id))
        {
            int pos = pre_line_pos + str_channel_id.length() + 1;
            if (status)
                mem[pos] = 'a';
            else
                mem[pos] = 'u';
            break;
        }

        pre_line_pos = next_line_pos + 1;
        next_line_pos = str.find_first_of('\n', pre_line_pos);
    }

}

int InterphonePool::GetRandomAvailableChannel()
{
    time_t tm;
    time(&tm);

    using namespace boost::interprocess;
    typedef std::map<int/*channel_id*/, char*/*Status*/> InterphoneStatusMap;
    InterphoneStatusMap interphone_status_map;

    named_mutex mutex(open_only, interphonepool_lock_shared_memory_name.c_str());
    scoped_lock<named_mutex> lock(mutex);

    shared_memory_object shared_memory(open_only, interphonepool_shared_memory_name.c_str(), read_write);
    mapped_region region(shared_memory, read_write);

    char* mem = static_cast<char*>(region.get_address());
    std::string str(mem);

    int pre_line_pos = 0;
    int next_line_pos = str.find_first_of('\n', pre_line_pos);
    while(next_line_pos != -1)
    {
        std::string channel_id = str.substr(pre_line_pos,
            str.find_first_of(",", pre_line_pos, next_line_pos - pre_line_pos) - pre_line_pos);
        int id = boost::lexical_cast<int>(channel_id);
        std::string status = str.substr(pre_line_pos + channel_id.length() + 1, 1);

        if (status == "a")
            interphone_status_map[id] = mem + pre_line_pos + channel_id.length() + 1;

        pre_line_pos = next_line_pos + 1;
        next_line_pos = str.find_first_of('\n', pre_line_pos);
    }

    int rnd = tm % interphone_status_map.size();

    InterphoneStatusMap::iterator it = interphone_status_map.begin();
    while (--rnd > 0 && it != interphone_status_map.end())
        ++it;

    if (it == interphone_status_map.end())
        it = interphone_status_map.begin();

    *(it->second) = 'u';
    return it->first;
}

void InterphonePool::InitInterPhonePool()
{
    using namespace boost::interprocess;

    named_mutex mutex(open_or_create, interphonepool_lock_shared_memory_name.c_str());
    scoped_lock<named_mutex> lock(mutex);

    shared_memory_object shared_memory(open_or_create, interphonepool_shared_memory_name.c_str(), read_write);

    shared_memory.truncate(10 * 1024);
}