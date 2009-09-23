#include <Windows.h>
#include <string>
#include "common.h"
#include "Channel.h"
#include "InterphonePool.h"
#include "../Inc/tc08a32.h"
#include "../Inc/NewSig.h"
#include <ostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <process.h>
#include <boost/interprocess/exceptions.hpp>

std::ostream& logger = std::cout;
typedef std::vector<Channel> ChannelArray;

void InitActiveFileLock()
{
    std::string lock_name = "_driver_lock";
    boost::interprocess::named_mutex::remove(lock_name.c_str());
}

void UpdateActiveFile()
{
    static int i = 0;
    const int COUNT = 10;

    if (++i >= COUNT) {
        using namespace boost::interprocess;

        named_mutex mutex(open_or_create, "_driver_lock");
        scoped_lock<named_mutex> sc_lock(mutex);

        std::string file_name = std::string("_driver");
        std::ofstream out_file;
        out_file.open(file_name.c_str(), std::ios_base::out | std::ios_base::trunc);

        time_t tm_t;
        out_file << getpid() << ":";

        out_file << time(&tm_t);

        i = 0;
    }
}

// Init system
ChannelArray InitLines()
{
	// GetVoicePath();
	ChannelArray Lines;// = new LINESTRUCT[TotalLine];
    InterphonePool::InitInterPhonePool();
    InterphonePool pool;
	SetBusyPara(350);
	WORD TotalLine = CheckValidCh();
 	for(int i=0; i < TotalLine; i++)
 	{
        if (CHTYPE_TRUNK == ::CheckChTypeNew(i))
        {
		    Lines.push_back(Channel(i));
		    InitDtmfBuf(i);
        }
        else if (CHTYPE_USER == ::CheckChTypeNew(i))
        {
            pool.AddChannel(i);
        }
 	}

	return Lines;
}

void DoWork(ChannelArray& lines)
{
	for (;;)
	{
		PUSH_PLAY();
		FeedSigFunc();
		for (ChannelArray::iterator it = lines.begin(); it != lines.end(); ++it)
			it->DoWork();

		Sleep (50);
        UpdateActiveFile();
	}
}

int main()
{
	try {
		DJDrv drv;
		DJCard card;
        ChannelArray lines = InitLines();
        InitActiveFileLock();
        UpdateActiveFile();
		Sig_Init(0);
		logger << "Init success!" << std::endl;

		DoWork(lines);
	} catch (const std::string& err) {
		logger << "Main catch an error." << std::endl;
		logger << err << std::endl;
		return 1;
	} catch (boost::interprocess::interprocess_exception& ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}
}
