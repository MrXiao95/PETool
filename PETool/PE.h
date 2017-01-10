#pragma once
class CPE
{
public:
	CPE();
	~CPE();
	DWORD ReadPeFile(const char* szPath);//从文件中读取PE文件
	void GetPeStruct();//获取PE结构信息
	DWORD RvaToRaw(DWORD dwRva);//虚拟内存地址转文件地址
	DWORD RawToRva(DWORD dwRaw);//文件地址转虚拟内存地址
	void Clear();
	void Init();
	DWORD SaveFile(char* szPath, char *szBuf, int nFileSize);
	void TestAddCodeInNewSec(const char* szPath = NULL);
	void TestAddCodeInCodeSec(const char* szPath = NULL,int nSec = 0);
	DWORD FileBufToImageBuf(void **pImageBuf);
	DWORD ImageBufToFileBuf(void *pImageBuf, void **pFileBuf);
public:
	void *m_pFileMem;
	IMAGE_DOS_HEADER *m_pDosHead;//DOS头
	IMAGE_FILE_HEADER *m_pFileHead;//标准pe头
	IMAGE_OPTIONAL_HEADER32 *m_pOptionalHeader32;//32位的可选PE头
	IMAGE_OPTIONAL_HEADER64 *m_pOptionalHeader64;//64位的可选PE头
	IMAGE_SECTION_HEADER *m_pSectionHead;//区块表
	int m_nSection;//区块个数
	int m_nFileSize;//文件大小
	char m_szPath[MAX_PATH];//文件路径
};

