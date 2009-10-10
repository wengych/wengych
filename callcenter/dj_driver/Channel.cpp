#include <vector>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include "Channel.h"
#include "common.h"
#include "Request.h"
#include "Response.h"
#include "../Inc/tc08a32.h"
#include "../Inc/NewSig.h"

using namespace boost;
using namespace boost::interprocess;

const char* request_queue_name = "request_queue_";
const char* response_queue_name = "response_queue_";
const char* response_mutex_name = "response_queue_lock_";
char* WelcomFileName = "C:\\DJDBDK\\voc\\bank.001";

#define bool_cast lexical_cast<bool> 
#define pchar_cast lexical_cast<char*>
#define string_cast lexical_cast<std::string>

bool Channel::Init( )
{
	return true;
}

bool Channel::WaitRing( )
{
	if (RingDetect(channel_id)) {
		resp->argument_map["ring_in"] = "true";
		logger << "ring in.\n";
		return true;
	} else {
		return false;
	}
}

bool Channel::GetCallerId( )
{
	std::string caller_id;
	if (DtmfHit(channel_id)) {
        while (DtmfHit(channel_id)) {
			char c= ConvertDtmf(GetDtmfCode(channel_id));
            if (c != 'd')
                caller_id += c;
        }
	} else {
		char buff[128] = { 0 };
		GetCallerIDStr(channel_id, buff);

		caller_id = buff;
	}
	resp->argument_map["caller_id"] = caller_id;
	return true;
}

bool Channel::OffHook( )
{
	::OffHook(channel_id);
	::StartSigCheck(channel_id);

	return true;
}

bool Channel::Interphone()
{
    int interphone_id = boost::lexical_cast<int>(req->argument_map["interphone_id"]);

    if (Sig_CheckBusy(channel_id))
    {
        ::ClearLink(channel_id, interphone_id);

        ::FeedPower(interphone_id);
        ::StartPlaySignal(channel_id, SIG_STOP);

        ::HangUp(channel_id);

        resp->state = "USER_HANG_UP";

        first_in = true;
        off_hook = false;
        return true;
    }
    else if (first_in)
    {
        logger << "FeedRealRing.\n";
        ::FeedRealRing(interphone_id);
        first_in = false;
    }
    else if(off_hook)
    {
        if (HANG_UP_FLAG_TRUE == HangUpDetect(interphone_id))
        {
            logger << "HangUpDetect.\n";
            resp->argument_map["hang_up"] = "inter_phone";

            FeedPower(interphone_id);
            StartPlaySignal(channel_id, SIG_STOP);

            ::HangUp(channel_id);
            ::ClearLink(channel_id, interphone_id);

            first_in = true;
            off_hook = false;
            return true;
        }
    }
    else if (OffHookDetect(interphone_id))
    {
        logger << "OffHookDetect.\n";
        FeedPower(interphone_id);
        StartPlaySignal(channel_id, SIG_STOP);
        SetLink(channel_id, interphone_id);

        StartHangUpDetect(interphone_id);
        logger << "StartHangUpDetect.\n";

        off_hook = true;
    }

    return false;
}

bool Channel::PlayFile()
{
	if (Sig_CheckBusy(channel_id)) {
		if (req->argument_map["is_start"] == "true")
			::StopPlayFile(channel_id);
		::HangUp(channel_id);
		Sig_ResetCheck(channel_id);

		resp->state = "USER_HANG_UP";

		play_list.clear();
		::StopPlay(channel_id);

		return true;
	}

	if (req->argument_map["is_start"] != "true") {
		::InitDtmfBuf(channel_id);
		char_separator<char> sep(",");
		tokenizer<char_separator<char> > tok(req->argument_map["file_list"], sep);
		play_list.insert(play_list.end(), tok.begin(), tok.end());

		char file_name[256];
		strcpy_s(file_name, play_list.begin()->c_str());
		::StartPlayFile(channel_id, file_name, 0);
		play_list.pop_front();

		req->argument_map["is_start"] = "true";
		req->argument_map["is_end"] = "false";

		logger << "start play file.\n";
	} else if (::DtmfHit(channel_id)) {
		if (req->argument_map["block"] == "true") {
			::InitDtmfBuf(channel_id);
			return false;
		}
		resp.reset(new Response(current_state));
		resp->argument_map["is_start"] = req->argument_map["is_start"];
		resp->argument_map["is_end"] = req->argument_map["is_end"];
		resp->argument_map["dtmf_hit"] = "true";
		// resp->argument_map["user_input"] = string_cast(ConvertDtmf(::GetDtmfCode(channel_id)));

		logger << "dtmf hit while play file.\n";

		::StopPlay(channel_id);
		play_list.clear();

		return true;
	} else if (::CheckPlayEnd(channel_id)){
		if (play_list.empty()) {
			resp.reset(new Response(current_state));
			resp->argument_map["is_start"] = req->argument_map["is_start"];
			resp->argument_map["is_end"] = "true";

			logger << "end play file.\n";
			return true;
		} else {
			::StopPlayFile(channel_id);
			char file_name[256];
			strcpy_s(file_name, play_list.begin()->c_str());
			::StartPlayFile(channel_id, file_name, 0);
			play_list.pop_front();

			logger << "play next file.\n";
		}
	}

	return false;
}

bool Channel::StopPlay()
{
	::StopPlayFile(channel_id);

    logger << "Channel::StopPlay()\n";
	return true;
}

bool Channel::HangUp()
{
	::HangUp(channel_id);

	return true;
}

