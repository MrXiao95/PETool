// ExportDirectoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "ExportDirectoryDlg.h"
#include "afxdialogex.h"
#define  LISTID 0
#define  LISTRVA 1
#define  LISTOFFSET 2
#define  LISTNAME 3

// CExportDirectoryDlg 对话框

IMPLEMENT_DYNAMIC(CExportDirectoryDlg, CDialogEx)

CExportDirectoryDlg::CExportDirectoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_EXPORTDIRECTORY, pParent)
{

}

CExportDirectoryDlg::~CExportDirectoryDlg()
{
}

void CExportDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTFUN, m_listFun);
	DDX_Text(pDX, IDC_EDITTIME, m_strTime);
	DDX_Text(pDX, IDC_EDITNAMERVA,m_strNameRav);
	DDX_Text(pDX, IDC_EDITID,m_strSatartID);
	DDX_Text(pDX, IDC_EDITFUNNUM,m_strFunCount);
	DDX_Text(pDX, IDC_EDITNAMENUM,m_strFunCountByName);
	DDX_Text(pDX, IDC_EDITFUNTABRVA,m_strFunTabRva);
	DDX_Text(pDX, IDC_EDITNAMETABRVA,m_strNameTabRva);
	DDX_Text(pDX, IDC_EDITIDTABRAV, m_strIDTabRva);
	DDX_Text(pDX, IDC_STATICDLLNAME, m_strDLLName);
}


BEGIN_MESSAGE_MAP(CExportDirectoryDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CExportDirectoryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CExportDirectoryDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CExportDirectoryDlg 消息处理程序


void CExportDirectoryDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CExportDirectoryDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CExportDirectoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DWORD dwStyle = m_listFun.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listFun.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listFun.InsertColumn(LISTID, L"序号", LVCFMT_LEFT, 80);
	m_listFun.InsertColumn(LISTRVA, L"RVA", LVCFMT_LEFT, 120);
	m_listFun.InsertColumn(LISTOFFSET, L"偏移", LVCFMT_LEFT, 120);
	m_listFun.InsertColumn(LISTNAME, L"函数名", LVCFMT_LEFT, 140);

	if (m_exportDirectory.size() > 0)
	{
		ShowExportDirectory();
	}
	
	return TRUE; 
}

void CExportDirectoryDlg::SetExportDirectory(CPE *pe)
{
	vector<EXPORTDIRECTORY>().swap(m_exportDirectory);
	DWORD dwFoa = 0;
	if (pe->m_pOptionalHeader32)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader32->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	}
	else if (pe->m_pOptionalHeader64)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader64->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	}
	else
	{
		return;
	}
	IMAGE_EXPORT_DIRECTORY exportDirctory;
	memcpy(&exportDirctory, (byte*)pe->m_pFileMem+dwFoa, sizeof(IMAGE_EXPORT_DIRECTORY));
	DWORD dwNameFoa = pe->RvaToFoa(exportDirctory.AddressOfNames);
	DWORD dwAddressOfNameOrdinals = pe->RvaToFoa(exportDirctory.AddressOfNameOrdinals);
	DWORD *pFunctions = (DWORD*)((char*)pe->m_pFileMem + pe->RvaToFoa(exportDirctory.AddressOfFunctions));
	EXPORTDIRECTORY tmp;
	for (int i=0;i<exportDirctory.NumberOfNames;i++)
	{
		DWORD dwTmp = pe->RvaToFoa(*(DWORD*)((char*)pe->m_pFileMem + dwNameFoa));
		tmp.strName = (char*)pe->m_pFileMem + dwTmp;
		tmp.nID = *(WORD*)((char*)pe->m_pFileMem + dwAddressOfNameOrdinals) + exportDirctory.Base;
		tmp.dwRVA = pFunctions[i];
		tmp.dwOffset = pe->RvaToFoa(pFunctions[i]);
		m_exportDirectory.push_back(tmp);
		dwNameFoa += 4;
		dwAddressOfNameOrdinals += 2;
	}

	time_t timeDateStamp = exportDirctory.TimeDateStamp;
	tm tmBegin;
	localtime_s(&tmBegin, &timeDateStamp);

	m_strTime.Format(L"%04d.%02d.%02d     %02d:%02d:%02d\r\n"
		, tmBegin.tm_year + 1900, tmBegin.tm_mon + 1, tmBegin.tm_mday
		, tmBegin.tm_hour, tmBegin.tm_min, tmBegin.tm_sec);

	m_strNameRav.Format(L"%08X",exportDirctory.Name);
	m_strSatartID.Format(L"%d",exportDirctory.Base);
	m_strFunCount.Format(L"%d",exportDirctory.NumberOfFunctions);
	m_strFunCountByName.Format(L"%d",exportDirctory.NumberOfNames);
	m_strFunTabRva.Format(L"%08X",exportDirctory.AddressOfFunctions);
	m_strNameTabRva.Format(L"%08X",exportDirctory.AddressOfNames);
	m_strIDTabRva.Format(L"%08X",exportDirctory.AddressOfNameOrdinals);
	char *szDllName = pe->RvaToFoa(exportDirctory.Name) + (char*)pe->m_pFileMem;
	m_strDLLName.Format(L"%s", CString(szDllName));
}

void CExportDirectoryDlg::ShowExportDirectory()
{
	for (int i = m_exportDirectory.size() - 1; i >= 0; i--)
	{
		CString strTemp;
		strTemp.Format(L"%d", m_exportDirectory[i].nID);
		int nRow = m_listFun.InsertItem(LISTID, strTemp);
		strTemp.Format(L"%08X", m_exportDirectory[i].dwRVA);
		m_listFun.SetItemText(nRow, LISTRVA, strTemp);
		
		strTemp.Format(L"%08X", m_exportDirectory[i].dwOffset);
		m_listFun.SetItemText(nRow, LISTOFFSET, strTemp);

		m_listFun.SetItemText(nRow, LISTNAME, m_exportDirectory[i].strName);
	}
}