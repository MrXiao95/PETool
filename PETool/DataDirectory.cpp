// DataDirectory.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "DataDirectory.h"
#include "afxdialogex.h"
#include "Definition.h"

// CDataDirectory 对话框

IMPLEMENT_DYNAMIC(CDataDirectory, CDialogEx)

CDataDirectory::CDataDirectory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_DATADIRECTORY, pParent)
	, m_pDataDirectory(NULL)
	, m_strExportRva(_T(""))
	, m_strImportRva(_T(""))
	, m_strResRva(_T(""))
	, m_strExceptionRva(_T(""))
	, m_strSecurityRva(_T(""))
	, m_strBaseRelocRva(_T(""))
	, m_strDebugRva(_T(""))
	, m_strArchitectureRva(_T(""))
	, m_strGlobalPtrRva(_T(""))
	, m_strTlsRva(_T(""))
	, m_strConfigRva(_T(""))
	, m_strBoundImportRva(_T(""))
	, m_strIatRva(_T(""))
	, m_strDelayImportRva(_T(""))
	, m_strComRva(_T(""))
	, m_strReserverRva(_T(""))
	, m_strExportSize(_T(""))
	, m_strImportSize(_T(""))
	, m_strResSize(_T(""))
	, m_strExceptionSize(_T(""))
	, m_strSecuritySize(_T(""))
	, m_strBaseRelocSize(_T(""))
	, m_strDebugSize(_T(""))
	, m_strArchitectureSize(_T(""))
	, m_strGlobalPtrSize(_T(""))
	, m_strTlsSize(_T(""))
	, m_strConfigSize(_T(""))
	, m_strBoundImportSize(_T(""))
	, m_strIatSize(_T(""))
	, m_strDelayImportSize(_T(""))
	, m_strComSize(_T(""))
	, m_strReserverSize(_T(""))
{

}

CDataDirectory::~CDataDirectory()
{
}

void CDataDirectory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITEXPORTRVA, m_strExportRva);
	DDX_Text(pDX, IDC_EDITIMPORTRVA, m_strImportRva);
	DDX_Text(pDX, IDC_EDITRESRVA, m_strResRva);
	DDX_Text(pDX, IDC_EDITEXCEPTIONRVA, m_strExceptionRva);
	DDX_Text(pDX, IDC_EDITSECURITYRVA, m_strSecurityRva);
	DDX_Text(pDX, IDC_EDITBASERELOCRVA, m_strBaseRelocRva);
	DDX_Text(pDX, IDC_EDITDEBUGRVA, m_strDebugRva);
	DDX_Text(pDX, IDC_EDITARCHITECTURERVA, m_strArchitectureRva);
	DDX_Text(pDX, IDC_EDITGLOBALPTRRVA, m_strGlobalPtrRva);
	DDX_Text(pDX, IDC_EDITTLSRVA, m_strTlsRva);
	DDX_Text(pDX, IDC_EDITCONFIGRVA, m_strConfigRva);
	DDX_Text(pDX, IDC_EDITBOUNDIMPORTRVA, m_strBoundImportRva);
	DDX_Text(pDX, IDC_EDITIATRVA, m_strIatRva);
	DDX_Text(pDX, IDC_EDITDELAYIMPORTRVA, m_strDelayImportRva);
	DDX_Text(pDX, IDC_EDITCOMRVA, m_strComRva);
	DDX_Text(pDX, IDC_EDITRESERVERRVA, m_strReserverRva);

	DDX_Text(pDX, IDC_EDITEXPORTSIZE, m_strExportSize);
	DDX_Text(pDX, IDC_EDITIMPORTSIZE, m_strImportSize);
	DDX_Text(pDX, IDC_EDITRESSIZE, m_strResSize);
	DDX_Text(pDX, IDC_EDITEXCEPTIONSIZE, m_strExceptionSize);
	DDX_Text(pDX, IDC_EDITSECURITYSIZE, m_strSecuritySize);
	DDX_Text(pDX, IDC_EDITBASERELOCSIZE, m_strBaseRelocSize);
	DDX_Text(pDX, IDC_EDITDEBUGSIZE, m_strDebugSize);
	DDX_Text(pDX, IDC_EDITARCHITECTURESIZE, m_strArchitectureSize);
	DDX_Text(pDX, IDC_EDITGLOBALPTRSIZE, m_strGlobalPtrSize);
	DDX_Text(pDX, IDC_EDITTLSSIZE, m_strTlsSize);
	DDX_Text(pDX, IDC_EDITCONFIGSIZE, m_strConfigSize);
	DDX_Text(pDX, IDC_EDITBOUNDIMPORTSIZE, m_strBoundImportSize);
	DDX_Text(pDX, IDC_EDITIATSIZE, m_strIatSize);
	DDX_Text(pDX, IDC_EDITDELAYIMPORTSIZE, m_strDelayImportSize);
	DDX_Text(pDX, IDC_EDITCOMSIZE, m_strComSize);
	DDX_Text(pDX, IDC_EDITRESERVERSIZE, m_strReserverSize);
	DDX_Control(pDX, IDC_BTNEXPORT, m_btnExport);
}


