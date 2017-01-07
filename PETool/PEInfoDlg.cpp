// PEFileInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "PEInfoDlg.h"
#include "afxdialogex.h"


// CPEFileInfo 对话框

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


// CPEFileInfo 消息处理程序


void CPEInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CPEInfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//NT头
	CString strTmp;
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	CString strOptHeader;
	if (pe->m_pOptionalHeader32)
	{
		m_strPeStruct += L"IMAGE_NT_HEADERS32 (PE文件头)结构说明：\r\n";
		strOptHeader.Format(L"OptionalHeader： [地址(RAW)范围:0x%08X - 0x%08X] [长度:%xh] [IMAGE_OPTIONAL_HEADER32结构, 默认长度为\"e0h\"(224).]\r\n"
			, (byte*)pe->m_pOptionalHeader32 - pBaseAdd
			, (byte*)pe->m_pSectionHead - 1 - pBaseAdd
			, ((byte*)pe->m_pSectionHead) - pBaseAdd);

	}
	else
	{
		m_strPeStruct += L"IMAGE_NT_HEADERS64 (PE文件头)结构说明：\r\n";
		strOptHeader.Format(L"OptionalHeader： [地址(RAW)范围:0x%08X - 0x%08X][长度:%xh] [IMAGE_OPTIONAL_HEADER64结构, 默认长度为\"f0h\"(240).]\r\n"
			, (byte*)pe->m_pOptionalHeader64 - pBaseAdd
			, (byte*)pe->m_pSectionHead - 1 - pBaseAdd
			, ((byte*)pe->m_pSectionHead) - pBaseAdd);
	}
	strTmp.Format(L"Signature：      [地址(RAW)范围:0x%08X - 0x%08X] [长度:04h] [PE文件标志(\"PE\", 0, 0), 长度为\"4\".]\r\n"
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead - 4
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead - 1);
	m_strPeStruct += strTmp;
	strTmp.Format(L"FileHeader：     [地址(RAW)范围:0x%08X - 0x%08X] [长度:14h] [IMAGE_FILE_HEADER结构, 长度为\"20\".]\r\n"
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead
		, (byte*)pe->m_pFileHead - (byte*)pe->m_pDosHead + sizeof(IMAGE_FILE_HEADER) - 1);
	m_strPeStruct += strTmp;
	m_strPeStruct += strOptHeader;

	m_strPeStruct += L"\r\n\r\n";

	m_strPeStruct += L"IMAGE_FILE_HEADER(映像文件头)结构如下：\r\n";
	strTmp.Format(L"Machine：              [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x04] [数据:0x%04X]     [运行平台(可执行文件的CPU类型).]\r\n"
		, (byte*)pe->m_pFileHead - pBaseAdd, pe->m_pFileHead->Machine);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfSections：     [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x06] [数据:0x%04X]     [区段 / 节 / 块(Section)的数目.]\r\n"
		, (byte*)&pe->m_pFileHead->NumberOfSections - pBaseAdd
		, pe->m_pFileHead->NumberOfSections);
	m_strPeStruct += strTmp;
	strTmp.Format(L"TimeDateStamp：        [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x08] [数据:0x48025287] [文件创建时的时间戳.]\r\n"
		, (byte*)&pe->m_pFileHead->TimeDateStamp - pBaseAdd
		, pe->m_pFileHead->TimeDateStamp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"PointerOfSymbolTable： [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x0C] [数据:0x%08X] [COFF符号指针, 指向符号表(用于调试).]\r\n"
		, (byte*)&pe->m_pFileHead->PointerToSymbolTable - pBaseAdd
		, pe->m_pFileHead->PointerToSymbolTable);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfSymbols：      [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x10] [数据:0x%08X] [符号表(即上一字段)中的符号个数(用于调试).]\r\n"
		, (byte*)&pe->m_pFileHead->NumberOfSymbols - pBaseAdd
		, pe->m_pFileHead->NumberOfSymbols);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfOptionalHeader： [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x14] [数据:0x%04X] \
		    [可选首部长度(可选头大小).在OBJ中, 该字段为0; 在可执行文件中, 是指IMAGE_OPTIONAL_HEADER结构的长度.]\r\n"
		, (byte*)&pe->m_pFileHead->SizeOfOptionalHeader - pBaseAdd
		, pe->m_pFileHead->SizeOfOptionalHeader);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Characteristics：      [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x16] [数据:0x%04X]     [文件属性 / 特性(文件信息标志).]\r\n\r\n"
		, (byte*)&pe->m_pFileHead->Characteristics - pBaseAdd
		, pe->m_pFileHead->Characteristics);
	m_strPeStruct += strTmp;
	m_strPeStruct += L"文件属性 特征值对照表：\r\n";

	m_strPeStruct += L"[值:0001h][IMAGE_FILE_RELOCS_STRIPPED          // Relocation info stripped from file.(重定位信息被移去)]\r\n";
	m_strPeStruct += L"[值:0002h][IMAGE_FILE_EXECUTABLE_IMAGE         // File is executable (i.e. no unresolved externel references).(文件可执行)]\r\n";
	m_strPeStruct += L"[值:0004h][IMAGE_FILE_LINE_NUMS_STRIPPED       // Line nunbers stripped from file.(行号被移去)]\r\n";
	m_strPeStruct += L"[值:0008h][IMAGE_FILE_LOCAL_SYMS_STRIPPED      // Local symbols stripped from file.(符号被移去)]\r\n";
	m_strPeStruct += L"[值:0010h][IMAGE_FILE_AGGRESIVE_WS_TRIM        // Agressively trim working set.(主动调整工作区)]\r\n";
	m_strPeStruct += L"[值:0020h][IMAGE_FILE_LARGE_ADDRESS_AWARE      // App can handle >2gb addresses.(高地址警告)]\r\n";
	m_strPeStruct += L"[值:0080h][IMAGE_FILE_BYTES_REVERSED_LO        // Bytes of machine word are reversed.(处理机的低位字节是相反的)]\r\n";
	m_strPeStruct += L"[值:0100h][IMAGE_FILE_32BIT_MACHINE            // 32 bit word machine. (32位机器)]\r\n";
	m_strPeStruct += L"[值:0200h][IMAGE_FILE_DEBUG_STRIPPED           // Debugging info stripped from file in .DBG file.(.DBG文件的调试信息被移去)]\r\n";
	m_strPeStruct += L"[值:0400h][IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP  // If Image is on removable media, copy and run from the swap file.(如果映象文件是在可移动媒体中,则先复制到交换文件后再运行)]\r\n";
	m_strPeStruct += L"[值:0800h][IMAGE_FILE_NET_RUN_FROM_SWAP        // If Image is on Net, copy and run from the swap file.(如果映象文件是在网络中,则复制到交换文件后才运行)]\r\n";
	m_strPeStruct += L"[值:1000h][IMAGE_FILE_SYSTEM                   // System File.(系统文件)]\r\n";
	m_strPeStruct += L"[值:2000h][IMAGE_FILE_DLL                      // File is a DLL.(文件是DLL文件)]\r\n";
	m_strPeStruct += L"[值:4000h][IMAGE_FILE_UP_SYSTEM_ONLY           // File should only be run on a UP machine.(文件只能运行在单处理器上)]\r\n";
	m_strPeStruct += L"[值:8000h][IMAGE_FILE_BYTES_REVERSED_HI        // Bytes of machine word are reversed.(处理机的高位字节是相反的)]\r\n\r\n";

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
	m_strPeStruct += L"IMAGE_OPTIONAL_HEADER64(可选映像头)结构如下：\r\n";

	strTmp.Format(L"Magic：                      [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x18] [数据:0x%04X]     [标志字(幻数), 常值为\"010Bh\".用来说明文件是ROM映像, 还是普通可执行的映像.]\r\n"
		, (byte*)pe->m_pOptionalHeader64 - pBaseAdd, pe->m_pOptionalHeader64->Magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorLinkerVersion：         [地址(RAW):0x%08X] [长度:01h] [偏移量:e_lfanew + 0x1A] [数据:0x%02X]       [链接器主(首)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorLinkerVersion：         [地址(RAW):0x%08X] [长度:01h] [偏移量:e_lfanew + 0x1B] [数据:0x%02X]       [链接器次(副)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfCode：                 [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x1C] [数据:0x%08X] [代码段(块)大小, 所有Code Section总共的大小(只入不舍), 这个值是向上对齐某一个值的整数倍.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfCode - pBaseAdd, pe->m_pOptionalHeader64->SizeOfCode);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfInitializedData：      [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x20] [数据:0x%08X] [已初始化数据块大小.即在编译时所构成的块的大小(不包括代码段), 但这个数据并不太准确.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfInitializedData - pBaseAdd, pe->m_pOptionalHeader64->SizeOfInitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfUninitializedData：    [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x24] [数据:0x%08X] [未初始化数据块大小.装载程序要在虚拟地址空间中为这些数据约定空间.未初始化数据通常在.bbs块中.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfUninitializedData - pBaseAdd, pe->m_pOptionalHeader64->SizeOfUninitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"AddressOfEntryPoint(RVA)：   [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x28] [数据:0x%08X] [程序开始执行的入口地址 / 入口点EP(RVA).这是一个\"相对虚拟地址\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->AddressOfEntryPoint - pBaseAdd, pe->m_pOptionalHeader64->AddressOfEntryPoint);
	m_strPeStruct += strTmp;
	strTmp.Format(L"BaseOfCode：                 [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x2C] [数据:0x%08X] [代码段(块)起始地址.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->BaseOfCode - pBaseAdd, pe->m_pOptionalHeader64->BaseOfCode);
	m_strPeStruct += strTmp;
	// 		strTmp.Format(L"BaseOfData：                 [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x30] [数据:0x%08X] [数据段(块)起始地址.]\r\n"
	// 			, (byte*)pe->m_pOptionalHeader64->BaseOfData - pBaseAdd, pe->m_pOptionalHeader64->BaseOfData);
	// 		m_strPeStruct += strTmp;
	strTmp.Format(L"ImageBase：                  [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x34] [数据:0x%08X] [基址, 程序默认装入的基地址.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->ImageBase - pBaseAdd, pe->m_pOptionalHeader64->ImageBase);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SectionAlignment：           [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x38] [数据:0x%08X] [内存中的节(块\"Section\")的对齐值, 常为:0x1000或0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SectionAlignment - pBaseAdd, pe->m_pOptionalHeader64->SectionAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"FileAlignment：              [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x3C] [数据:0x%08X] [文件中的节(块\"Section\")的对齐值, 常为:0x1000或0x200或0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->FileAlignment - pBaseAdd, pe->m_pOptionalHeader64->FileAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorOperatingSystemVersion：[地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x40] [数据:0x%04X]     [操作系统主(首)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorOperatingSystemVersion：[地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x42] [数据:0x%04X]     [操作系统次(副)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorImageVersion：          [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x44] [数据:0x%04X]     [该可执行文件的主(首)版本号, 由程序员自定义.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorImageVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorImageVersion：          [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x46] [数据:0x%04X]     [该可执行文件的次(副)版本号, 由程序员自定义.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorImageVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorSubsystemVersion：      [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x48] [数据:0x%04X]     [所需子系统主(首)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MajorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MajorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorSubsystemVersion：      [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x4A] [数据:0x%04X]     [所需子系统次(副)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->MinorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader64->MinorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Win32VersionValue：          [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x4C] [数据:0x%08X] [保留.总是\"00000000\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->Win32VersionValue - pBaseAdd, pe->m_pOptionalHeader64->Win32VersionValue);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfImage：                [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x50] [数据:0x%08X] [映像大小(映像装入内存后的总尺寸 / 内存中整个PE映像的尺寸).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfImage - pBaseAdd, pe->m_pOptionalHeader64->SizeOfImage);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeaders：		     [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x54] [数据:0x%08X] [首部及块表(首部 + 块表)的大小.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfHeaders - pBaseAdd, pe->m_pOptionalHeader64->SizeOfHeaders);
	m_strPeStruct += strTmp;
	strTmp.Format(L"CheckSum：                   [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x58] [数据:0x%08X] [CRC校验和.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->CheckSum - pBaseAdd, pe->m_pOptionalHeader64->CheckSum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Subsystem：                  [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x5C] [数据:0x%04X]     [子系统:Windows 图形用户界面 / 图形接口子系统(Image runs in the Windows GUI subsystem.).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->Subsystem - pBaseAdd, pe->m_pOptionalHeader64->Subsystem);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DllCharacteristics：         [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x5E] [数据:0x%04X]     [DLLMain()函数何时被调用.当文件为DLL程序时使用, 默认值为\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->DllCharacteristics - pBaseAdd, pe->m_pOptionalHeader64->DllCharacteristics);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackReserve：         [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x60] [数据:0x%08X] [初始化时为线程保留的栈大小.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfStackReserve - pBaseAdd, pe->m_pOptionalHeader64->SizeOfStackReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackCommit：          [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x64] [数据:0x%08X] [初始化时线程实际使用的栈大小.这个值总比\"SizeOfStackReserve\"要小一些.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfStackCommit - pBaseAdd, pe->m_pOptionalHeader64->SizeOfStackCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapReserve：          [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x68] [数据:0x%08X] [初始化时为进程保留的堆大小.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfHeapReserve - pBaseAdd, pe->m_pOptionalHeader64->SizeOfHeapReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapCommit：           [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x6C] [数据:0x%08X] [初始化时进程实际使用的堆大小.这个值总比\"SizeOfHeapReserve\"要小一些.]\r\n"
		, (byte*)pe->m_pOptionalHeader64->SizeOfHeapCommit - pBaseAdd, pe->m_pOptionalHeader64->SizeOfHeapCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"LoaderFlags：                [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x70] [数据:0x%08X] [设置自动调用断点或调试器.与调试有关, 默认值为\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader64->LoaderFlags - pBaseAdd, pe->m_pOptionalHeader64->LoaderFlags);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfRvaAndSizes：        [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x74] [数据:0x%08X] [数据目录结构的数量(项数).值总为\"00000010h\"(16项).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->NumberOfRvaAndSizes - pBaseAdd, pe->m_pOptionalHeader64->NumberOfRvaAndSizes);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DataDirectory：              [地址(RAW)范围:0x%08X - 0x%08X] [长度:80h] [数据目录表(16项, 每个成员占8字节).]\r\n"
		, (byte*)pe->m_pOptionalHeader64->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader64->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";

	ShowDataDirectory64(pe, pBaseAdd);


	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}

void CPEInfoDlg::ShowDataDirectory64(const CPE * pe, const byte * pBaseAdd)
{
	CString strTmp;
	//数据目录表
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DATA_DIRECTORY(数据目录表)结构如下：\r\n";

	strTmp.Format(L"[地址(RAW)范围:0x%08X - 0x%08X] [长度:0x%02Xh] [数据目录表(16项, 每个成员占8字节).]\r\n\r\n"
		, (byte*)pe->m_pOptionalHeader64->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader64->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1
		, ((byte*)&pe->m_pOptionalHeader64->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd) - ((byte*)pe->m_pOptionalHeader64->DataDirectory - pBaseAdd));
	m_strPeStruct += strTmp;
	m_strPeStruct += L"    [成员]                  [地址(RAW)]     [偏移量]           [数据:RVA]         [大小]   [说明]               [结构]\r\n";
	strTmp.Format(L"Export Table：              0x%08X  [e_lfanew + 0x078]     0x%08X     0x%08X  [导出表]   [IMAGE_DIRECTORY_ENTRY_EXPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[0]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[0].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[0].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Table：              0x%08X  [e_lfanew + 0x080]     0x%08X     0x%08X  [导入表]   [IMAGE_DIRECTORY_ENTRY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[1]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[1].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[1].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Resources Table：           0x%08X  [e_lfanew + 0x088]     0x%08X     0x%08X  [资源]     [IMAGE_DIRECTORY_ENTRY_RESOURCE]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[2]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[2].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[2].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Exception Table：           0x%08X  [e_lfanew + 0x090]     0x%08X     0x%08X  [异常]     [IMAGE_DIRECTORY_ENTRY_EXCEPTION]\r\n"
		, (byte*) &(pe->m_pOptionalHeader64->DataDirectory[3]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[3].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[3].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Security Table：            0x%08X  [e_lfanew + 0x098]     0x%08X     0x%08X  [安全证书] [IMAGE_DIRECTORY_ENTRY_SECURITY]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[4]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[4].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[4].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Base relocation Table：     0x%08X  [e_lfanew + 0x0A0]     0x%08X     0x%08X  [重定位表] [IMAGE_DIRECTORY_ENTRY_BASERELOC]\r\n"
		, (byte*) &(pe->m_pOptionalHeader64->DataDirectory[5]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[5].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[5].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Debug：                     0x%08X  [e_lfanew + 0x0A8]     0x%08X     0x%08X  [调试信息] [IMAGE_DIRECTORY_ENTRY_DEBUG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[6]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[6].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[6].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Architecture(Copyrught)：   0x%08X  [e_lfanew + 0x0B0]     0x%08X     0x%08X  [版权所有] [IMAGE_DIRECTORY_ENTRY_ARCHITECTURE(IMAGE_DIRECTORY_ENTRY_COPYRIGHT)]\r\n"
		, (byte*) &(pe->m_pOptionalHeader64->DataDirectory[7]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[7].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[7].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Global Ptr：                0x%08X  [e_lfanew + 0x0B8]     0x%08X     0x%08X  [全局指针] [IMAGE_DIRECTORY_ENTRY_GLOBALPTR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[8]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[8].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[8].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Tread local storage(TLS)：  0x%08X  [e_lfanew + 0x0C0]     0x%08X     0x%08X  [TLS 表]   [IMAGE_DIRECTORY_ENTRY_TLS]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[9]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[9].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[9].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Load configuration：        0x%08X  [e_lfanew + 0x0C8]     0x%08X     0x%08X  [加载配置] [IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[10]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[10].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[10].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Bound Import：              0x%08X  [e_lfanew + 0x0D0]     0x%08X     0x%08X  [绑定导入] [IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[11]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[11].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[11].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Address Table(IAT)： 0x%08X  [e_lfanew + 0x0D8]     0x%08X     0x%08X  [IAT 表]   [IMAGE_DIRECTORY_ENTRY_IAT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[12]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[12].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[12].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Delay Import：              0x%08X  [e_lfanew + 0x0E0]     0x%08X     0x%08X  [延迟导入] [IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[13]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[13].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[13].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"COM descriptor：            0x%08X  [e_lfanew + 0x0E8]     0x%08X     0x%08X  [COM]      [IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[14]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[14].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[14].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"保留：                      0x%08X  [e_lfanew + 0x0F0]     0x%08X     0x%08X  [保留]     [NULL]\r\n"
		, (byte*)&(pe->m_pOptionalHeader64->DataDirectory[15]) - pBaseAdd, pe->m_pOptionalHeader64->DataDirectory[15].VirtualAddress, pe->m_pOptionalHeader64->DataDirectory[15].Size);
	m_strPeStruct += strTmp;
}

void CPEInfoDlg::ShowOptionalHeader32(const CPE * pe, const byte * pBaseAdd)
{
	CString strTmp;
	m_strPeStruct += L"IMAGE_OPTIONAL_HEADER32(可选映像头)结构如下：\r\n";

	strTmp.Format(L"Magic：                      [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x18] [数据:0x%04X]     [标志字(幻数), 常值为\"010Bh\".用来说明文件是ROM映像, 还是普通可执行的映像.]\r\n"
		, (byte*)pe->m_pOptionalHeader32 - pBaseAdd, pe->m_pOptionalHeader32->Magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorLinkerVersion：         [地址(RAW):0x%08X] [长度:01h] [偏移量:e_lfanew + 0x1A] [数据:0x%02X]       [链接器主(首)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorLinkerVersion：         [地址(RAW):0x%08X] [长度:01h] [偏移量:e_lfanew + 0x1B] [数据:0x%02X]       [链接器次(副)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorLinkerVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorLinkerVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfCode：                 [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x1C] [数据:0x%08X] [代码段(块)大小, 所有Code Section总共的大小(只入不舍), 这个值是向上对齐某一个值的整数倍.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfCode - pBaseAdd, pe->m_pOptionalHeader32->SizeOfCode);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfInitializedData：      [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x20] [数据:0x%08X] [已初始化数据块大小.即在编译时所构成的块的大小(不包括代码段), 但这个数据并不太准确.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfInitializedData - pBaseAdd, pe->m_pOptionalHeader32->SizeOfInitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfUninitializedData：    [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x24] [数据:0x%08X] [未初始化数据块大小.装载程序要在虚拟地址空间中为这些数据约定空间.未初始化数据通常在.bbs块中.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfUninitializedData - pBaseAdd, pe->m_pOptionalHeader32->SizeOfUninitializedData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"AddressOfEntryPoint(RVA)：   [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x28] [数据:0x%08X] [程序开始执行的入口地址 / 入口点EP(RVA).这是一个\"相对虚拟地址\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->AddressOfEntryPoint - pBaseAdd, pe->m_pOptionalHeader32->AddressOfEntryPoint);
	m_strPeStruct += strTmp;
	strTmp.Format(L"BaseOfCode：                 [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x2C] [数据:0x%08X] [代码段(块)起始地址.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->BaseOfCode - pBaseAdd, pe->m_pOptionalHeader32->BaseOfCode);
	m_strPeStruct += strTmp;
	strTmp.Format(L"BaseOfData：                 [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x30] [数据:0x%08X] [数据段(块)起始地址.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->BaseOfData - pBaseAdd, pe->m_pOptionalHeader32->BaseOfData);
	m_strPeStruct += strTmp;
	strTmp.Format(L"ImageBase：                  [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x34] [数据:0x%08X] [基址, 程序默认装入的基地址.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->ImageBase - pBaseAdd, pe->m_pOptionalHeader32->ImageBase);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SectionAlignment：           [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x38] [数据:0x%08X] [内存中的节(块\"Section\")的对齐值, 常为:0x1000或0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SectionAlignment - pBaseAdd, pe->m_pOptionalHeader32->SectionAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"FileAlignment：              [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x3C] [数据:0x%08X] [文件中的节(块\"Section\")的对齐值, 常为:0x1000或0x200或0x04.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->FileAlignment - pBaseAdd, pe->m_pOptionalHeader32->FileAlignment);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorOperatingSystemVersion：[地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x40] [数据:0x%04X]     [操作系统主(首)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorOperatingSystemVersion：[地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x42] [数据:0x%04X]     [操作系统次(副)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorOperatingSystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorOperatingSystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorImageVersion：          [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x44] [数据:0x%04X]     [该可执行文件的主(首)版本号, 由程序员自定义.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorImageVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorImageVersion：          [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x46] [数据:0x%04X]     [该可执行文件的次(副)版本号, 由程序员自定义.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorImageVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorImageVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MajorSubsystemVersion：      [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x48] [数据:0x%04X]     [所需子系统主(首)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MajorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MajorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"MinorSubsystemVersion：      [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x4A] [数据:0x%04X]     [所需子系统次(副)版本号.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->MinorSubsystemVersion - pBaseAdd, pe->m_pOptionalHeader32->MinorSubsystemVersion);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Win32VersionValue：          [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x4C] [数据:0x%08X] [保留.总是\"00000000\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->Win32VersionValue - pBaseAdd, pe->m_pOptionalHeader32->Win32VersionValue);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfImage：                [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x50] [数据:0x%08X] [映像大小(映像装入内存后的总尺寸 / 内存中整个PE映像的尺寸).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfImage - pBaseAdd, pe->m_pOptionalHeader32->SizeOfImage);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeaders：		     [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x54] [数据:0x%08X] [首部及块表(首部 + 块表)的大小.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfHeaders - pBaseAdd, pe->m_pOptionalHeader32->SizeOfHeaders);
	m_strPeStruct += strTmp;
	strTmp.Format(L"CheckSum：                   [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x58] [数据:0x%08X] [CRC校验和.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->CheckSum - pBaseAdd, pe->m_pOptionalHeader32->CheckSum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Subsystem：                  [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x5C] [数据:0x%04X]     [子系统:Windows 图形用户界面 / 图形接口子系统(Image runs in the Windows GUI subsystem.).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->Subsystem - pBaseAdd, pe->m_pOptionalHeader32->Subsystem);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DllCharacteristics：         [地址(RAW):0x%08X] [长度:02h] [偏移量:e_lfanew + 0x5E] [数据:0x%04X]     [DLLMain()函数何时被调用.当文件为DLL程序时使用, 默认值为\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->DllCharacteristics - pBaseAdd, pe->m_pOptionalHeader32->DllCharacteristics);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackReserve：         [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x60] [数据:0x%08X] [初始化时为线程保留的栈大小.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfStackReserve - pBaseAdd, pe->m_pOptionalHeader32->SizeOfStackReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfStackCommit：          [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x64] [数据:0x%08X] [初始化时线程实际使用的栈大小.这个值总比\"SizeOfStackReserve\"要小一些.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfStackCommit - pBaseAdd, pe->m_pOptionalHeader32->SizeOfStackCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapReserve：          [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x68] [数据:0x%08X] [初始化时为进程保留的堆大小.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfHeapReserve - pBaseAdd, pe->m_pOptionalHeader32->SizeOfHeapReserve);
	m_strPeStruct += strTmp;
	strTmp.Format(L"SizeOfHeapCommit：           [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x6C] [数据:0x%08X] [初始化时进程实际使用的堆大小.这个值总比\"SizeOfHeapReserve\"要小一些.]\r\n"
		, (byte*)pe->m_pOptionalHeader32->SizeOfHeapCommit - pBaseAdd, pe->m_pOptionalHeader32->SizeOfHeapCommit);
	m_strPeStruct += strTmp;
	strTmp.Format(L"LoaderFlags：                [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x70] [数据:0x%08X] [设置自动调用断点或调试器.与调试有关, 默认值为\"0\".]\r\n"
		, (byte*)pe->m_pOptionalHeader32->LoaderFlags - pBaseAdd, pe->m_pOptionalHeader32->LoaderFlags);
	m_strPeStruct += strTmp;
	strTmp.Format(L"NumberOfRvaAndSizes：        [地址(RAW):0x%08X] [长度:04h] [偏移量:e_lfanew + 0x74] [数据:0x%08X] [数据目录结构的数量(项数).值总为\"00000010h\"(16项).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->NumberOfRvaAndSizes - pBaseAdd, pe->m_pOptionalHeader32->NumberOfRvaAndSizes);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DataDirectory：              [地址(RAW)范围:0x%08X - 0x%08X] [长度:80h] [数据目录表(16项, 每个成员占8字节).]\r\n"
		, (byte*)pe->m_pOptionalHeader32->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader32->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";

	ShowDataDirectory32(pe, pBaseAdd);

}

void CPEInfoDlg::ShowDataDirectory32(const CPE * pe, const byte * pBaseAdd)
{
	CString strTmp;
	//数据目录表
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DATA_DIRECTORY(数据目录表)结构如下：\r\n";

	strTmp.Format(L"[地址(RAW)范围:0x%08X - 0x%08X] [长度:0x%02Xh] [数据目录表(16项, 每个成员占8字节).]\r\n\r\n"
		, (byte*)pe->m_pOptionalHeader32->DataDirectory - pBaseAdd, (byte*)&pe->m_pOptionalHeader32->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd - 1
		, ((byte*)&pe->m_pOptionalHeader32->DataDirectory + (sizeof(IMAGE_DATA_DIRECTORY) * 16) - pBaseAdd) - ((byte*)pe->m_pOptionalHeader32->DataDirectory - pBaseAdd));
	m_strPeStruct += strTmp;
	m_strPeStruct += L"    [成员]                  [地址(RAW)]     [偏移量]           [数据:RVA]         [大小]   [说明]               [结构]\r\n";
	strTmp.Format(L"Export Table：              0x%08X  [e_lfanew + 0x078]     0x%08X     0x%08X  [导出表]   [IMAGE_DIRECTORY_ENTRY_EXPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[0]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[0].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[0].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Table：              0x%08X  [e_lfanew + 0x080]     0x%08X     0x%08X  [导入表]   [IMAGE_DIRECTORY_ENTRY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[1]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[1].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[1].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Resources Table：           0x%08X  [e_lfanew + 0x088]     0x%08X     0x%08X  [资源]     [IMAGE_DIRECTORY_ENTRY_RESOURCE]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[2]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[2].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[2].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Exception Table：           0x%08X  [e_lfanew + 0x090]     0x%08X     0x%08X  [异常]     [IMAGE_DIRECTORY_ENTRY_EXCEPTION]\r\n"
		, (byte*) &(pe->m_pOptionalHeader32->DataDirectory[3]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[3].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[3].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Security Table：            0x%08X  [e_lfanew + 0x098]     0x%08X     0x%08X  [安全证书] [IMAGE_DIRECTORY_ENTRY_SECURITY]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[4]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[4].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[4].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Base relocation Table：     0x%08X  [e_lfanew + 0x0A0]     0x%08X     0x%08X  [重定位表] [IMAGE_DIRECTORY_ENTRY_BASERELOC]\r\n"
		, (byte*) &(pe->m_pOptionalHeader32->DataDirectory[5]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[5].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[5].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Debug：                     0x%08X  [e_lfanew + 0x0A8]     0x%08X     0x%08X  [调试信息] [IMAGE_DIRECTORY_ENTRY_DEBUG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[6]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[6].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[6].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Architecture(Copyrught)：   0x%08X  [e_lfanew + 0x0B0]     0x%08X     0x%08X  [版权所有] [IMAGE_DIRECTORY_ENTRY_ARCHITECTURE(IMAGE_DIRECTORY_ENTRY_COPYRIGHT)]\r\n"
		, (byte*) &(pe->m_pOptionalHeader32->DataDirectory[7]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[7].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[7].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Global Ptr：                0x%08X  [e_lfanew + 0x0B8]     0x%08X     0x%08X  [全局指针] [IMAGE_DIRECTORY_ENTRY_GLOBALPTR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[8]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[8].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[8].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Tread local storage(TLS)：  0x%08X  [e_lfanew + 0x0C0]     0x%08X     0x%08X  [TLS 表]   [IMAGE_DIRECTORY_ENTRY_TLS]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[9]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[9].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[9].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Load configuration：        0x%08X  [e_lfanew + 0x0C8]     0x%08X     0x%08X  [加载配置] [IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[10]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[10].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[10].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Bound Import：              0x%08X  [e_lfanew + 0x0D0]     0x%08X     0x%08X  [绑定导入] [IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[11]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[11].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[11].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Import Address Table(IAT)： 0x%08X  [e_lfanew + 0x0D8]     0x%08X     0x%08X  [IAT 表]   [IMAGE_DIRECTORY_ENTRY_IAT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[12]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[12].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[12].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"Delay Import：              0x%08X  [e_lfanew + 0x0E0]     0x%08X     0x%08X  [延迟导入] [IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[13]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[13].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[13].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"COM descriptor：            0x%08X  [e_lfanew + 0x0E8]     0x%08X     0x%08X  [COM]      [IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[14]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[14].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[14].Size);
	m_strPeStruct += strTmp;
	strTmp.Format(L"保留：                      0x%08X  [e_lfanew + 0x0F0]     0x%08X     0x%08X  [保留]     [NULL]\r\n"
		, (byte*)&(pe->m_pOptionalHeader32->DataDirectory[15]) - pBaseAdd, pe->m_pOptionalHeader32->DataDirectory[15].VirtualAddress, pe->m_pOptionalHeader32->DataDirectory[15].Size);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}

void CPEInfoDlg::ShowDosHead(const CPE * pe, const byte * pBaseAdd)
{
	m_strPeStruct += L"DOS首部 结构说明：\r\n\r\n";
	CString strTmp;
	DWORD dosSub = (byte*)&(pe->m_pDosHead->e_lfanew) - pBaseAdd + sizeof(DWORD) - 1;
	strTmp.Format(L"MZ header：      [地址(RAW)范围:0x00000000 - 0x%08X] [长度:0040h] [名称:IMAGE_DOS_HEADER] [DOS文件头.]\r\n", dosSub);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DOS stub header：[地址(RAW)范围:0x%08X - 0x%08X][长度:00a0h][名称:DOS STUB][DOS下有效的EXE文件格式, 存根(长度不定).]\r\n", dosSub + 1, pe->m_pDosHead->e_lfanew - 1);
	m_strPeStruct += strTmp;
	//DOS头
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DOS_HEADER (DOS文件头)结构如下：\r\n\r\n";
	strTmp.Format(L"e_magic：    [地址(RAW):0x00000000] [长度:02h] [数据:0x%X] [Magic number.][DOS可执行文件标记\"MZ\"头,定义为\"5A4Dh\",定值.]\r\n", pe->m_pDosHead->e_magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cblp：     [地址(RAW):0x00000002] [长度:02h] [数据:0x%04X] [Bytes on last page of file.]\r\n", pe->m_pDosHead->e_cblp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cp：	     [地址(RAW):0x00000004] [长度:02h] [数据:0x%04X] [Pages in file.]\r\n", pe->m_pDosHead->e_cp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_crlc：     [地址(RAW):0x00000006] [长度:02h] [数据:0x%04X] [Relocations.]\r\n", pe->m_pDosHead->e_crlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cparhdr：  [地址(RAW):0x00000008] [长度:02h] [数据:0x%04X] [Size of header in paragraphs.]\r\n", pe->m_pDosHead->e_cparhdr);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_minalloc： [地址(RAW):0x0000000a] [长度:02h] [数据:0x%04X] [Minimum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_minalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_maxalloc： [地址(RAW):0x0000000c] [长度:02h] [数据:0x%04X] [Maximum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_maxalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ss：       [地址(RAW):0x0000000e] [长度:02h] [数据:0x%04X] [Initial(relative) SS value.]\r\n", pe->m_pDosHead->e_ss);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_sp：       [地址(RAW):0x00000010] [长度:02h] [数据:0x%04X] [Initial SP value.]\r\n", pe->m_pDosHead->e_sp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_csum：     [地址(RAW):0x00000012] [长度:02h] [数据:0x%04X] [Checksum.]\r\n", pe->m_pDosHead->e_csum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ip：       [地址(RAW):0x00000014] [长度:02h] [数据:0x%04X] [Initial IP value.] [DOS代码入口IP.]\r\n", pe->m_pDosHead->e_ip);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cs：       [地址(RAW):0x00000016] [长度:02h] [数据:0x%04X] [Initial(relative) CS value.] [DOS代码的入口CS.]\r\n", pe->m_pDosHead->e_cs);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfarlc：   [地址(RAW):0x00000018] [长度:02h] [数据:0x%04X] [File address of relocation table.]\r\n", pe->m_pDosHead->e_lfarlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ovno：     [地址(RAW):0x0000001a] [长度:02h] [数据:0x%04X] [Overlay number.]\r\n", pe->m_pDosHead->e_ovno);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res[4]：   [地址(RAW):0x0000001c] [长度:08h] [数据:0x0000000000000000] [Reserved words.]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oemid：    [地址(RAW):0x00000024] [长度:02h] [数据:0x%04X] [OEM identifier(for e_oeminfo).]\r\n", pe->m_pDosHead->e_oemid);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oeminfo：  [地址(RAW):0x00000026] [长度:02h] [数据:0x%04X] [OEM information; e_oemid specific.]\r\n", pe->m_pDosHead->e_oeminfo);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res2[10]： [地址(RAW):0x00000028] [长度:14h] [数据:0x0000000000000000000000000000000000000000] [Reserved words.] [长度为\"20\".]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfanew：   [地址(RAW):0x0000003c] [长度:04h] [数据:0x%08X] [偏移量:0x3C] [File address of new exe header.] [PE文件头地址.]\r\n", pe->m_pDosHead->e_lfanew);
	m_strPeStruct += strTmp;
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}

void CPEInfoDlg::ShowSectionHead(const CPE * pe, const byte * pBaseAdd)
{
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	CString strTmp;
	m_strPeStruct += L"IMAGE_SECTION_HEADER(块表 | 区段 | 节表)结构如下：\r\n";
	m_strPeStruct += L"------------------------------------------------------------\r\n";
	for (int i=0;i<pe->m_nSection;i++)
	{
		char szName[9] = {0};
		strcpy_s(szName, 8, (char*)pe->m_pSectionHead[i].Name);
		m_strPeStruct += L"[成员]                   [地址(RAW)]      [数据:RVA]      [说明]\r\n";
		strTmp.Format(L"Name：                   0x%08X        [%s]        [名称, 长度:8位(16字节)的ASCII码.]\r\n"
			,(byte*)&pe->m_pSectionHead[i].Name - pBaseAdd,CString(szName));
		m_strPeStruct += strTmp;
		strTmp.Format(L"VirtualSize：            0x%08X        0x%08X     [V(VS), 内存中大小(对齐前的长度).]\r\n"
			, (byte*)&pe->m_pSectionHead[i].Misc.VirtualSize - pBaseAdd, pe->m_pSectionHead[i].Misc.VirtualSize);
		m_strPeStruct += strTmp;
		strTmp.Format(L"VirtualAddress：         0x%08X        0x%08X     [V(VO), 内存中偏移(该块的RVA).]\r\n"
			, (byte*)&pe->m_pSectionHead[i].VirtualAddress - pBaseAdd, pe->m_pSectionHead[i].VirtualAddress);
		m_strPeStruct += strTmp;
		strTmp.Format(L"SizeOfRawData：          0x%08X        0x%08X     [R(RS), 文件中大小(对齐后的长度).]\r\n"
			, (byte*)&pe->m_pSectionHead[i].SizeOfRawData - pBaseAdd, pe->m_pSectionHead[i].SizeOfRawData);
		m_strPeStruct += strTmp;
		strTmp.Format(L"PointerToRawData：       0x%08X        0x%08X	  [R(RO), 文件中偏移.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].PointerToRawData - pBaseAdd, pe->m_pSectionHead[i].PointerToRawData);
		m_strPeStruct += strTmp;
		strTmp.Format(L"PointerToRelocations：   0x%08X        0x%08X	  [在OBJ文件中使用, 重定位的偏移.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].PointerToRelocations - pBaseAdd, pe->m_pSectionHead[i].PointerToRelocations);
		m_strPeStruct += strTmp;
		strTmp.Format(L"PointerToLinenumbers：   0x%08X        0x%08X	  [行号表的偏移, 提供调试.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].PointerToLinenumbers - pBaseAdd, pe->m_pSectionHead[i].PointerToLinenumbers);
		m_strPeStruct += strTmp;
		strTmp.Format(L"NumberOfRelocations：    0x%08X        0x%04X	  [在OBJ文件中使用, 重定位项数目.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].NumberOfRelocations - pBaseAdd, pe->m_pSectionHead[i].NumberOfRelocations);
		m_strPeStruct += strTmp;
		strTmp.Format(L"NumberOfLinenumbers：    0x%08X        0x%04X	  [行号表中行号的数目.]\r\n"
			, (byte*)&pe->m_pSectionHead[i].NumberOfLinenumbers - pBaseAdd, pe->m_pSectionHead[i].NumberOfLinenumbers);
		m_strPeStruct += strTmp;
		strTmp.Format(L"Characteristics：        0x%08X        0x%08X     [标志(块属性)]\r\n"
			, (byte*)&pe->m_pSectionHead[i].Characteristics - pBaseAdd, pe->m_pSectionHead[i].Characteristics);
		m_strPeStruct += strTmp;

		strTmp.Format(L"[地址(RAW)范围:0x%08X - 0x%08X]\r\n"
			, pe->m_pSectionHead[i].PointerToRawData, pe->m_pSectionHead[i].PointerToRawData + pe->m_pSectionHead[i].SizeOfRawData -1);
		m_strPeStruct += strTmp;

		m_strPeStruct += L"------------------------------------------------------------\r\n";
	}
	m_strPeStruct += L" 标志(属性块)       常用特征值对照表：\r\n";
	m_strPeStruct += L"[值:00000020h]  [IMAGE_SCN_CNT_CODE                // Section contains code.(包含可执行代码)]\r\n";
	m_strPeStruct += L"[值:00000040h]  [IMAGE_SCN_CNT_INITIALIZED_DATA    // Section contains initialized data.(该块包含已初始化的数据)]\r\n";
	m_strPeStruct += L"[值:00000080h]  [IMAGE_SCN_CNT_UNINITIALIZED_DATA  // Section contains uninitialized data.(该块包含未初始化的数据)]\r\n";
	m_strPeStruct += L"[值:00000200h]  [IMAGE_SCN_LNK_INFO                // Section contains comments or some other type of information.]\r\n";
	m_strPeStruct += L"[值:00000800h]  [IMAGE_SCN_LNK_REMOVE              // Section contents will not become part of image.]\r\n";
	m_strPeStruct += L"[值:00001000h]  [IMAGE_SCN_LNK_COMDAT              // Section contents comdat.]\r\n";
	m_strPeStruct += L"[值:00004000h]  [IMAGE_SCN_NO_DEFER_SPEC_EXC       // Reset speculative exceptions handling bits in the TLB entries for this section.]\r\n";
	m_strPeStruct += L"[值:00008000h]  [IMAGE_SCN_GPREL                   // Section content can be accessed relative to GP.]\r\n";
	m_strPeStruct += L"[值:00500000h]  [IMAGE_SCN_ALIGN_16BYTES           // Default alignment if no others are specified.]\r\n";
	m_strPeStruct += L"[值:01000000h]  [IMAGE_SCN_LNK_NRELOC_OVFL         // Section contains extended relocations.]\r\n";
	m_strPeStruct += L"[值:02000000h]  [IMAGE_SCN_MEM_DISCARDABLE         // Section can be discarded.]\r\n";
	m_strPeStruct += L"[值:04000000h]  [IMAGE_SCN_MEM_NOT_CACHED          // Section is not cachable.]\r\n";
	m_strPeStruct += L"[值:08000000h]  [IMAGE_SCN_MEM_NOT_PAGED           // Section is not pageable.]\r\n";
	m_strPeStruct += L"[值:10000000h]  [IMAGE_SCN_MEM_SHARED              // Section is shareable(该块为共享块).]\r\n";
	m_strPeStruct += L"[值:20000000h]  [IMAGE_SCN_MEM_EXECUTE             // Section is executable.(该块可执行)]\r\n";
	m_strPeStruct += L"[值:40000000h]  [IMAGE_SCN_MEM_READ                // Section is readable.(该块可读)]\r\n";
	m_strPeStruct += L"[值:80000000h]  [IMAGE_SCN_MEM_WRITE               // Section is writeable.(该块可写)]\r\n";
	m_strPeStruct += L"------------------------------------------------------------\r\n";

	m_strPeStruct += L"各种常见块(Sections) 的描述：\r\n";

	m_strPeStruct += L"[.text]  [指令代码.]\r\n";
	m_strPeStruct += L"[.data]  [初始化的数据.]\r\n";
	m_strPeStruct += L"[.idata] [导入表.]\r\n";
	m_strPeStruct += L"[.rsrc]  [资源数据.]\r\n";
	m_strPeStruct += L"[.reloc] [基地址重定位表.]\r\n";
	m_strPeStruct += L"[.edata] [输出表.]\r\n";
	m_strPeStruct += L"[.tls]   [thread local storage, 线程局部存储器.]\r\n";
	m_strPeStruct += L"[.rdata] [存放调试目录和说明字符串.]\r\n";

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n\r\n";
}