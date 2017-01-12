// OptionalHead.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "OptionalHead.h"
#include "afxdialogex.h"


// COptionalHead 对话框

IMPLEMENT_DYNAMIC(COptionalHead, CDialogEx)

COptionalHead::COptionalHead(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_OPTFILEHEAD, pParent)
	, pOptionalHeader32(NULL)
	, pOptionalHeader64(NULL)
	, m_strMagic(_T(""))
	, m_strMajorLinkerVersion(_T(""))
	, m_strMinorLinkerVersion(_T(""))
	, m_strSizeOfCode(_T(""))
	, m_strSizeOfInitData(_T(""))
	, m_strSizeOfUninitData(_T(""))
	, m_strEntryPoint(_T(""))
	, m_strBaseOfCode(_T(""))
	, m_strBaseOfData(_T(""))
	, m_strImageBase(_T(""))
	, m_strSectionAlignment(_T(""))
	, m_strFileAlignment(_T(""))
	, m_strMajorOSVersion(_T(""))
	, m_strMinorOSVersion(_T(""))
	, m_strMajorImageVersion(_T(""))
	, m_strMinorImageVersion(_T(""))
	, m_strMajorSubsystemVersion(_T(""))
	, m_strMinorSubsystemVersion(_T(""))
	, m_strWin32VersionValue(_T(""))
	, m_strSizeOfImage(_T(""))
	, m_strSizeOfHeaders(_T(""))
	, m_strCheckSum(_T(""))
	, m_strSubsystem(_T(""))
	, m_strDllCharacteristics(_T(""))
	, m_strSizeOfStackReserve(_T(""))
	, m_strSizeOfStackCommit(_T(""))
	, m_strSizeOfHeapReserve(_T(""))
	, m_strSizeOfHeapCommit(_T(""))
	, m_strLoaderFlags(_T(""))
	, m_strNumberOfRvaAndSizes(_T(""))
{

}

COptionalHead::~COptionalHead()
{
}

void COptionalHead::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITMAGIC, m_strMagic);
	DDX_Text(pDX, IDC_EDITMAJORLINKER, m_strMajorLinkerVersion);
	DDX_Text(pDX, IDC_EDITMINORLINKER, m_strMinorLinkerVersion);
	DDX_Text(pDX, IDC_EDITSIZEOFCODE, m_strSizeOfCode);
	DDX_Text(pDX, IDC_EDITSIZEOFINITDATA, m_strSizeOfInitData);
	DDX_Text(pDX, IDC_EDITSIZEUNINIT, m_strSizeOfUninitData);
	DDX_Text(pDX, IDC_EDITENTRYPOINT, m_strEntryPoint);
	DDX_Text(pDX, IDC_EDITBASECODE, m_strBaseOfCode);
	DDX_Text(pDX, IDC_EDITBASEDATA, m_strBaseOfData);
	DDX_Text(pDX, IDC_EDITIMAGEBASE, m_strImageBase);
	DDX_Text(pDX, IDC_EDITSECTIONALIGNMENT, m_strSectionAlignment);
	DDX_Text(pDX, IDC_EDITFILEALIGNMENT, m_strFileAlignment);
	DDX_Text(pDX, IDC_EDITMAJOROS, m_strMajorOSVersion);
	DDX_Text(pDX, IDC_EDITMINOROS, m_strMinorOSVersion);
	DDX_Text(pDX, IDC_EDITMAORIMAGE, m_strMajorImageVersion);
	DDX_Text(pDX, IDC_EDITMINORIMAGE, m_strMinorImageVersion);
	DDX_Text(pDX, IDC_EDITMAJORSUBSYSTEM, m_strMajorSubsystemVersion);
	DDX_Text(pDX, IDC_EDITMINORSUBSYSTEM, m_strMinorSubsystemVersion);
	DDX_Text(pDX, IDC_EDITWIN32VERSION, m_strWin32VersionValue);
	DDX_Text(pDX, IDC_EDITSIZEOFIMAGE, m_strSizeOfImage);
	DDX_Text(pDX, IDC_EDITSIZEOFHEADERS, m_strSizeOfHeaders);
	DDX_Text(pDX, IDC_EDITCHECKSUM, m_strCheckSum);
	DDX_Text(pDX, IDC_EDITSUBSYSTEM, m_strSubsystem);
	DDX_Text(pDX, IDC_EDITDLLCHARACTERISTICS, m_strDllCharacteristics);
	DDX_Text(pDX, IDC_EDITSIZEOFSTACKRESERVER, m_strSizeOfStackReserve);
	DDX_Text(pDX, IDC_EDITSIZEOFSTACKCOMMIT, m_strSizeOfStackCommit);
	DDX_Text(pDX, IDC_EDITSIZEOFHEAPRESERVER, m_strSizeOfHeapReserve);
	DDX_Text(pDX, IDC_EDITSIZEOFHEAPCOMMIT, m_strSizeOfHeapCommit);
	DDX_Text(pDX, IDC_EDITLOADERFLAGS, m_strLoaderFlags);
	DDX_Text(pDX, IDC_EDITNUMBEROFRVAANDSIZES, m_strNumberOfRvaAndSizes);
}


