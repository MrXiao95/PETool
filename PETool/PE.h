#pragma once
class CPE
{
public:
	CPE();
	~CPE();
	DWORD ReadPeFile(const char* szPath);//���ļ��ж�ȡPE�ļ�
	void GetPeStruct();//��ȡPE�ṹ��Ϣ
	DWORD RvaToFoa(DWORD dwRva);//�����ڴ��ַת�ļ���ַ
	DWORD FoaToRva(DWORD dwFoa);//�ļ���ַת�����ڴ��ַ
	void Clear();
	void Init();
	DWORD SaveFile(char* szPath, char *szBuf, int nFileSize);
	void TestAddCodeInNewSec(const char* szPath = NULL);
	void TestAddCodeInCodeSec(const char* szPath = NULL,int nSec = 0);
	DWORD FileBufToImageBuf(void **pImageBuf);
	DWORD ImageBufToFileBuf(void *pImageBuf, void **pFileBuf);
	char* GetSectionNameOfRAV(DWORD rva);
public:
	void *m_pFileMem;
	IMAGE_DOS_HEADER *m_pDosHead;//DOSͷ
	IMAGE_FILE_HEADER *m_pFileHead;//��׼peͷ
	IMAGE_OPTIONAL_HEADER32 *m_pOptionalHeader32;//32λ�Ŀ�ѡPEͷ
	IMAGE_OPTIONAL_HEADER64 *m_pOptionalHeader64;//64λ�Ŀ�ѡPEͷ
	IMAGE_SECTION_HEADER *m_pSectionHead;//�����
	int m_nSection;//�������
	int m_nFileSize;//�ļ���С
	char m_szPath[MAX_PATH];//�ļ�·��
};

