#include "stdafx.h"
#include "PE.h"
#include "Definition.h"

CPE::CPE()
{
	Init();
}


CPE::~CPE()
{
	Clear();
}

DWORD CPE::ReadPeFile(const char* szPath)
{
	Clear();
	Init();
	FILE *pFile = NULL;

	fopen_s(&pFile, szPath, "rb");
	if (pFile == NULL)
	{
		return 0;
	}
	fseek(pFile, 0, SEEK_END);
	m_nFileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	void *pTmp = NULL;
	pTmp = malloc(m_nFileSize);
	if (pTmp == NULL)
	{
		fclose(pFile);
		return 0;
	}
	memset(pTmp, 0, m_nFileSize);
	fread(pTmp, m_nFileSize, 1, pFile);
	fclose(pFile);
	m_pFileMem = pTmp;
	pTmp = NULL;
	GetPeStruct();
	strcpy_s(m_szPath, szPath);
	return m_nFileSize;
}

void CPE::GetPeStruct()
{
	if (*(PWORD)m_pFileMem != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(NULL,L"不是有效的PE文件",L"错误",MB_OK);
		return;
	}
	m_pDosHead = (IMAGE_DOS_HEADER*)m_pFileMem;
	if (*(PDWORD)((byte*)m_pFileMem+m_pDosHead->e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		MessageBox(NULL, L"不是有效的PE文件", L"错误", MB_OK);
		return;
	}
	m_pFileHead = (IMAGE_FILE_HEADER*)((byte*)m_pFileMem + m_pDosHead->e_lfanew + sizeof(DWORD));
	if (m_pFileHead->Machine == IMAGE_FILE_MACHINE_I386)
	{
		m_pOptionalHeader32 = (IMAGE_OPTIONAL_HEADER32*)((byte*)m_pFileMem + m_pDosHead->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER));
		m_pSectionHead = (IMAGE_SECTION_HEADER *)((byte*)m_pOptionalHeader32 + m_pFileHead->SizeOfOptionalHeader);
	}
	else if (m_pFileHead->Machine == IMAGE_FILE_MACHINE_IA64 || m_pFileHead->Machine == IMAGE_FILE_MACHINE_AMD64)
	{
		m_pOptionalHeader64 = (IMAGE_OPTIONAL_HEADER64*)((byte*)m_pFileMem + m_pDosHead->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER));
		m_pSectionHead = (IMAGE_SECTION_HEADER *)((byte*)m_pOptionalHeader64 + m_pFileHead->SizeOfOptionalHeader);
	}
	m_nSection = m_pFileHead->NumberOfSections;
}

void CPE::Clear()
{
	SafeDelete(m_pFileMem);
	m_pDosHead = NULL;
	m_pFileHead = NULL;
	m_pOptionalHeader32 = NULL;
	m_pOptionalHeader64 = NULL;
	m_pSectionHead = NULL;
	m_nSection = 0;
	m_nFileSize = 0;
}

void CPE::Init()
{
	m_pFileMem = NULL;
	m_pDosHead = NULL;
	m_pFileHead = NULL;
	m_pOptionalHeader32 = NULL;
	m_pOptionalHeader64 = NULL;
	m_pSectionHead = NULL;
	m_nSection = 0;
	m_nFileSize = 0;
	memset(m_szPath, 0, MAX_PATH);
}

DWORD CPE::RvaToFoa(DWORD dwRva)
{
	DWORD dwFoa = 0;
	
	for (int i = 0; i < m_nSection; i++)
	{
		if (dwRva >= m_pSectionHead[i].VirtualAddress && dwRva <= m_pSectionHead[i].VirtualAddress + m_pSectionHead[i].SizeOfRawData)
		{
			dwFoa = dwRva - m_pSectionHead[i].VirtualAddress + m_pSectionHead[i].PointerToRawData;
			break;
		}
	}
	return dwFoa;
}

DWORD CPE::FoaToRva(DWORD dwFoa)
{
	DWORD dwRva = 0;
	DWORD dwImageBase = 0;
	if (m_pOptionalHeader32)
	{
		dwImageBase = m_pOptionalHeader32->ImageBase;
	}
	else
	{
		dwImageBase = m_pOptionalHeader64->ImageBase;
	}

	for (int i=0;i<m_nSection;i++)
	{
		if (dwFoa>=m_pSectionHead[i].PointerToRawData && dwFoa<=m_pSectionHead[i].PointerToRawData + m_pSectionHead[i].SizeOfRawData)
		{
			dwRva = dwFoa - m_pSectionHead[i].PointerToRawData + dwImageBase;
			break;
		}
	}
	return dwRva;
}

