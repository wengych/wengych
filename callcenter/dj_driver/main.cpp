#include <Windows.h>
#include <string>
#include "common.h"
#include "Channel.h"
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

void UpdateActiveFile()
{
    static int i = 0;
    const int COUNT = 10;

    if (++i >= COUNT) {
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
	SetBusyPara(350);
	WORD TotalLine = CheckValidCh();
 	for(int i=0; i < TotalLine; i++)
 	{
		Lines.push_back(Channel(i));
		InitDtmfBuf(i);
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
