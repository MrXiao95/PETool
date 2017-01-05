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
		MessageBox(NULL, L"文件打开失败", L"错误", MB_OK);
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

DWORD CPE::RvaToRaw(DWORD dwRva)
{
	DWORD dwRaw = 0;
	if (m_pOptionalHeader32)
	{
		dwRaw = dwRva - m_pOptionalHeader32->BaseOfCode;
	}
	else
	{
		dwRaw = dwRva - m_pOptionalHeader64->BaseOfCode;
	}
	for (int i = 0; i < m_nSection; i++)
	{
		if (dwRaw >= m_pSectionHead[i].VirtualAddress && dwRaw <= m_pSectionHead[i].VirtualAddress + m_pSectionHead[i].SizeOfRawData)
		{
			dwRaw += m_pSectionHead[i].PointerToRawData;
			break;
		}
	}
	return dwRaw;
}

DWORD CPE::RawToRva(DWORD dwRaw)
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
		if (dwRaw>=m_pSectionHead[i].PointerToRawData && dwRaw<=m_pSectionHead[i].PointerToRawData + m_pSectionHead[i].SizeOfRawData)
		{
			dwRva = dwRaw - m_pSectionHead[i].PointerToRawData + dwImageBase;
			break;
		}
	}
	return dwRva;
}