void CPE::TestAddCodeInCodeSec(const char* szPath,int nSec)
{
	char szShellCode[] = { 0x6a,0x00,0x6a,0x00, 0x6a,0x00, 0x6a,0x00,
		0xE8,0x00,0x00,0x00,0x00,
		0xE9,0x00,0x00,0x00,0x00 };

	IMAGE_DOS_HEADER *pDos = NULL;
	IMAGE_NT_HEADERS *pNtHead = NULL;
	IMAGE_SECTION_HEADER *pSectionHead = NULL;
	void *pImageBuf = NULL;
	void *pFileBuf = NULL;
	if (szPath != NULL)
	{
		ReadPeFile(szPath);
	}

	if (0 == FileBufToImageBuf(&pImageBuf))
	{
		return;
	}
	pDos = (IMAGE_DOS_HEADER*)pImageBuf;
	pNtHead = (IMAGE_NT_HEADERS*)(pDos->e_lfanew + (byte*)pImageBuf);
	pSectionHead = (IMAGE_SECTION_HEADER*)((byte*)&pNtHead->OptionalHeader + pNtHead->FileHeader.SizeOfOptionalHeader);
	if (pSectionHead->SizeOfRawData < pSectionHead->Misc.VirtualSize + sizeof(szShellCode))
	{
		return;
	}
	void* beginCode = (byte*)pImageBuf + pSectionHead->VirtualAddress + pSectionHead->Misc.VirtualSize;
	memcpy(beginCode, szShellCode, sizeof(szShellCode));
	//修正E8
	int pMsgBox = (int)MessageBox;
	DWORD e8Next = (((byte*)beginCode + 13 - pImageBuf) + pNtHead->OptionalHeader.ImageBase);
	DWORD e8Add = pMsgBox - e8Next;
	memcpy((byte*)beginCode + 9, &e8Add, sizeof(e8Add));
	//修正E9
	DWORD e9Next = (((byte*)beginCode + 18 - pImageBuf) + pNtHead->OptionalHeader.ImageBase);
	DWORD e9Add = (pNtHead->OptionalHeader.AddressOfEntryPoint + pNtHead->OptionalHeader.ImageBase) - e9Next;
	memcpy((byte*)beginCode + 14, &e9Add, sizeof(e9Add));
	//修改OEP
	pNtHead->OptionalHeader.AddressOfEntryPoint = (DWORD)((byte*)beginCode - pImageBuf);
	int nSize = ImageBufToFileBuf(pImageBuf, &pFileBuf);
	if (0 == nSize)
	{
		MessageBox(NULL, L"内存镜像转文件镜像失败", L"错误", MB_OK);
		return;
	}
	char szNewPath[MAX_PATH] = { 0 };
	memcpy(szNewPath, m_szPath, MAX_PATH);
	strcat_s(szNewPath, "_InsertCode.exe");
	SaveFile(szNewPath, (char*)pFileBuf, nSize);
	free(pImageBuf);
	free(pFileBuf);
}

