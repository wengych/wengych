
#ifndef __PROCESS_MANAGE_
#define __PROCESS_MANAGE_

#include <string>
#include <vector>

class CProcessManage
{
public :

	//����pid���жϽ����Ƿ����
	//return:	0:���� >0��Ӧ���̣�����pidΪ0��ϵͳ���̣���˴�����ʱ��϶����᷵��0������-1�Ļ����Ͳ���dword�����ˣ�
    static bool  IsProgramRunning(DWORD pid, std::string valid_process_name) ;
    static bool IsProgramRunning(const std::string& pid, std::string valid_process_name) ;
	//����ָ��λ�ý���
	//return:	0:���� >0��Ӧ���̣�����pidΪ0��ϵͳ���̣���˴�����ʱ��϶����᷵��0��
	static  DWORD  StartProgram(std::string strFile);

	
};


#endif