#ifndef __CHANNEL_WORK__
#define __CHANNEL_WORK__
#include <boost/function.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <list>
#include <string>

enum CHANNEL_STATE;
struct Request;
struct Response;
using boost::interprocess::message_queue;
using boost::interprocess::named_mutex;

const int MAX_NUM_MSG = 4096;
const int MAX_MSG_SIZE = 1024;

class Channel {
public:
	typedef boost::function<bool()> WorkType;

	Channel(int channel_id);
	Channel(const Channel& rhs);

	bool GetCallerId();
	bool OffHook();
	bool WaitRing();
	bool Init();
	bool PlayFile();
	bool StopPlay();
	bool WaitDtmf();
	bool HangUp();

	void CreateRequestQueue();
	void CreateResponseQueue();
    void CreateResponseMutex();
	bool GetRequest();
	bool PostResponse();

	void ResetChannel();

	void DoWork();
	WorkType GetWork();

private:
	typedef boost::shared_ptr<message_queue> MessageQueuePtr;
	typedef boost::shared_ptr<named_mutex> NamedMutexPtr;

	boost::shared_ptr<Response> resp;
	boost::shared_ptr<Request> req;
	std::list<std::string> play_list;

	int channel_id;
	std::string current_state;
	WorkType current_work;
	char QUEUE_BUFFER[MAX_MSG_SIZE];
	MessageQueuePtr request_queue;
	MessageQueuePtr response_queue;
    NamedMutexPtr response_mutex;
};
#endif