void CPE::TestAddCodeInNewSec(const char* szPath)
{
	char szShellCode[] = { 0x6a,0x00,0x6a,0x00, 0x6a,0x00, 0x6a,0x00,
		0xE8,0x00,0x00,0x00,0x00,
		0xE9,0x00,0x00,0x00,0x00 };
	if (szPath != NULL)
	{
		ReadPeFile(szPath);
	}
	IMAGE_DOS_HEADER *pDos = NULL;
	IMAGE_NT_HEADERS *pNtHead = NULL;
	IMAGE_SECTION_HEADER *pSectionHead = NULL;

	void *pImageBuf = NULL;
	void *pFileBuf = NULL;

	int nImageSize = FileBufToImageBuf(&pImageBuf);
	if (0 == nImageSize)
	{
		return;
	}
	pDos = (IMAGE_DOS_HEADER*)pImageBuf;
	pNtHead = (IMAGE_NT_HEADERS*)(pDos->e_lfanew + (byte*)pImageBuf);
	pSectionHead = (IMAGE_SECTION_HEADER*)((byte*)&pNtHead->OptionalHeader + pNtHead->FileHeader.SizeOfOptionalHeader);
	//判断节表空间够不够 不够就往前面挪

	char szTmpBuf[80] = { 0 };
	memcpy(szTmpBuf, pSectionHead + pNtHead->FileHeader.NumberOfSections, sizeof(szTmpBuf));
	bool bIsNull = true;
	for (int i = 0; i < 80; i++)
	{
		if (szTmpBuf[i] != '\0')
		{
			bIsNull = false;
			break;
		}
	}
	if (!bIsNull)//空间不够 得把PE头前移
	{
		void *NewPeHead = pDos + 1;
		int nOldSise = (byte*)pNtHead - (byte*)(pDos + 1);
		memcpy(NewPeHead, pNtHead, sizeof(IMAGE_NT_HEADERS) + (sizeof(IMAGE_SECTION_HEADER)*pNtHead->FileHeader.NumberOfSections));

		pDos = (IMAGE_DOS_HEADER*)pImageBuf;
		int nNew = (byte*)(pDos + 1) - (byte*)pDos;
		pDos->e_lfanew = nNew;
		pNtHead = (IMAGE_NT_HEADERS*)(pDos->e_lfanew + (byte*)pImageBuf);
		pSectionHead = (IMAGE_SECTION_HEADER*)((byte*)&pNtHead->OptionalHeader + pNtHead->FileHeader.SizeOfOptionalHeader);
		memset(pSectionHead + pNtHead->FileHeader.NumberOfSections, 0, nOldSise);
	}

	//在文件后面插入4096个字节 做为新的节
	void *pNewImage = malloc(nImageSize + 4096);
	memset(pNewImage, 0, nImageSize + 4096);
	memcpy(pNewImage, pImageBuf, nImageSize);
	free(pImageBuf);
	pImageBuf = NULL;
	pDos = (IMAGE_DOS_HEADER*)pNewImage;
	pNtHead = (IMAGE_NT_HEADERS*)(pDos->e_lfanew + (byte*)pNewImage);
	pSectionHead = (IMAGE_SECTION_HEADER*)((byte*)&pNtHead->OptionalHeader + pNtHead->FileHeader.SizeOfOptionalHeader);

	//将代码节复制到最后作为新的节
	IMAGE_SECTION_HEADER *pNewSectionHead = pSectionHead + pNtHead->FileHeader.NumberOfSections;
	memcpy(pNewSectionHead, pSectionHead, sizeof(IMAGE_SECTION_HEADER));
	//改节表的内容
	int nNumberOfSections = pNtHead->FileHeader.NumberOfSections - 1;
	memcpy(pNewSectionHead->Name, "newSec", 6);
	pNewSectionHead->Misc.VirtualSize = 4096;
	pNewSectionHead->PointerToRawData = pSectionHead[nNumberOfSections].PointerToRawData + pSectionHead[nNumberOfSections].SizeOfRawData;
	pNewSectionHead->SizeOfRawData = 4096;
	pNewSectionHead->VirtualAddress = pNtHead->OptionalHeader.SizeOfImage;
	pNtHead->OptionalHeader.SizeOfImage += 4096;
	pNtHead->FileHeader.NumberOfSections += 1;

	//插入代码
	void* beginCode = (byte*)pNewImage + pNewSectionHead->VirtualAddress;
	memcpy(beginCode, szShellCode, sizeof(szShellCode));
	//修正E8
	int pMsgBox = (int)MessageBox;
	DWORD e8Next = (((byte*)beginCode + 13 - pNewImage) + pNtHead->OptionalHeader.ImageBase);
	DWORD e8Add = pMsgBox - e8Next;
	memcpy((byte*)beginCode + 9, &e8Add, sizeof(e8Add));
	//修正E9
	DWORD e9Next = (((byte*)beginCode + 18 - pNewImage) + pNtHead->OptionalHeader.ImageBase);
	DWORD e9Add = (pNtHead->OptionalHeader.AddressOfEntryPoint + pNtHead->OptionalHeader.ImageBase) - e9Next;
	memcpy((byte*)beginCode + 14, &e9Add, sizeof(e9Add));
	//修改OEP
	pNtHead->OptionalHeader.AddressOfEntryPoint = (DWORD)((byte*)beginCode - pNewImage);

	int nSize = ImageBufToFileBuf(pNewImage, &pFileBuf);
	char szNewPath[MAX_PATH] = { 0 };
	memcpy(szNewPath, m_szPath, MAX_PATH);
	strcat_s(szNewPath, "_newSec.exe");
	SaveFile(szNewPath, (char*)pFileBuf, nSize);
	free(pFileBuf);
	free(pNewImage);
}

