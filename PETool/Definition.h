#ifndef __DEFINITION_H__
#define __DEFINITION_H__

#define SafeDelete(p) if(p){delete p;p=NULL;}

#define MAINWINDOWTITLE L"PETool"


#define WM_USER_SHOWEXPORTDIRCTORY WM_USER + 101
// typedef struct FILEINFO
// {
// 	char szPath[MAX_PATH];//�ļ�·��
// 	WORD Machine;//����ƽ̨
// 	//PE�ļ�ͷ��ַ  ��0x000000E0
// 	//����ַ        ��0x01000000
// 	//��ڵ�EP(RVA) ��0x0000739D
// 	//��ڵ�OEP(RAW)��0x0000679D
// 	//��ڵ�EP���ڽڣ�[.text][1 / 3]
// 	//������Ŀ      ��3 ��
// 	//�������汾��Ϣ��7.10
// 	//��ϵͳ
// }FILEINFO,*PFILEINFO;

#endif // !__DEFINITION_H__

