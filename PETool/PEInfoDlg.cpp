// PEFileInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "PEInfoDlg.h"
#include "afxdialogex.h"


// CPEFileInfo �Ի���

IMPLEMENT_DYNAMIC(CPEInfoDlg, CDialogEx)

CPEInfoDlg::CPEInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_PEINFO, pParent)
	, m_strPeStruct(_T(""))
{

}

CPEInfoDlg::~CPEInfoDlg()
{
}

void CPEInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITPE, m_strPeStruct);
	DDX_Control(pDX, IDC_EDITPE, m_editPE);
}


BEGIN_MESSAGE_MAP(CPEInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPEInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPEInfoDlg::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPEFileInfo ��Ϣ�������


void CPEInfoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CPEInfoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}


void CPEInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_editPE.m_hWnd)
	{
		CRect rt;
		GetClientRect(rt);

		m_editPE.MoveWindow(rt);
	}
}

void CPEInfoDlg::SetPeStruct(CPE *pe)
{
	byte *pBaseAdd = (byte*)(pe->m_pDosHead);
	m_strPeStruct = L"================================================================================================\r\n";

	ShowDosHead(pe, pBaseAdd);
	ShowNtHead(pe, pBaseAdd);
	ShowSectionHead(pe,pBaseAdd);
	
	m_strPeStruct += L"================================================================================================\r\n";
	UpdateData(FALSE);
}

void CPEInfoDlg::ShowNtHead(const CPE * pe, const byte * pBaseAdd)
{
	//NTͷ
	CString strTmp;
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	CString strOptHeader;
	if (pe->m_pOptionalHeader32)
	{
		m_strPeStruct += L"IMAGE_NT_HEADERS32 (PE�ļ�ͷ)�ṹ˵����\r\n";
		strOptHeader.Format(L"OptionalHeader�� [��ַ(RAW)��Χ:0x%08X - 0x%08X] [����:%xh] [IMAGE_OPTIONAL_HEADER32�ṹ, Ĭ�ϳ���Ϊ\"e0h\"(224).]\r\n"
			, (byte*)pe->m_pOptionalHeader32 - pBaseAdd
			, (byte*)pe->m_pSectionHead - 1 - pBaseAdd
			, ((byte*)pe->m_pSectionHead) - pBaseAdd);

	}
	else
	{
		m_strPeStruct += L"IMAGE_NT_HEADERS64 (PE�ļ�ͷ)�ṹ˵����\r\n";
		strOptHeader.Format(L"OptionalHeader�� [��ַ(RAW)��Χ:0x%08X - 0x%08X][����:%xh] [IMAGE_OPTIONAL_HEADER64�ṹ, Ĭ�ϳ���Ϊ\"f0h\"(240).]\r\n"
			, (byte*)pe->m_pOptionalHeader64 - pBaseAdd
			, (byte*)pe->m_pSectionHead - 1 - pBaseAdd
			, ((byte*)pe->m_pSectionHead) - pBaseAdd);
	}
	strTmp.Format(L"Signature��      [��ַ(RAW)��Χ:0x%08X - 0x%08X] [����:04h] [PE�ļ���־(\"PE\", 0, 0), ����Ϊ\"4\".]\r\n"
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead - 4
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead - 1);
	m_strPeStruct += strTmp;
	strTmp.Format(L"FileHeader��     [��ַ(RAW)��Χ:0x%08X - 0x%08X] [����:14h] [IMAGE_FILE_HEADER�ṹ, ����Ϊ\"20\".]\r\n"
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead + sizeof(IMAGE_FILE_HEADER) - 1);
	m_strPeStruct += strTmp;
	m_strPeStruct += strOptHeader;

	m_strPeStruct += L"\r\n\r\n";

	m_strPeStruct += L"IMAGE_FILE_HEADER(ӳ���ļ�ͷ)�ṹ���£�\r\n";
	strTmp.Format(L"Machine��              [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x04] [����:0x%04X]     [����ƽ̨(��ִ���ļ���CPU����).]\r\n"
		, (byte*)pe->m_pFileHead - pBaseAdd, pe->m_pFileHead->Machine);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfSections��     [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x06] [����:0x%04X]     [���� / �� / ��(Section)����Ŀ.]\r\n"
		, (byte*)&pe->m_pFileHead->NumberOfSections - pBaseAdd
		, pe->m_pFileHead->NumberOfSections);
	m_strPeStruct += strTmp;
	strTmp.Format(L"TimeDateStamp��        [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x08] [����:0x48025287] [�ļ�����ʱ��ʱ���.]\r\n"
		, (byte*)&pe->m_pFileHead->TimeDateStamp - pBaseAdd
		, pe->m_pFileHead->TimeDateStamp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"PointerOfSymbolTable�� [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x0C] [����:0x%08X] [COFF����ָ��, ָ����ű�(���ڵ���).]\r\n"
		, (byte*)&pe->m_pFileHead->PointerToSymbolTable - pBaseAdd
		, pe->m_pFileHead->PointerToSymbolTable);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfSymbols��      [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x10] [����:0x%08X] [���ű�(����һ�ֶ�)�еķ��Ÿ���(���ڵ���).]\r\n"
		, (byte*)&pe->m_pFileHead->NumberOfSymbols - pBaseAdd
		, pe->m_pFileHead->NumberOfSymbols);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfOptionalHeader�� [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x14] [����:0x%04X] \
		    [��ѡ�ײ�����(��ѡͷ��С).��OBJ��, ���ֶ�Ϊ0; �ڿ�ִ���ļ���, ��ָIMAGE_OPTIONAL_HEADER�ṹ�ĳ���.]\r\n"
		, (byte*)&pe->m_pFileHead->SizeOfOptionalHeader - pBaseAdd
		, pe->m_pFileHead->SizeOfOptionalHeader);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Characteristics��      [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x16] [����:0x%04X]     [�ļ����� / ����(�ļ���Ϣ��־).]\r\n\r\n"
		, (byte*)&pe->m_pFileHead->Characteristics - pBaseAdd
		, pe->m_pFileHead->Characteristics);
	m_strPeStruct += strTmp;
	m_strPeStruct += L"�ļ����� ����ֵ���ձ�\r\n";

	m_strPeStruct += L"[ֵ:0001h][IMAGE_FILE_RELOCS_STRIPPED          // Relocation info stripped from file.(�ض�λ��Ϣ����ȥ)]\r\n";
	m_strPeStruct += L"[ֵ:0002h][IMAGE_FILE_EXECUTABLE_IMAGE         // File is executable (i.e. no unresolved externel references).(�ļ���ִ��)]\r\n";
	m_strPeStruct += L"[ֵ:0004h][IMAGE_FILE_LINE_NUMS_STRIPPED       // Line nunbers stripped from file.(�кű���ȥ)]\r\n";
	m_strPeStruct += L"[ֵ:0008h][IMAGE_FILE_LOCAL_SYMS_STRIPPED      // Local symbols stripped from file.(���ű���ȥ)]\r\n";
	m_strPeStruct += L"[ֵ:0010h][IMAGE_FILE_AGGRESIVE_WS_TRIM        // Agressively trim working set.(��������������)]\r\n";
	m_strPeStruct += L"[ֵ:0020h][IMAGE_FILE_LARGE_ADDRESS_AWARE      // App can handle >2gb addresses.(�ߵ�ַ����)]\r\n";
	m_strPeStruct += L"[ֵ:0080h][IMAGE_FILE_BYTES_REVERSED_LO        // Bytes of machine word are reversed.(������ĵ�λ�ֽ����෴��)]\r\n";
	m_strPeStruct += L"[ֵ:0100h][IMAGE_FILE_32BIT_MACHINE            // 32 bit word machine. (32λ����)]\r\n";
	m_strPeStruct += L"[ֵ:0200h][IMAGE_FILE_DEBUG_STRIPPED           // Debugging info stripped from file in .DBG file.(.DBG�ļ��ĵ�����Ϣ����ȥ)]\r\n";
	m_strPeStruct += L"[ֵ:0400h][IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP  // If Image is on removable media, copy and run from the swap file.(���ӳ���ļ����ڿ��ƶ�ý����,���ȸ��Ƶ������ļ���������)]\r\n";
	m_strPeStruct += L"[ֵ:0800h][IMAGE_FILE_NET_RUN_FROM_SWAP        // If Image is on Net, copy and run from the swap file.(���ӳ���ļ�����������,���Ƶ������ļ��������)]\r\n";
	m_strPeStruct += L"[ֵ:1000h][IMAGE_FILE_SYSTEM                   // System File.(ϵͳ�ļ�)]\r\n";
	m_strPeStruct += L"[ֵ:2000h][IMAGE_FILE_DLL                      // File is a DLL.(�ļ���DLL�ļ�)]\r\n";
	m_strPeStruct += L"[ֵ:4000h][IMAGE_FILE_UP_SYSTEM_ONLY           // File should only be run on a UP machine.(�ļ�ֻ�������ڵ���������)]\r\n";
	m_strPeStruct += L"[ֵ:8000h][IMAGE_FILE_BYTES_REVERSED_HI        // Bytes of machine word are reversed.(������ĸ�λ�ֽ����෴��)]\r\n\r\n";

	ShowOptionalHeader(pe, pBaseAdd);

}

