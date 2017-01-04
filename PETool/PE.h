#pragma once
class CPE
{
public:
	CPE();
	~CPE();
	DWORD ReadPeFile(const char* szPath);//���ļ��ж�ȡPE�ļ�
	void GetPeStruct();//��ȡPE�ṹ��Ϣ
	DWORD RvaToRaw(DWORD dwRva);//�����ڴ��ַת�ļ���ַ
	DWORD RawToRva(DWORD dwRaw);//�ļ���ַת�����ڴ��ַ
	void Clear();
	void Init();
public:
	void *m_pFileMem;
	IMAGE_DOS_HEADER *m_pDosHead;//DOSͷ
	IMAGE_FILE_HEADER *m_pFileHead;//��׼peͷ
	IMAGE_OPTIONAL_HEADER32 *m_pOptionalHeader32;//32λ�Ŀ�ѡPEͷ
	IMAGE_OPTIONAL_HEADER64 *m_pOptionalHeader64;//64λ�Ŀ�ѡPEͷ
	IMAGE_SECTION_HEADER *m_pSection;//�����
	int m_nSection;//�������
	int m_nFileSize;//�ļ���С
	char m_szPath[MAX_PATH];//�ļ�·��
};
