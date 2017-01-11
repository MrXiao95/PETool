#ifndef __DEFINITION_H__
#define __DEFINITION_H__

#define SafeDelete(p) if(p){delete p;p=NULL;}

#define MAINWINDOWTITLE L"PETool"


#define WM_USER_SHOWEXPORTDIRCTORY WM_USER + 101
// typedef struct FILEINFO
// {
// 	char szPath[MAX_PATH];//文件路径
// 	WORD Machine;//运行平台
// 	//PE文件头地址  ：0x000000E0
// 	//基地址        ：0x01000000
// 	//入口点EP(RVA) ：0x0000739D
// 	//入口点OEP(RAW)：0x0000679D
// 	//入口点EP所在节：[.text][1 / 3]
// 	//区段数目      ：3 个
// 	//链接器版本信息：7.10
// 	//子系统
// }FILEINFO,*PFILEINFO;

#endif // !__DEFINITION_H__