BEGIN_MESSAGE_MAP(COptionalHead, CDialogEx)
	ON_BN_CLICKED(IDOK, &COptionalHead::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COptionalHead::OnBnClickedCancel)
END_MESSAGE_MAP()


void COptionalHead::SetOptionalHead32(IMAGE_OPTIONAL_HEADER32 *pOptionalHeader32)
{
	m_strMagic.Format(L"%04X",pOptionalHeader32->Magic);
	m_strMajorLinkerVersion.Format(L"%02X", pOptionalHeader32->MajorLinkerVersion);
	m_strMinorLinkerVersion.Format(L"%02X", pOptionalHeader32->MinorLinkerVersion);
	m_strSizeOfCode.Format(L"%08X", pOptionalHeader32->SizeOfCode);
	m_strSizeOfInitData.Format(L"%08X", pOptionalHeader32->SizeOfInitializedData);
	m_strSizeOfUninitData.Format(L"%08X", pOptionalHeader32->SizeOfUninitializedData);
	m_strEntryPoint.Format(L"%08X", pOptionalHeader32->AddressOfEntryPoint);
	m_strBaseOfCode.Format(L"%08X", pOptionalHeader32->BaseOfCode);
	m_strBaseOfData.Format(L"%08X", pOptionalHeader32->BaseOfData);
	m_strImageBase.Format(L"%08X", pOptionalHeader32->ImageBase);
	m_strSectionAlignment.Format(L"%08X", pOptionalHeader32->SectionAlignment);
	m_strFileAlignment.Format(L"%08X", pOptionalHeader32->FileAlignment);
	m_strMajorOSVersion.Format(L"%04X", pOptionalHeader32->MajorOperatingSystemVersion);
	m_strMinorOSVersion.Format(L"%04X", pOptionalHeader32->MinorOperatingSystemVersion);
	m_strMajorImageVersion.Format(L"%04X", pOptionalHeader32->MajorImageVersion);
	m_strMinorImageVersion.Format(L"%04X", pOptionalHeader32->MinorImageVersion);
	m_strMajorSubsystemVersion.Format(L"%04X", pOptionalHeader32->MajorSubsystemVersion);
	m_strMinorSubsystemVersion.Format(L"%04X", pOptionalHeader32->MinorSubsystemVersion);
	m_strWin32VersionValue.Format(L"%08X", pOptionalHeader32->Win32VersionValue);
	m_strSizeOfImage.Format(L"%08X", pOptionalHeader32->SizeOfImage);
	m_strSizeOfHeaders.Format(L"%08X", pOptionalHeader32->SizeOfHeaders);
	m_strCheckSum.Format(L"%08X", pOptionalHeader32->CheckSum);
	m_strSubsystem.Format(L"%04X", pOptionalHeader32->Subsystem);
	m_strDllCharacteristics.Format(L"%04X", pOptionalHeader32->DllCharacteristics);
	m_strSizeOfStackReserve.Format(L"%08X", pOptionalHeader32->SizeOfStackReserve);
	m_strSizeOfStackCommit.Format(L"%08X", pOptionalHeader32->SizeOfStackCommit);
	m_strSizeOfHeapReserve.Format(L"%08X", pOptionalHeader32->SizeOfHeapReserve);
	m_strSizeOfHeapCommit.Format(L"%08X", pOptionalHeader32->SizeOfHeapCommit);
	m_strLoaderFlags.Format(L"%08X", pOptionalHeader32->LoaderFlags);
	m_strNumberOfRvaAndSizes.Format(L"%08X", pOptionalHeader32->NumberOfRvaAndSizes);
}

