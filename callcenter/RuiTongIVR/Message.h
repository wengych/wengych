
#ifndef __MESSAGE_H_
#define __MESSAGE_H_

#include <string>
#include <boost/interprocess/ipc/message_queue.hpp>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

#include <vector>

using namespace boost::interprocess;
using namespace std;


//要发送的队列的头
//const char* MSG_QUEUE_TAG=	"request_queue_";
#define MSG_QUEUE_TAG "response_queue_"

#define NAME_SHARE_MEM_TAG "monitor_shared_memory"
#define NAME_MUTEX_TAG "monitor_lock_shared_memory"

#define SHARE_MEM_SIZE (1024*10)

#define	 NAME_MEM ""

class CMessage
{
public:
	static bool SendMsg(std::string queueName,std::string msg);
	static bool SendStartMonitMsg(std::string queueName);
	static bool SendStopMonitMsg(std::string queueName);
	static bool SendExitMsg(std::string queueName);
    static bool SendActiveMsg(std::string queueName);
    static std::string GetMutexName(const char channel_id);
};


class CShareMem
{
private:
	std::string m_szSMName;
	std::string m_szMutexName;	
	named_mutex* m_pMutex;
	//创建共享内存区，读、清空（即写）
	shared_memory_object* m_pSMObject;
	const std::size_t m_memSize ;
	//scoped_lock<named_mutex> m_lock;

public :
	CShareMem();
	~CShareMem();

	//读取数据
	bool Read(std::string& readData);
	bool ReadAndClear(std::string& readData);

	//写数据
	void Write(std::string writeData);
	//清空共享内存
	void Clear();
};

class CMemMsg
{
private:
	/*static*/ CShareMem m_sMem;
public:
	CMemMsg();
    bool Read(std::vector<std::string>& strVector);
    void Write(std::string str);
};

class CActiveFile
{
private:
    std::string m_fileName;
    //bool b_open;
public:
    CActiveFile(std::string fileName);
    bool GetPInfo(DWORD& pid,CTime& tm, std::string mutex_name);
    //CTime GetTime();
};

#endif
