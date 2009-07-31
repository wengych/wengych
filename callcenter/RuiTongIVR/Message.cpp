
#include "stdafx.h"
#include "Message.h"
#include <boost/tokenizer.hpp>
#include <boost/interprocess/exceptions.hpp>

bool CMessage::SendMsg(std::string queueName,std::string msg)
{
	bool ret = false;

	try{
		//Open a message queue.
		message_queue mq(open_only ,queueName.c_str());
        named_mutex mutex(open_only, GetMutexName(*queueName.rbegin()).c_str());
        scoped_lock<named_mutex> sc_lck(mutex);

		return mq.try_send(msg.c_str(),msg.length(),0);
	}
	catch(interprocess_exception &ex){
		//message_queue::remove("message_queue");
		GLog("发送消息[%s]给app:[%s]时错误，err:[%s]",msg.c_str(),queueName.c_str(),ex.what());
		//std::cout << ex.what() << std::endl;
	}
	return ret;
}

bool CMessage::SendStartMonitMsg(std::string queueName)
{
	//Response:StartMonit
	return true;
}

bool CMessage::SendStopMonitMsg(std::string queueName)
{
	//Response:StopMonit
	return true;
}

//告诉子进程退出
bool CMessage::SendExitMsg(std::string queueName)
{
	//Response:EXIT
	std::string msg = "Response:EXIT";
	return CMessage::SendMsg(queueName,msg);
}

bool CMessage::SendActiveMsg(std::string queueName)
{
    //Response:ACTIVE_CHECK
    std::string msg = "Response:ACTIVE_CHECK";
    return CMessage::SendMsg(queueName,msg);
}

std::string CMessage::GetMutexName( const char channel_id )
{
    return std::string("response_queue_lock_") + channel_id;
}
//////////////////////////////////////////////////////////////////////////

CShareMem::CShareMem():m_memSize(SHARE_MEM_SIZE)
{
	m_szSMName = NAME_SHARE_MEM_TAG;// +name;
	m_szMutexName = NAME_MUTEX_TAG;// +name;

	try
	{
		shared_memory_object::remove(m_szSMName.c_str());
		named_mutex::remove(m_szMutexName.c_str()); 
		
		//创建mutex
		m_pMutex = new named_mutex(open_or_create,m_szMutexName.c_str());
		{
			scoped_lock<named_mutex> lock(*m_pMutex);
			if (lock)
			{
				m_pSMObject = new shared_memory_object(open_or_create, m_szSMName.c_str(), read_write);
				m_pSMObject->truncate(m_memSize);
                LogWrapper::Info("create mutex or shared_memory succeed, :%s",m_szSMName.c_str());
    		}
		}	
	}
	catch (interprocess_exception& err)
	{
		LogWrapper::Info("create mutex or shared_memory failed,err :%s",err.what());
	}

}

CShareMem::~CShareMem()
{
	named_mutex::remove(m_szMutexName.c_str()); 
	shared_memory_object::remove(m_szSMName.c_str());
	delete m_pSMObject;
	delete m_pMutex;
	m_pMutex = NULL;
	m_pSMObject = NULL;
}

bool CShareMem::Read(std::string& readData)
{
	bool ret =false;
	if (m_pSMObject != NULL && m_pSMObject->get_mode() != invalid_mode)
	{
		scoped_lock<named_mutex> lock(*m_pMutex,try_to_lock);
		if (lock)
		{//加锁成功
			mapped_region region(*m_pSMObject, read_only);

			char *mem = static_cast<char*>(region.get_address());
			readData = mem;
			ret = true;
		}
	}
	return ret;
}

bool CShareMem::ReadAndClear(std::string& readData)
{
	bool ret =false;
	if (m_pSMObject != NULL && m_pSMObject->get_mode() != invalid_mode)
	{
		scoped_lock<named_mutex> lock(*m_pMutex,try_to_lock);
		if (lock)
		{//加锁成功
			mapped_region region(*m_pSMObject, read_write);

			char *mem = static_cast<char*>(region.get_address());
			readData = mem;
			//int iSize = region.get_size();
			std::memset(region.get_address(), 0x00, region.get_size());
			ret = true;
		}
	}
	return ret;
}


void CShareMem::Clear()
{
	if (m_pSMObject != NULL && m_pSMObject->get_mode() != invalid_mode)
	{
		scoped_lock<named_mutex> lock(*m_pMutex,try_to_lock);
		if (lock)
		{//加锁成功
			mapped_region region(*m_pSMObject,read_write);

			std::memset(region.get_address(), 0x00, region.get_size());
		}
	}	
}

void CShareMem::Write(std::string writeData)
{
	if (m_pSMObject != NULL 
		&& m_pSMObject->get_mode() != invalid_mode 
		&& writeData.size() <=m_memSize)
	{
		scoped_lock<named_mutex> lock(*m_pMutex,try_to_lock);
		if (lock)
		{//加锁成功
			mapped_region region(*m_pSMObject,read_write);

			char *mem = static_cast<char*>(region.get_address());
			std::memcpy(region.get_address(),writeData.c_str(), writeData.size());
			//std::memset(region.get_address(),writeData.c_str(), writeData.size());
		}
	}	
}

//////////////////////////////////////////////////////////////////////////

CMemMsg::CMemMsg()
{
}

// CShareMem CMemMsg::m_sMem(NAME_MEM);

bool CMemMsg::Read(std::vector<std::string>& strVector)
{
	std::string readData;
	if (!m_sMem.ReadAndClear(readData))
        return false;

	GLog("接收到数据:\n%s",readData.c_str());
	// 读取的数据类型:
	// 共享内存区的数据格式为:
	// app:n:通道状态:电话号码
	//		n为通道号
	typedef boost::char_delimiters_separator<char> separator;
	typedef boost::tokenizer<separator>            tokenizer;
	separator sep(true, "", ":\n");
	tokenizer tok(readData, sep);
	for (tokenizer::iterator i = tok.begin();
		i != tok.end();
		++i)
	{    
		strVector.push_back(*i);
	}
	if (strVector.size() >0)
		return true;

    return false;
}


void CMemMsg::Write(std::string str)
{
	m_sMem.Write(str);
}

//////////////////////////////////////////////////////////////////////////

CActiveFile::CActiveFile(std::string fileName)
{
    m_fileName = fileName;
	// m_mutexName = fileName.substr(fileName.find_last_of("\\") + 1) + "_lock";
}

bool CActiveFile::GetPInfo(DWORD& pid, CTime& tm, std::string mutex_name)
{
    named_mutex mutex(open_or_create, mutex_name.c_str());
    CFile myfile;

    scoped_lock<named_mutex> sc_lock(mutex);
    if (myfile.Open(m_fileName.c_str(),CFile::modeRead ))
    {//打开成功
        char fileBuf[1024*4] = {0x00};
        myfile.Read(fileBuf,1024*4);
        std::string fileData = fileBuf;
        // 时间
        std::string segData = fileData.substr(fileData. find_last_of(":")+1);
        time_t tt = atol(segData.c_str());
        tm = CTime(tt);
        
        // 进程id
        segData = fileData.substr(0, fileData.find_last_of(":"));
        pid = atol(segData.c_str());
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////