BEGIN_MESSAGE_MAP(CDataDirectory, CDialogEx)
	ON_BN_CLICKED(IDC_BTNEXPORT, &CDataDirectory::OnBnClickedBtnexport)
	ON_BN_CLICKED(IDC_BTNRELOC, &CDataDirectory::OnBnClickedBtnreloc)
	ON_BN_CLICKED(IDC_BTNIMPORT, &CDataDirectory::OnBnClickedBtnimport)
END_MESSAGE_MAP()


// CDataDirectory 消息处理程序


BOOL CDataDirectory::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_pDataDirectory)
	{
		ShowDataDirectory();
		UpdateData(FALSE);
	}
	return FALSE;
}

void CDataDirectory::SetDataDirectory(IMAGE_DATA_DIRECTORY* pDataDirectory)
{
	m_pDataDirectory = pDataDirectory;
}

void CDataDirectory::ShowDataDirectory() 
{
	m_strExportRva.Format(L"%08x",m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	m_strExportSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
	m_btnExport.EnableWindow(m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	m_strImportRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	m_strImportSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);
	GetDlgItem(IDC_BTNIMPORT)->EnableWindow(m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	m_strResRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress);
	m_strResSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size);

	m_strExceptionRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress);
	m_strExceptionSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size);

	m_strSecurityRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress);
	m_strSecuritySize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size);

	m_strBaseRelocRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	m_strBaseRelocSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size);
	GetDlgItem(IDC_BTNRELOC)->EnableWindow(m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	m_strDebugRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress);
	m_strDebugSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size);

	m_strArchitectureRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].VirtualAddress);
	m_strArchitectureSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].Size);

	m_strGlobalPtrRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].VirtualAddress);
	m_strGlobalPtrSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].Size);

	m_strTlsRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
	m_strTlsSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size);

	m_strConfigRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress);
	m_strConfigSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size);

	m_strBoundImportRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress);
	m_strBoundImportSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size);

	m_strIatRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress);
	m_strIatSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size);

	m_strDelayImportRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress);
	m_strDelayImportSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size);

	m_strComRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress);
	m_strComSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size);

	m_strReserverRva.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR + 1].VirtualAddress);
	m_strReserverSize.Format(L"%08x", m_pDataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR + 1].Size);
}

void CDataDirectory::OnBnClickedBtnexport()
{
	CWnd *pWnd = FindWindow(NULL, MAINWINDOWTITLE);
	if (pWnd)
	{
		pWnd->PostMessage(WM_USER_SHOWEXPORTDIRCTORY);
	}
	else
	{
		GetParent()->PostMessage(WM_USER_SHOWEXPORTDIRCTORY);
	}
}

//显示重定位表
void CDataDirectory::OnBnClickedBtnreloc()
{
	CWnd *pWnd = FindWindow(NULL, MAINWINDOWTITLE);
	if (pWnd)
	{
		pWnd->PostMessage(WM_USER_SHOWBASERELOC);
	}
	else
	{
		GetParent()->PostMessage(WM_USER_SHOWBASERELOC);
	}
}


void CDataDirectory::OnBnClickedBtnimport()
{
	CWnd *pWnd = FindWindow(NULL, MAINWINDOWTITLE);
	if (pWnd)
	{
		pWnd->PostMessage(WM_USER_SHOWIMPORT);
	}
	else
	{
		GetParent()->PostMessage(WM_USER_SHOWIMPORT);
	}
}