void COptionalHead::SetOptionalHead64(IMAGE_OPTIONAL_HEADER64 *pOptionalHeader64)
{
	m_strMagic.Format(L"%04X", pOptionalHeader64->Magic);
	m_strMajorLinkerVersion.Format(L"%02X", pOptionalHeader64->MajorLinkerVersion);
	m_strMinorLinkerVersion.Format(L"%02X", pOptionalHeader64->MinorLinkerVersion);
	m_strSizeOfCode.Format(L"%08X", pOptionalHeader64->SizeOfCode);
	m_strSizeOfInitData.Format(L"%08X", pOptionalHeader64->SizeOfInitializedData);
	m_strSizeOfUninitData.Format(L"%08X", pOptionalHeader64->SizeOfUninitializedData);
	m_strEntryPoint.Format(L"%08X", pOptionalHeader64->AddressOfEntryPoint);
	m_strBaseOfCode.Format(L"%08X", pOptionalHeader64->BaseOfCode);
	m_strBaseOfData.Format(L"00000000");
	m_strImageBase.Format(L"%08X", pOptionalHeader64->ImageBase);
	m_strSectionAlignment.Format(L"%08X", pOptionalHeader64->SectionAlignment);
	m_strFileAlignment.Format(L"%08X", pOptionalHeader64->FileAlignment);
	m_strMajorOSVersion.Format(L"%04X", pOptionalHeader64->MajorOperatingSystemVersion);
	m_strMinorOSVersion.Format(L"%04X", pOptionalHeader64->MinorOperatingSystemVersion);
	m_strMajorImageVersion.Format(L"%04X", pOptionalHeader64->MajorImageVersion);
	m_strMinorImageVersion.Format(L"%04X", pOptionalHeader64->MinorImageVersion);
	m_strMajorSubsystemVersion.Format(L"%04X", pOptionalHeader64->MajorSubsystemVersion);
	m_strMinorSubsystemVersion.Format(L"%04X", pOptionalHeader64->MinorSubsystemVersion);
	m_strWin32VersionValue.Format(L"%08X", pOptionalHeader64->Win32VersionValue);
	m_strSizeOfImage.Format(L"%08X", pOptionalHeader64->SizeOfImage);
	m_strSizeOfHeaders.Format(L"%08X", pOptionalHeader64->SizeOfHeaders);
	m_strCheckSum.Format(L"%08X", pOptionalHeader64->CheckSum);
	m_strSubsystem.Format(L"%04X", pOptionalHeader64->Subsystem);
	m_strDllCharacteristics.Format(L"%04X", pOptionalHeader64->DllCharacteristics);
	m_strSizeOfStackReserve.Format(L"%08X", pOptionalHeader64->SizeOfStackReserve);
	m_strSizeOfStackCommit.Format(L"%08X", pOptionalHeader64->SizeOfStackCommit);
	m_strSizeOfHeapReserve.Format(L"%08X", pOptionalHeader64->SizeOfHeapReserve);
	m_strSizeOfHeapCommit.Format(L"%08X", pOptionalHeader64->SizeOfHeapCommit);
	m_strLoaderFlags.Format(L"%08X", pOptionalHeader64->LoaderFlags);
	m_strNumberOfRvaAndSizes.Format(L"%08X", pOptionalHeader64->NumberOfRvaAndSizes);
}


void COptionalHead::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void COptionalHead::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