void CPEInfoDlg::ShowOptionalHeader(const CPE * pe, const byte * pBaseAdd)
{
	if (pe->m_pOptionalHeader32)
	{
		ShowOptionalHeader32(pe, pBaseAdd);
	}
	else
	{
		ShowOptionalHeader64(pe, pBaseAdd);
	}
}

void CPEInfoDlg::ShowOptionalHeader64(const CPE * pe, const byte * pBaseAdd)
{
	CString strTmp;
	m_strPeStruct += L"IMAGE_OPTIONAL_HEADER64(��ѡӳ��ͷ)�ṹ���£�\r\n";

	strTmp.Format(L"Magic��                      [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x18] [����:0x%04X]     [��־��(����), ��ֵΪ\"010Bh\".����˵���ļ���ROMӳ��, ������ͨ��ִ�е�ӳ��.]\r\n"
		, (byte*)pe->m_pOptionalHeader64 - pBaseAdd, pe->m_pOptionalHeader64->Magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorLinkerVersion��         [��ַ(RAW):0x%08X] [����:01h] [ƫ����:e_lfanew + 0x1A] [����:0x%02X]       [��������(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorLinkerVersion��         [��ַ(RAW):0x%08X] [����:01h] [ƫ����:e_lfanew + 0x1B] [����:0x%02X]       [��������(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfCode��                 [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x1C] [����:0x%08X] [�����(��)��С, ����Code Section�ܹ��Ĵ�С(ֻ�벻��), ���ֵ�����϶���ĳһ��ֵ��������.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfCode - pBaseAdd, pe->m_pOptionalHeader64->SizeOfCode);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfInitializedData��      [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x20] [����:0x%08X] [�ѳ�ʼ�����ݿ��С.���ڱ���ʱ�����ɵĿ�Ĵ�С(�����������), ��������ݲ���̫׼ȷ.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfInitializedData - pBaseAdd, pe->m_pOptionalHeader64->SizeOfInitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfUninitializedData��    [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x24] [����:0x%08X] [δ��ʼ�����ݿ��С.װ�س���Ҫ�������ַ�ռ���Ϊ��Щ����Լ���ռ�.δ��ʼ������ͨ����.bbs����.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfUninitializedData - pBaseAdd, pe->m_pOptionalHeader64->SizeOfUninitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"AddressOfEntryPoint(RVA)��   [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x28] [����:0x%08X] [����ʼִ�е���ڵ�ַ / ��ڵ�EP(RVA).����һ��\"��������ַ\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->AddressOfEntryPoint - pBaseAdd, pe->m_pOptionalHeader64->AddressOfEntryPoint);
	m_strPeStruct += strTmp;
	strTmp.Format(L"BaseOfCode��                 [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x2C] [����:0x%08X] [�����(��)��ʼ��ַ.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->BaseOfCode - pBaseAdd, pe->m_pOptionalHeader64->BaseOfCode);
	m_strPeStruct += strTmp;
	// 		strTmp.Format(L"BaseOfData��                 [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x30] [����:0x%08X] [���ݶ�(��)��ʼ��ַ.]\r\n"
	// 			, (byte*)pe->m_pOptionalHeader64->BaseOfData - pBaseAdd, pe->m_pOptionalHeader64->BaseOfData);
	// 		m_strPeStruct += strTmp;
	strTmp.Format(L"ImageBase��                  [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x34] [����:0x%08X] [��ַ, ����Ĭ��װ��Ļ���ַ.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->ImageBase - pBaseAdd, pe->m_pOptionalHeader64->ImageBase);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SectionAlignment��           [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x38] [����:0x%08X] [�ڴ��еĽ�(��\"Section\")�Ķ���ֵ, ��Ϊ:0x1000��0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SectionAlignment - pBaseAdd, pe->m_pOptionalHeader64->SectionAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"FileAlignment��              [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x3C] [����:0x%08X] [�ļ��еĽ�(��\"Section\")�Ķ���ֵ, ��Ϊ:0x1000��0x200��0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->FileAlignment - pBaseAdd, pe->m_pOptionalHeader64->FileAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorOperatingSystemVersion��[��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x40] [����:0x%04X]     [����ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorOperatingSystemVersion��[��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x42] [����:0x%04X]     [����ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorImageVersion��          [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x44] [����:0x%04X]     [�ÿ�ִ���ļ�����(��)�汾��, �ɳ���Ա�Զ���.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorImageVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorImageVersion��          [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x46] [����:0x%04X]     [�ÿ�ִ���ļ��Ĵ�(��)�汾��, �ɳ���Ա�Զ���.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorImageVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorSubsystemVersion��      [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x48] [����:0x%04X]     [������ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorSubsystemVersion��      [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x4A] [����:0x%04X]     [������ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Win32VersionValue��          [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x4C] [����:0x%08X] [����.����\"00000000\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->Win32VersionValue - pBaseAdd, pe->m_pOptionalHeader64->Win32VersionValue);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfImage��                [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x50] [����:0x%08X] [ӳ���С(ӳ��װ���ڴ����ܳߴ� / �ڴ�������PEӳ��ĳߴ�).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfImage - pBaseAdd, pe->m_pOptionalHeader64->SizeOfImage);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeaders��		     [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x54] [����:0x%08X] [�ײ������(�ײ� + ���)�Ĵ�С.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfHeaders - pBaseAdd, pe->m_pOptionalHeader64->SizeOfHeaders);
	m_strPeStruct += strTmp;
	strTmp.Format(L"CheckSum��                   [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x58] [����:0x%08X] [CRCУ���.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->CheckSum - pBaseAdd, pe->m_pOptionalHeader64->CheckSum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Subsystem��                  [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x5C] [����:0x%04X]     [��ϵͳ:Windows ͼ���û����� / ͼ�νӿ���ϵͳ(Image runs in the Windows GUI subsystem.).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->Subsystem - pBaseAdd, pe->m_pOptionalHeader64->Subsystem);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DllCharacteristics��         [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x5E] [����:0x%04X]     [DLLMain()������ʱ������.���ļ�ΪDLL����ʱʹ��, Ĭ��ֵΪ\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->DllCharacteristics - pBaseAdd, pe->m_pOptionalHeader64->DllCharacteristics);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackReserve��         [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x60] [����:0x%08X] [��ʼ��ʱΪ�̱߳�����ջ��С.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfStackReserve - pBaseAdd, pe->m_pOptionalHeader64->SizeOfStackReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackCommit��          [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x64] [����:0x%08X] [��ʼ��ʱ�߳�ʵ��ʹ�õ�ջ��С.���ֵ�ܱ�\"SizeOfStackReserve\"ҪСһЩ.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfStackCommit - pBaseAdd, pe->m_pOptionalHeader64->SizeOfStackCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapReserve��          [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x68] [����:0x%08X] [��ʼ��ʱΪ���̱����ĶѴ�С.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfHeapReserve - pBaseAdd, pe->m_pOptionalHeader64->SizeOfHeapReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapCommit��           [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x6C] [����:0x%08X] [��ʼ��ʱ����ʵ��ʹ�õĶѴ�С.���ֵ�ܱ�\"SizeOfHeapReserve\"ҪСһЩ.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfHeapCommit - pBaseAdd, pe->m_pOptionalHeader64->SizeOfHeapCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"LoaderFlags��                [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x70] [����:0x%08X] [�����Զ����öϵ�������.������й�, Ĭ��ֵΪ\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->LoaderFlags - pBaseAdd, pe->m_pOptionalHeader64->LoaderFlags);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfRvaAndSizes��        [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x74] [����:0x%08X] [����Ŀ¼�ṹ������(����).ֵ��Ϊ\"00000010h\"(16��).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->NumberOfRvaAndSizes - pBaseAdd, pe->m_pOptionalHeader64->NumberOfRvaAndSizes);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DataDirectory��              [��ַ(RAW)��Χ:0x%08X - 0x%08X] [����:80h] [����Ŀ¼��(16��, ÿ����Առ8�ֽ�).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader64->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";

	ShowDataDirectory64(pe, pBaseAdd);


	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}

void CPEInfoDlg::ShowDataDirectory64(const CPE * pe, const byte * pBaseAdd)
{
	CString strTmp;
	//����Ŀ¼��
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DATA_DIRECTORY(����Ŀ¼��)�ṹ���£�\r\n";

	strTmp.Format(L"[��ַ(RAW)��Χ:0x%08X - 0x%08X] [����:0x%02Xh] [����Ŀ¼��(16��, ÿ����Առ8�ֽ�).]\r\n\r\n"
		, (byte*)pe->m_pOptionalHeader64->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader64->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1
		, ((byte*)&pe->m_pOptionalHeader64->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd) - ((byte*)pe->m_pOptionalHeader64->DataDirectory - pBaseAdd));
	m_strPeStruct += strTmp;
	m_strPeStruct += L"    [��Ա]                  [��ַ(RAW)]     [ƫ����]           [����:RVA]         [��С]   [˵��]               [�ṹ]\r\n";
	strTmp.Format(L"Export Table��              0x%08X  [e_lfanew + 0x078]     0x%08X     0x%08X  [������]   [IMAGE_DIRECTORY_ENTRY_EXPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[0]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[0].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[0].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Table��              0x%08X  [e_lfanew + 0x080]     0x%08X     0x%08X  [�����]   [IMAGE_DIRECTORY_ENTRY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[1]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[1].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[1].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Resources Table��           0x%08X  [e_lfanew + 0x088]     0x%08X     0x%08X  [��Դ]     [IMAGE_DIRECTORY_ENTRY_RESOURCE]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[2]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[2].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[2].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Exception Table��           0x%08X  [e_lfanew + 0x090]     0x%08X     0x%08X  [�쳣]     [IMAGE_DIRECTORY_ENTRY_EXCEPTION]\r\n"
		, (byte*) &(pe->m_pOptionalHeader64->DataDirectory[3]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[3].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[3].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Security Table��            0x%08X  [e_lfanew + 0x098]     0x%08X     0x%08X  [��ȫ֤��] [IMAGE_DIRECTORY_ENTRY_SECURITY]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[4]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[4].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[4].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Base relocation Table��     0x%08X  [e_lfanew + 0x0A0]     0x%08X     0x%08X  [�ض�λ��] [IMAGE_DIRECTORY_ENTRY_BASERELOC]\r\n"
		, (byte*) &(pe->m_pOptionalHeader64->DataDirectory[5]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[5].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[5].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Debug��                     0x%08X  [e_lfanew + 0x0A8]     0x%08X     0x%08X  [������Ϣ] [IMAGE_DIRECTORY_ENTRY_DEBUG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[6]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[6].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[6].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Architecture(Copyrught)��   0x%08X  [e_lfanew + 0x0B0]     0x%08X     0x%08X  [��Ȩ����] [IMAGE_DIRECTORY_ENTRY_ARCHITECTURE(IMAGE_DIRECTORY_ENTRY_COPYRIGHT)]\r\n"
		, (byte*) &(pe->m_pOptionalHeader64->DataDirectory[7]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[7].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[7].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Global Ptr��                0x%08X  [e_lfanew + 0x0B8]     0x%08X     0x%08X  [ȫ��ָ��] [IMAGE_DIRECTORY_ENTRY_GLOBALPTR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[8]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[8].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[8].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Tread local storage(TLS)��  0x%08X  [e_lfanew + 0x0C0]     0x%08X     0x%08X  [TLS ��]   [IMAGE_DIRECTORY_ENTRY_TLS]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[9]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[9].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[9].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Load configuration��        0x%08X  [e_lfanew + 0x0C8]     0x%08X     0x%08X  [��������] [IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[10]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[10].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[10].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Bound Import��              0x%08X  [e_lfanew + 0x0D0]     0x%08X     0x%08X  [�󶨵���] [IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[11]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[11].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[11].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Address Table(IAT)�� 0x%08X  [e_lfanew + 0x0D8]     0x%08X     0x%08X  [IAT ��]   [IMAGE_DIRECTORY_ENTRY_IAT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[12]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[12].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[12].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Delay Import��              0x%08X  [e_lfanew + 0x0E0]     0x%08X     0x%08X  [�ӳٵ���] [IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[13]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[13].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[13].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"COM descriptor��            0x%08X  [e_lfanew + 0x0E8]     0x%08X     0x%08X  [COM]      [IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[14]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[14].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[14].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"������                      0x%08X  [e_lfanew + 0x0F0]     0x%08X     0x%08X  [����]     [NULL]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[15]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[15].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[15].Size);
	m_strPeStruct += strTmp;
}

void CPEInfoDlg::ShowOptionalHeader32(const CPE * pe, const byte * pBaseAdd)
{
	CString strTmp;
	m_strPeStruct += L"IMAGE_OPTIONAL_HEADER32(��ѡӳ��ͷ)�ṹ���£�\r\n";

	strTmp.Format(L"Magic��                      [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x18] [����:0x%04X]     [��־��(����), ��ֵΪ\"010Bh\".����˵���ļ���ROMӳ��, ������ͨ��ִ�е�ӳ��.]\r\n"
		, (byte*)pe->m_pOptionalHeader32 - pBaseAdd, pe->m_pOptionalHeader32->Magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorLinkerVersion��         [��ַ(RAW):0x%08X] [����:01h] [ƫ����:e_lfanew + 0x1A] [����:0x%02X]       [��������(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorLinkerVersion��         [��ַ(RAW):0x%08X] [����:01h] [ƫ����:e_lfanew + 0x1B] [����:0x%02X]       [��������(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfCode��                 [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x1C] [����:0x%08X] [�����(��)��С, ����Code Section�ܹ��Ĵ�С(ֻ�벻��), ���ֵ�����϶���ĳһ��ֵ��������.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfCode - pBaseAdd, pe->m_pOptionalHeader32->SizeOfCode);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfInitializedData��      [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x20] [����:0x%08X] [�ѳ�ʼ�����ݿ��С.���ڱ���ʱ�����ɵĿ�Ĵ�С(�����������), ��������ݲ���̫׼ȷ.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfInitializedData - pBaseAdd, pe->m_pOptionalHeader32->SizeOfInitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfUninitializedData��    [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x24] [����:0x%08X] [δ��ʼ�����ݿ��С.װ�س���Ҫ�������ַ�ռ���Ϊ��Щ����Լ���ռ�.δ��ʼ������ͨ����.bbs����.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfUninitializedData - pBaseAdd, pe->m_pOptionalHeader32->SizeOfUninitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"AddressOfEntryPoint(RVA)��   [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x28] [����:0x%08X] [����ʼִ�е���ڵ�ַ / ��ڵ�EP(RVA).����һ��\"��������ַ\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->AddressOfEntryPoint - pBaseAdd, pe->m_pOptionalHeader32->AddressOfEntryPoint);
	m_strPeStruct += strTmp;
	strTmp.Format(L"BaseOfCode��                 [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x2C] [����:0x%08X] [�����(��)��ʼ��ַ.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->BaseOfCode - pBaseAdd, pe->m_pOptionalHeader32->BaseOfCode);
	m_strPeStruct += strTmp;
	strTmp.Format(L"BaseOfData��                 [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x30] [����:0x%08X] [���ݶ�(��)��ʼ��ַ.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->BaseOfData - pBaseAdd, pe->m_pOptionalHeader32->BaseOfData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"ImageBase��                  [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x34] [����:0x%08X] [��ַ, ����Ĭ��װ��Ļ���ַ.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->ImageBase - pBaseAdd, pe->m_pOptionalHeader32->ImageBase);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SectionAlignment��           [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x38] [����:0x%08X] [�ڴ��еĽ�(��\"Section\")�Ķ���ֵ, ��Ϊ:0x1000��0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SectionAlignment - pBaseAdd, pe->m_pOptionalHeader32->SectionAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"FileAlignment��              [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x3C] [����:0x%08X] [�ļ��еĽ�(��\"Section\")�Ķ���ֵ, ��Ϊ:0x1000��0x200��0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->FileAlignment - pBaseAdd, pe->m_pOptionalHeader32->FileAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorOperatingSystemVersion��[��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x40] [����:0x%04X]     [����ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorOperatingSystemVersion��[��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x42] [����:0x%04X]     [����ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorImageVersion��          [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x44] [����:0x%04X]     [�ÿ�ִ���ļ�����(��)�汾��, �ɳ���Ա�Զ���.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorImageVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorImageVersion��          [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x46] [����:0x%04X]     [�ÿ�ִ���ļ��Ĵ�(��)�汾��, �ɳ���Ա�Զ���.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorImageVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorSubsystemVersion��      [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x48] [����:0x%04X]     [������ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorSubsystemVersion��      [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x4A] [����:0x%04X]     [������ϵͳ��(��)�汾��.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Win32VersionValue��          [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x4C] [����:0x%08X] [����.����\"00000000\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->Win32VersionValue - pBaseAdd, pe->m_pOptionalHeader32->Win32VersionValue);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfImage��                [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x50] [����:0x%08X] [ӳ���С(ӳ��װ���ڴ����ܳߴ� / �ڴ�������PEӳ��ĳߴ�).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfImage - pBaseAdd, pe->m_pOptionalHeader32->SizeOfImage);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeaders��		     [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x54] [����:0x%08X] [�ײ������(�ײ� + ���)�Ĵ�С.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfHeaders - pBaseAdd, pe->m_pOptionalHeader32->SizeOfHeaders);
	m_strPeStruct += strTmp;
	strTmp.Format(L"CheckSum��                   [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x58] [����:0x%08X] [CRCУ���.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->CheckSum - pBaseAdd, pe->m_pOptionalHeader32->CheckSum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Subsystem��                  [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x5C] [����:0x%04X]     [��ϵͳ:Windows ͼ���û����� / ͼ�νӿ���ϵͳ(Image runs in the Windows GUI subsystem.).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->Subsystem - pBaseAdd, pe->m_pOptionalHeader32->Subsystem);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DllCharacteristics��         [��ַ(RAW):0x%08X] [����:02h] [ƫ����:e_lfanew + 0x5E] [����:0x%04X]     [DLLMain()������ʱ������.���ļ�ΪDLL����ʱʹ��, Ĭ��ֵΪ\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->DllCharacteristics - pBaseAdd, pe->m_pOptionalHeader32->DllCharacteristics);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackReserve��         [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x60] [����:0x%08X] [��ʼ��ʱΪ�̱߳�����ջ��С.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfStackReserve - pBaseAdd, pe->m_pOptionalHeader32->SizeOfStackReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackCommit��          [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x64] [����:0x%08X] [��ʼ��ʱ�߳�ʵ��ʹ�õ�ջ��С.���ֵ�ܱ�\"SizeOfStackReserve\"ҪСһЩ.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfStackCommit - pBaseAdd, pe->m_pOptionalHeader32->SizeOfStackCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapReserve��          [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x68] [����:0x%08X] [��ʼ��ʱΪ���̱����ĶѴ�С.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfHeapReserve - pBaseAdd, pe->m_pOptionalHeader32->SizeOfHeapReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapCommit��           [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x6C] [����:0x%08X] [��ʼ��ʱ����ʵ��ʹ�õĶѴ�С.���ֵ�ܱ�\"SizeOfHeapReserve\"ҪСһЩ.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfHeapCommit - pBaseAdd, pe->m_pOptionalHeader32->SizeOfHeapCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"LoaderFlags��                [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x70] [����:0x%08X] [�����Զ����öϵ�������.������й�, Ĭ��ֵΪ\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->LoaderFlags - pBaseAdd, pe->m_pOptionalHeader32->LoaderFlags);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfRvaAndSizes��        [��ַ(RAW):0x%08X] [����:04h] [ƫ����:e_lfanew + 0x74] [����:0x%08X] [����Ŀ¼�ṹ������(����).ֵ��Ϊ\"00000010h\"(16��).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->NumberOfRvaAndSizes - pBaseAdd, pe->m_pOptionalHeader32->NumberOfRvaAndSizes);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DataDirectory��              [��ַ(RAW)��Χ:0x%08X - 0x%08X] [����:80h] [����Ŀ¼��(16��, ÿ����Առ8�ֽ�).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader32->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";

	ShowDataDirectory32(pe, pBaseAdd);

}

void CPEInfoDlg::ShowDataDirectory32(const CPE * pe, const byte * pBaseAdd)
{
	CString strTmp;
	//����Ŀ¼��
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DATA_DIRECTORY(����Ŀ¼��)�ṹ���£�\r\n";

	strTmp.Format(L"[��ַ(RAW)��Χ:0x%08X - 0x%08X] [����:0x%02Xh] [����Ŀ¼��(16��, ÿ����Առ8�ֽ�).]\r\n\r\n"
		, (byte*)pe->m_pOptionalHeader32->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader32->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1
		, ((byte*)&pe->m_pOptionalHeader32->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd) - ((byte*)pe->m_pOptionalHeader32->DataDirectory - pBaseAdd));
	m_strPeStruct += strTmp;
	m_strPeStruct += L"    [��Ա]                  [��ַ(RAW)]     [ƫ����]           [����:RVA]         [��С]   [˵��]               [�ṹ]\r\n";
	strTmp.Format(L"Export Table��              0x%08X  [e_lfanew + 0x078]     0x%08X     0x%08X  [������]   [IMAGE_DIRECTORY_ENTRY_EXPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[0]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[0].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[0].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Table��              0x%08X  [e_lfanew + 0x080]     0x%08X     0x%08X  [�����]   [IMAGE_DIRECTORY_ENTRY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[1]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[1].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[1].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Resources Table��           0x%08X  [e_lfanew + 0x088]     0x%08X     0x%08X  [��Դ]     [IMAGE_DIRECTORY_ENTRY_RESOURCE]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[2]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[2].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[2].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Exception Table��           0x%08X  [e_lfanew + 0x090]     0x%08X     0x%08X  [�쳣]     [IMAGE_DIRECTORY_ENTRY_EXCEPTION]\r\n"
		, (byte*) &(pe->m_pOptionalHeader32->DataDirectory[3]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[3].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[3].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Security Table��            0x%08X  [e_lfanew + 0x098]     0x%08X     0x%08X  [��ȫ֤��] [IMAGE_DIRECTORY_ENTRY_SECURITY]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[4]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[4].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[4].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Base relocation Table��     0x%08X  [e_lfanew + 0x0A0]     0x%08X     0x%08X  [�ض�λ��] [IMAGE_DIRECTORY_ENTRY_BASERELOC]\r\n"
		, (byte*) &(pe->m_pOptionalHeader32->DataDirectory[5]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[5].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[5].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Debug��                     0x%08X  [e_lfanew + 0x0A8]     0x%08X     0x%08X  [������Ϣ] [IMAGE_DIRECTORY_ENTRY_DEBUG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[6]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[6].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[6].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Architecture(Copyrught)��   0x%08X  [e_lfanew + 0x0B0]     0x%08X     0x%08X  [��Ȩ����] [IMAGE_DIRECTORY_ENTRY_ARCHITECTURE(IMAGE_DIRECTORY_ENTRY_COPYRIGHT)]\r\n"
		, (byte*) &(pe->m_pOptionalHeader32->DataDirectory[7]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[7].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[7].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Global Ptr��                0x%08X  [e_lfanew + 0x0B8]     0x%08X     0x%08X  [ȫ��ָ��] [IMAGE_DIRECTORY_ENTRY_GLOBALPTR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[8]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[8].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[8].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Tread local storage(TLS)��  0x%08X  [e_lfanew + 0x0C0]     0x%08X     0x%08X  [TLS ��]   [IMAGE_DIRECTORY_ENTRY_TLS]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[9]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[9].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[9].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Load configuration��        0x%08X  [e_lfanew + 0x0C8]     0x%08X     0x%08X  [��������] [IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[10]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[10].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[10].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Bound Import��              0x%08X  [e_lfanew + 0x0D0]     0x%08X     0x%08X  [�󶨵���] [IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[11]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[11].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[11].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Address Table(IAT)�� 0x%08X  [e_lfanew + 0x0D8]     0x%08X     0x%08X  [IAT ��]   [IMAGE_DIRECTORY_ENTRY_IAT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[12]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[12].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[12].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Delay Import��              0x%08X  [e_lfanew + 0x0E0]     0x%08X     0x%08X  [�ӳٵ���] [IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[13]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[13].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[13].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"COM descriptor��            0x%08X  [e_lfanew + 0x0E8]     0x%08X     0x%08X  [COM]      [IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[14]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[14].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[14].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"������                      0x%08X  [e_lfanew + 0x0F0]     0x%08X     0x%08X  [����]     [NULL]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[15]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[15].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[15].Size);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}

void CPEInfoDlg::ShowDosHead(const CPE * pe, const byte * pBaseAdd)
{
	m_strPeStruct += L"DOS�ײ� �ṹ˵����\r\n\r\n";
	CString strTmp;
	DWORD dosSub = (byte*)&(pe->m_pDosHead->e_lfanew) - pBaseAdd + sizeof(DWORD) - 1;
	strTmp.Format(L"MZ header��      [��ַ(RAW)��Χ:0x00000000 - 0x%08X] [����:0040h] [����:IMAGE_DOS_HEADER] [DOS�ļ�ͷ.]\r\n", dosSub);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DOS stub header��[��ַ(RAW)��Χ:0x%08X - 0x%08X][����:00a0h][����:DOS STUB][DOS����Ч��EXE�ļ���ʽ, ���(���Ȳ���).]\r\n", dosSub + 1, pe->m_pDosHead->e_lfanew - 1);
	m_strPeStruct += strTmp;
	//DOSͷ
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DOS_HEADER (DOS�ļ�ͷ)�ṹ���£�\r\n\r\n";
	strTmp.Format(L"e_magic��    [��ַ(RAW):0x00000000] [����:02h] [����:0x%X] [Magic number.][DOS��ִ���ļ����\"MZ\"ͷ,����Ϊ\"5A4Dh\",��ֵ.]\r\n", pe->m_pDosHead->e_magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cblp��     [��ַ(RAW):0x00000002] [����:02h] [����:0x%04X] [Bytes on last page of file.]\r\n", pe->m_pDosHead->e_cblp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cp��	     [��ַ(RAW):0x00000004] [����:02h] [����:0x%04X] [Pages in file.]\r\n", pe->m_pDosHead->e_cp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_crlc��     [��ַ(RAW):0x00000006] [����:02h] [����:0x%04X] [Relocations.]\r\n", pe->m_pDosHead->e_crlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cparhdr��  [��ַ(RAW):0x00000008] [����:02h] [����:0x%04X] [Size of header in paragraphs.]\r\n", pe->m_pDosHead->e_cparhdr);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_minalloc�� [��ַ(RAW):0x0000000a] [����:02h] [����:0x%04X] [Minimum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_minalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_maxalloc�� [��ַ(RAW):0x0000000c] [����:02h] [����:0x%04X] [Maximum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_maxalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ss��       [��ַ(RAW):0x0000000e] [����:02h] [����:0x%04X] [Initial(relative) SS value.]\r\n", pe->m_pDosHead->e_ss);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_sp��       [��ַ(RAW):0x00000010] [����:02h] [����:0x%04X] [Initial SP value.]\r\n", pe->m_pDosHead->e_sp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_csum��     [��ַ(RAW):0x00000012] [����:02h] [����:0x%04X] [Checksum.]\r\n", pe->m_pDosHead->e_csum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ip��       [��ַ(RAW):0x00000014] [����:02h] [����:0x%04X] [Initial IP value.] [DOS�������IP.]\r\n", pe->m_pDosHead->e_ip);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cs��       [��ַ(RAW):0x00000016] [����:02h] [����:0x%04X] [Initial(relative) CS value.] [DOS��������CS.]\r\n", pe->m_pDosHead->e_cs);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfarlc��   [��ַ(RAW):0x00000018] [����:02h] [����:0x%04X] [File address of relocation table.]\r\n", pe->m_pDosHead->e_lfarlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ovno��     [��ַ(RAW):0x0000001a] [����:02h] [����:0x%04X] [Overlay number.]\r\n", pe->m_pDosHead->e_ovno);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res[4]��   [��ַ(RAW):0x0000001c] [����:08h] [����:0x0000000000000000] [Reserved words.]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oemid��    [��ַ(RAW):0x00000024] [����:02h] [����:0x%04X] [OEM identifier(for e_oeminfo).]\r\n", pe->m_pDosHead->e_oemid);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oeminfo��  [��ַ(RAW):0x00000026] [����:02h] [����:0x%04X] [OEM information; e_oemid specific.]\r\n", pe->m_pDosHead->e_oeminfo);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res2[10]�� [��ַ(RAW):0x00000028] [����:14h] [����:0x0000000000000000000000000000000000000000] [Reserved words.] [����Ϊ\"20\".]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfanew��   [��ַ(RAW):0x0000003c] [����:04h] [����:0x%08X] [ƫ����:0x3C] [File address of new exe header.] [PE�ļ�ͷ��ַ.]\r\n", pe->m_pDosHead->e_lfanew);
	m_strPeStruct += strTmp;
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}

void CPEInfoDlg::ShowSectionHead(const CPE * pe, const byte * pBaseAdd)
{
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	CString strTmp;
	m_strPeStruct += L"IMAGE_SECTION_HEADER(��� | ���� | �ڱ�)�ṹ���£�\r\n";
	m_strPeStruct += L"------------------------------------------------------------\r\n";
	for (int i=0;i<pe->m_nSection;i++)
	{
		char szName[9] = {0};
		strcpy_s(szName, 8, (char*)pe->m_pSectionHead[i].Name);
		m_strPeStruct += L"[��Ա]                   [��ַ(RAW)]      [����:RVA]      [˵��]\r\n";
		strTmp.Format(L"Name��                   0x%08X        [%s]        [����, ����:8λ(16�ֽ�)��ASCII��.]\r\n"
			,(byte*)&pe->m_pSectionHead[i].Name - pBaseAdd,CString(szName));
		m_strPeStruct += strTmp;
		strTmp.Format(L"VirtualSize��            0x%08X        0x%08X     [V(VS), �ڴ��д�С(����ǰ�ĳ���).]\r\n"
			, (byte*)&pe->m_pSectionHead[i].Misc.VirtualSize - pBaseAdd, pe->m_pSectionHead[i].Misc.VirtualSize);
		m_strPeStruct += strTmp;
		strTmp.Format(L"VirtualAddress��         0x%08X        0x%08X     [V(VO), �ڴ���ƫ��(�ÿ��RVA).]\r\n"
			, (byte*)&pe->m_pSectionHead[i].VirtualAddress - pBaseAdd, pe->m_pSectionHead[i].VirtualAddress);
		m_strPeStruct += strTmp;
		strTmp.Format(L"SizeOfRawData��          0x%08X        0x%08X     [R(RS), �ļ��д�С(�����ĳ���).]\r\n"
			, (byte*)&pe->m_pSectionHead[i].SizeOfRawData - pBaseAdd, pe->m_pSectionHead[i].SizeOfRawData);
		m_strPeStruct += strTmp;
		strTmp.Format(L"PointerToRawData��       0x%08X        0x%08X	  [R(RO), �ļ���ƫ��.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].PointerToRawData - pBaseAdd, pe->m_pSectionHead[i].PointerToRawData);
		m_strPeStruct += strTmp;
		strTmp.Format(L"PointerToRelocations��   0x%08X        0x%08X	  [��OBJ�ļ���ʹ��, �ض�λ��ƫ��.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].PointerToRelocations - pBaseAdd, pe->m_pSectionHead[i].PointerToRelocations);
		m_strPeStruct += strTmp;
		strTmp.Format(L"PointerToLinenumbers��   0x%08X        0x%08X	  [�кű��ƫ��, �ṩ����.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].PointerToLinenumbers - pBaseAdd, pe->m_pSectionHead[i].PointerToLinenumbers);
		m_strPeStruct += strTmp;
		strTmp.Format(L"NumberOfRelocations��    0x%08X        0x%04X	  [��OBJ�ļ���ʹ��, �ض�λ����Ŀ.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].NumberOfRelocations - pBaseAdd, pe->m_pSectionHead[i].NumberOfRelocations);
		m_strPeStruct += strTmp;
		strTmp.Format(L"NumberOfLinenumbers��    0x%08X        0x%04X	  [�кű����кŵ���Ŀ.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].NumberOfLinenumbers - pBaseAdd, pe->m_pSectionHead[i].NumberOfLinenumbers);
		m_strPeStruct += strTmp;
		strTmp.Format(L"Characteristics��        0x%08X        0x%08X     [��־(������)]\r\n"
			, (byte*)&pe->m_pSectionHead[i].Characteristics - pBaseAdd, pe->m_pSectionHead[i].Characteristics);
		m_strPeStruct += strTmp;

		strTmp.Format(L"[��ַ(RAW)��Χ:0x%08X - 0x%08X]\r\n"
			, pe->m_pSectionHead[i].PointerToRawData, pe->m_pSectionHead[i].PointerToRawData + pe->m_pSectionHead[i].SizeOfRawData -1);
		m_strPeStruct += strTmp;

		m_strPeStruct += L"------------------------------------------------------------\r\n";
	}
	m_strPeStruct += L" ��־(���Կ�)       ��������ֵ���ձ�\r\n";
	m_strPeStruct += L"[ֵ:00000020h]  [IMAGE_SCN_CNT_CODE                // Section contains code.(������ִ�д���)]\r\n";
	m_strPeStruct += L"[ֵ:00000040h]  [IMAGE_SCN_CNT_INITIALIZED_DATA    // Section contains initialized data.(�ÿ�����ѳ�ʼ��������)]\r\n";
	m_strPeStruct += L"[ֵ:00000080h]  [IMAGE_SCN_CNT_UNINITIALIZED_DATA  // Section contains uninitialized data.(�ÿ����δ��ʼ��������)]\r\n";
	m_strPeStruct += L"[ֵ:00000200h]  [IMAGE_SCN_LNK_INFO                // Section contains comments or some other type of information.]\r\n";
	m_strPeStruct += L"[ֵ:00000800h]  [IMAGE_SCN_LNK_REMOVE              // Section contents will not become part of image.]\r\n";
	m_strPeStruct += L"[ֵ:00001000h]  [IMAGE_SCN_LNK_COMDAT              // Section contents comdat.]\r\n";
	m_strPeStruct += L"[ֵ:00004000h]  [IMAGE_SCN_NO_DEFER_SPEC_EXC       // Reset speculative exceptions handling bits in the TLB entries for this section.]\r\n";
	m_strPeStruct += L"[ֵ:00008000h]  [IMAGE_SCN_GPREL                   // Section content can be accessed relative to GP.]\r\n";
	m_strPeStruct += L"[ֵ:00500000h]  [IMAGE_SCN_ALIGN_16BYTES           // Default alignment if no others are specified.]\r\n";
	m_strPeStruct += L"[ֵ:01000000h]  [IMAGE_SCN_LNK_NRELOC_OVFL         // Section contains extended relocations.]\r\n";
	m_strPeStruct += L"[ֵ:02000000h]  [IMAGE_SCN_MEM_DISCARDABLE         // Section can be discarded.]\r\n";
	m_strPeStruct += L"[ֵ:04000000h]  [IMAGE_SCN_MEM_NOT_CACHED          // Section is not cachable.]\r\n";
	m_strPeStruct += L"[ֵ:08000000h]  [IMAGE_SCN_MEM_NOT_PAGED           // Section is not pageable.]\r\n";
	m_strPeStruct += L"[ֵ:10000000h]  [IMAGE_SCN_MEM_SHARED              // Section is shareable(�ÿ�Ϊ�����).]\r\n";
	m_strPeStruct += L"[ֵ:20000000h]  [IMAGE_SCN_MEM_EXECUTE             // Section is executable.(�ÿ��ִ��)]\r\n";
	m_strPeStruct += L"[ֵ:40000000h]  [IMAGE_SCN_MEM_READ                // Section is readable.(�ÿ�ɶ�)]\r\n";
	m_strPeStruct += L"[ֵ:80000000h]  [IMAGE_SCN_MEM_WRITE               // Section is writeable.(�ÿ��д)]\r\n";
	m_strPeStruct += L"------------------------------------------------------------\r\n";

	m_strPeStruct += L"���ֳ�����(Sections) ��������\r\n";

	m_strPeStruct += L"[.text]  [ָ�����.]\r\n";
	m_strPeStruct += L"[.data]  [��ʼ��������.]\r\n";
	m_strPeStruct += L"[.idata] [�����.]\r\n";
	m_strPeStruct += L"[.rsrc]  [��Դ����.]\r\n";
	m_strPeStruct += L"[.reloc] [����ַ�ض�λ��.]\r\n";
	m_strPeStruct += L"[.edata] [�����.]\r\n";
	m_strPeStruct += L"[.tls]   [thread local storage, �ֲ߳̾��洢��.]\r\n";
	m_strPeStruct += L"[.rdata] [��ŵ���Ŀ¼��˵���ַ���.]\r\n";

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}