DWORD CPE::SaveFile(char* szPath,char *szBuf,int nFileSize)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, szPath, "wb");
	if (pFile == NULL)
	{
		return 0;
	}
	int nRet = fwrite(szBuf, nFileSize, 1, pFile);
	fclose(pFile);
	return nRet;
}

DWORD CPE::FileBufToImageBuf(void **pImageBuf)
{
	IMAGE_DOS_HEADER *pDos = NULL;
	IMAGE_NT_HEADERS *pNtHead = NULL;
	IMAGE_SECTION_HEADER *pSectionHead = NULL;

	if (*(PWORD)m_pFileMem != IMAGE_DOS_SIGNATURE)
	{
		MessageBox(NULL, L"找不到有效的DOS头", L"错误", MB_OK);

		return 0;
	}
	pDos = (IMAGE_DOS_HEADER*)m_pFileMem;
	if (*(PDWORD)((byte*)m_pFileMem + (pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		MessageBox(NULL, L"找不到有效的PE头", L"错误", MB_OK);
		return 0;
	}
	pNtHead = (IMAGE_NT_HEADERS*)((byte*)m_pFileMem + (pDos->e_lfanew));
	pSectionHead = (IMAGE_SECTION_HEADER*)((byte*)&pNtHead->OptionalHeader + pNtHead->FileHeader.SizeOfOptionalHeader);

	void *pTmp = NULL;
	pTmp = malloc(pNtHead->OptionalHeader.SizeOfImage);
	if (pTmp == NULL)
	{
		return 0;
	}
	memset(pTmp, 0, pNtHead->OptionalHeader.SizeOfImage);
	memcpy(pTmp, m_pFileMem, pNtHead->OptionalHeader.SizeOfHeaders);
	for (int i = 0; i < pNtHead->FileHeader.NumberOfSections; i++)
	{
		memcpy((byte*)pTmp + pSectionHead[i].VirtualAddress, (byte*)m_pFileMem + pSectionHead[i].PointerToRawData, pSectionHead[i].SizeOfRawData);
	}
	*pImageBuf = pTmp;
	pTmp = NULL;
	return pNtHead->OptionalHeader.SizeOfImage;
}

DWORD CPE::ImageBufToFileBuf(void *pImageBuf,void **pFileBuf)
{
	IMAGE_DOS_HEADER *pDos = NULL;
	IMAGE_NT_HEADERS *pNtHead = NULL;
	IMAGE_SECTION_HEADER *pSectionHead = NULL;

	if (*(PWORD)pImageBuf != IMAGE_DOS_SIGNATURE)
	{
		return 0;
	}
	pDos = (IMAGE_DOS_HEADER*)pImageBuf;
	if (*(PDWORD)((byte*)pImageBuf + (pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		return 0;
	}
	pNtHead = (IMAGE_NT_HEADERS*)((byte*)pImageBuf + (pDos->e_lfanew));
	pSectionHead = (IMAGE_SECTION_HEADER*)((byte*)&pNtHead->OptionalHeader + pNtHead->FileHeader.SizeOfOptionalHeader);
	int nSize = pNtHead->OptionalHeader.SizeOfHeaders;
	for (int i = 0; i < pNtHead->FileHeader.NumberOfSections; i++)
	{
		nSize += pSectionHead[i].SizeOfRawData;
	}
	void *pTmp = NULL;
	pTmp = malloc(nSize);
	if (pTmp == NULL)
	{
		return 0;
	}
	memset(pTmp, 0, nSize);
	memcpy(pTmp, pImageBuf, pNtHead->OptionalHeader.SizeOfHeaders);
	for (int i = 0; i < pNtHead->FileHeader.NumberOfSections; i++)
	{
		memcpy((byte*)pTmp + pSectionHead[i].PointerToRawData, (byte*)pImageBuf + pSectionHead[i].VirtualAddress, pSectionHead[i].SizeOfRawData);
	}

	*pFileBuf = pTmp;
	pTmp = NULL;
	return nSize;
}