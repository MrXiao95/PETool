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
	: CDialogEx(IDD_EXPORTDIRECTORY_DLG, pParent)
{

}

CExportDirectoryDlg::~CExportDirectoryDlg()
{
}

void CExportDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTFUN, m_listFun);
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