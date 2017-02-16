// BoundImportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "BoundImportDlg.h"
#include "afxdialogex.h"


// CBoundImportDlg 对话框

IMPLEMENT_DYNAMIC(CBoundImportDlg, CDialogEx)

CBoundImportDlg::CBoundImportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_BOUNDIMPORTDESCRIPTOR, pParent)
{

}

CBoundImportDlg::~CBoundImportDlg()
{
}

void CBoundImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTDLL, m_listDll);
	DDX_Control(pDX, IDC_LISTDLLREF, m_listDllRef);
}


BEGIN_MESSAGE_MAP(CBoundImportDlg, CDialogEx)
END_MESSAGE_MAP()


// CBoundImportDlg 消息处理程序
void CBoundImportDlg::SetBoundImport(CPE *pe)
{
	m_pe = pe;
	vector<IMAGEBOUNDIMPORT>().swap(m_vecBoundImport);
	DWORD dwFoa = 0;
	if (pe->m_pOptionalHeader32)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader32->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress);
	}
	else if (pe->m_pOptionalHeader64)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress);
	}
	else
	{
		return;
	}
	IMAGE_BOUND_IMPORT_DESCRIPTOR *pBoundImport = (IMAGE_BOUND_IMPORT_DESCRIPTOR*)((byte*)m_pe->m_pFileMem + dwFoa);
	while (true)
	{
		if (pBoundImport->NumberOfModuleForwarderRefs == 0
			&& pBoundImport->OffsetModuleName == 0
			&& pBoundImport->TimeDateStamp == 0)
		{
			break;
		}
		IMAGEBOUNDIMPORT imageBoundImport;
		imageBoundImport.NumberOfModuleForwarderRefs = pBoundImport->NumberOfModuleForwarderRefs;
		imageBoundImport.TimeDateStamp = pBoundImport->TimeDateStamp;
		char *szName = (char*)m_pe->m_pFileMem + dwFoa + pBoundImport->OffsetModuleName;
		imageBoundImport.OffsetModuleName = CString(szName);
		m_vecBoundImport.push_back(imageBoundImport);
		for (int i = 0; i < pBoundImport->NumberOfModuleForwarderRefs; i++) 
		{
			pBoundImport++;

			IMAGE_BOUND_FORWARDER_REF *pBoundForwarderRef = (IMAGE_BOUND_FORWARDER_REF*)pBoundImport;
		}
		pBoundImport++;
	}
}


BOOL CBoundImportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwStyle = m_listDll.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listDll.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listDll.InsertColumn(0, L"DLL Name", LVCFMT_LEFT, 120);
	m_listDll.InsertColumn(1, L"Time Date Stamp", LVCFMT_LEFT, 100);
	m_listDll.InsertColumn(2, L"绑定时间", LVCFMT_LEFT, 130);
	m_listDll.InsertColumn(3, L"依赖模块数", LVCFMT_LEFT, 80);

	m_listDllRef.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listDllRef.InsertColumn(0, L"DLL Name", LVCFMT_LEFT, 120);
	m_listDllRef.InsertColumn(1, L"Time Date Stamp", LVCFMT_LEFT, 100);
	m_listDllRef.InsertColumn(2, L"绑定时间", LVCFMT_LEFT, 130);
	m_listDllRef.InsertColumn(3, L"依赖模块数", LVCFMT_LEFT, 80);
	
	for (size_t i = 0; i < m_vecBoundImport.size(); i++)
	{
		CString strTmp;
		m_listDll.InsertItem(i,m_vecBoundImport[i].OffsetModuleName);
		strTmp.Format(L"%X",m_vecBoundImport[i].TimeDateStamp);
		m_listDll.SetItemText(i, 1, strTmp);

		time_t timeDateStamp = m_vecBoundImport[i].TimeDateStamp;
		tm tmBegin;
		localtime_s(&tmBegin, &timeDateStamp);
		strTmp.Format(L"%04d.%02d.%02d     %02d:%02d:%02d\r\n"
			, tmBegin.tm_year + 1900, tmBegin.tm_mon + 1, tmBegin.tm_mday
			, tmBegin.tm_hour, tmBegin.tm_min, tmBegin.tm_sec);
		m_listDll.SetItemText(i, 2, strTmp);

		strTmp.Format(L"%Xh  %d", m_vecBoundImport[i].NumberOfModuleForwarderRefs, m_vecBoundImport[i].NumberOfModuleForwarderRefs);
		m_listDll.SetItemText(i, 3, strTmp);
	}
	return TRUE;  
}