bool Channel::ClearDtmf()
{
    if (Sig_CheckBusy(channel_id))
    {
        ::HangUp(channel_id);
        ::Sig_ResetCheck(channel_id);

        resp->state = "USER_HANG_UP";

        return true;
    }

    ::InitDtmfBuf(channel_id);
    return true;
}

bool Channel::WaitDtmf()
{
	if (Sig_CheckBusy(channel_id)) {
		::HangUp(channel_id);
		Sig_ResetCheck(channel_id);

		resp->state = "USER_HANG_UP";

		return true;
	}

	char ch = -1;
	if (::DtmfHit(channel_id))
		ch = ConvertDtmf(::GetDtmfCode(channel_id));
	else 
		return false;

	if (ch != -1)
	{
		resp.reset(new Response(current_state));
		resp->argument_map["user_input"] = ch;

		logger << "user input: " << ch << "\n";

		return true;
	} else {
		return false;
	}
}

void Channel::CreateRequestQueue( )
{
	std::stringstream ss;
	ss << request_queue_name << channel_id;
	message_queue::remove(ss.str().c_str());
	request_queue.reset(new message_queue(open_or_create,
			ss.str().c_str(),
			MAX_NUM_MSG,
			sizeof(char) * MAX_MSG_SIZE
			)
		);

	logger << ss.str() << '\n';
}

void Channel::CreateResponseQueue( )
{
	std::stringstream ss;
	ss << response_queue_name << channel_id;
	message_queue::remove(ss.str().c_str());
	response_queue.reset(new message_queue(open_or_create,
			ss.str().c_str(),
			MAX_NUM_MSG,
			sizeof(char) * MAX_MSG_SIZE
			)
		);

	logger << ss.str() << '\n';
}

void Channel::CreateResponseMutex()
{
    std::stringstream ss;
    ss << response_mutex_name << channel_id;
    named_mutex::remove(ss.str().c_str());
    response_mutex.reset(new named_mutex(open_or_create,
        ss.str().c_str()));

    logger << ss.str() << '\n';
}

Channel::Channel( int _channel_id )
: channel_id(_channel_id)
{
	CreateRequestQueue();
	CreateResponseQueue();
    CreateResponseMutex();

	current_state = "";
	current_work = GetWork();

    first_in = true;
    off_hook = false;
}

Channel::Channel( const Channel& rhs )
: channel_id(rhs.channel_id),
current_state(rhs.current_state),
request_queue(rhs.request_queue),
response_queue(rhs.response_queue),
response_mutex(rhs.response_mutex),
first_in(rhs.first_in),
off_hook(rhs.off_hook)
{
	current_work = GetWork();
}

Channel::WorkType Channel::GetWork()
{

	if (current_state == "INIT")
		return bind(&Channel::Init, &(*this));
	if (current_state == "WAIT_RING")
		return bind(&Channel::WaitRing, &(*this));
	if (current_state == "GET_CALLER_ID")
		return bind(&Channel::GetCallerId, &(*this));
	if (current_state == "OFF_HOOK")
		return bind(&Channel::OffHook, &(*this));
	if (current_state == "STOP_PLAY")
		return bind(&Channel::StopPlay, &(*this));
	if (current_state == "PLAY_FILE")
		return bind(&Channel::PlayFile, &(*this));
	if (current_state == "WAIT_DTMF")
		return bind(&Channel::WaitDtmf, &(*this));
    if (current_state == "CLEAR_DTMF")
        return bind(&Channel::ClearDtmf, &(*this));
	if (current_state == "USER_HANG_UP")
		return bind(&Channel::HangUp, &(*this));
    if (current_state == "INTERPHONE")
        return bind(&Channel::Interphone, &(*this));

	return NULL;
}

void Channel::DoWork()
{
	/*
	if (current_work == NULL) {
		if (!GetRequest())
			return;
		current_work = GetWork();
		current_work();
	} else if (!req) {
	*/
	if (!current_work || !req) {
		if (!GetRequest())
			return;
		current_work = GetWork();
		resp.reset(new Response(current_state));
	} else if (req->argument_map["block"] == "true" && current_work) {
		// do work with block
		if (current_work()) {
			// work complete
			if (GetRequest()) {
				// has new request
				current_work = GetWork();
				resp.reset(new Response(current_state));
			} else {
				// will send response while work finish and there is no new request. 
				PostResponse();
				current_state = "";
				current_work = GetWork();
				resp.reset(/*NULL*/);
			}
		}
	} else if (current_work){
		// do work with non-block
		bool work_result = current_work();

		if (GetRequest()) {
			// has new request
			current_work = GetWork();
			resp.reset(new Response(current_state));
		} else if (work_result) {
			// work complete
			PostResponse();
			current_state = "";
			current_work = GetWork();
			resp.reset(/*NULL*/);
		}
	} else {
		// has request but have no work to do.
	}

}

// 非阻塞方式读取队列，读取成功后改变current_state并返回
// 失败则直接返回
bool Channel::GetRequest()
{
	size_t recvd_size;
	unsigned int priority;
	if (request_queue->try_receive(QUEUE_BUFFER, MAX_MSG_SIZE, recvd_size, priority)) {
		req.reset(new Request(QUEUE_BUFFER, recvd_size));
		current_state = req->state;
		return true;
	}

	return false;
}

bool Channel::PostResponse()
{
	using namespace boost::interprocess;

	scoped_lock<named_mutex> sc_lock(*response_mutex);
	return response_queue->try_send(resp->str().c_str(), resp->str().length(), 0);
}
