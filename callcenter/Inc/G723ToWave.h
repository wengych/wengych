#ifndef _G723TOWAVE_H
#define _G723TOWAVE_H
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

//Mode- 0:6.3k 1:5.3K 
//����ֵ��ת�����WAVE���������ֽ���
//˵�����û��Լ�����InBuf��OutBuf�Ŀռ�.
//�����G.723(6.3K)�ģ���Ҫ��InBufΪ24���������ֽڣ������G.723(5.3K)����Ҫ��InBufΪ20���������ֽ�
//OutBuf�Ĵ�СӦΪ240*n���ֽڣ�n=(InBuf�ֽ���/24(��20)).
int WINAPI G723ToWave(char* InBuf,int iInBufSize,short int* OutBuf,int Mode);
int WINAPI WaveToG723(short* InBuf,int iInBufSize,char* OutBuf,int Mode);

//G723��ʽ�ļ���WAVE��ʽ�ļ���ת����
//G723File��g723�ļ���   WaveFile��ת����õ���WAVE�ļ����ļ���   Mode: 0:6.3k 1:5.3K
int WINAPI G723FToWaveF(char* G723File,char* WaveFile,int Mode);
int WINAPI WaveFToG723F(char* WaveFile,char* G723File,int Mode);

// add in 2005.12.15
int WINAPI G723ToWave_BufEx(char* InBuf,int iInBufSize,short int* OutBuf,int Mode, int InitFlag);

int WINAPI G723FToWaveFForMDR(char* G723File,char* WaveFile,int Mode,BOOL* CancelConvertFlag);


/*
#ifdef __cplusplus
}
#endif
*/

#endif