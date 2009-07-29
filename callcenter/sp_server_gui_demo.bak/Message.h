
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


//Ҫ���͵Ķ��е�ͷ
//const char* MSG_QUEUE_TAG=	"request_queue_";
#define MSG_QUEUE_TAG "response_queue_"

#define NAME_SHARE_MEM_TAG "monitor_shared_memory"
#define NAME_MUTEX_TAG "monitor_lock_shared_memory"

#define SHARE_MEM_SIZE (1024*10)

#define	 NAME_MEM ""

class CMessage
{
public:
	bool SendMsg(std::string queueName,std::string msg);
	bool SendStartMonitMsg(std::string queueName);
	bool SendStopMonitMsg(std::string queueName);
	bool SendExitMsg(std::string queueName);

};


class CShareMem
{
private:
	std::string m_szSMName;
	std::string m_szMutexName;	
	named_mutex* m_pMutex;
	//���������ڴ�����������գ���д��
	shared_memory_object* m_pSMObject;
	const std::size_t m_memSize ;
	//scoped_lock<named_mutex> m_lock;

public :
	CShareMem();
	~CShareMem();

	//��ȡ����
	bool Read(std::string& readData);
	bool ReadAndClear(std::string& readData);

	//д����
	void Write(std::string writeData);
	//��չ����ڴ�
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

#endif
