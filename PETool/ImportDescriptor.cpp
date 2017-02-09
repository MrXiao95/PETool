// ImportDescriptor.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "ImportDescriptor.h"
#include "afxdialogex.h"


// CImportDescriptor 对话框

IMPLEMENT_DYNAMIC(CImportDescriptor, CDialogEx)

CImportDescriptor::CImportDescriptor(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_IMPORTDESCRIPTOR, pParent)
{

}

CImportDescriptor::~CImportDescriptor()
{
}

void CImportDescriptor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTDLL, m_listDll);
	DDX_Control(pDX, IDC_LISTFUN, m_listFun);
}


BEGIN_MESSAGE_MAP(CImportDescriptor, CDialogEx)
	ON_BN_CLICKED(IDOK, &CImportDescriptor::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LISTDLL, &CImportDescriptor::OnNMClickListdll)
END_MESSAGE_MAP()


// CImportDescriptor 消息处理程序


void CImportDescriptor::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

void CImportDescriptor::SetImportDescriptor(CPE* pe)
{
	m_pe = pe;
	vector<IMAGE_IMPORT_DESCRIPTOR>().swap(m_importDescriptor);

	DWORD dwFoa = 0;
	if (pe->m_pOptionalHeader32)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader32->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	}
	else if (pe->m_pOptionalHeader64)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	}
	else
	{
		return;
	}

	IMAGE_IMPORT_DESCRIPTOR importDescriptor;
	while (true)
	{
		memcpy(&importDescriptor, (byte*)pe->m_pFileMem + dwFoa + ((m_importDescriptor.size()) * sizeof(IMAGE_IMPORT_DESCRIPTOR)), sizeof(IMAGE_IMPORT_DESCRIPTOR));
		if (importDescriptor.OriginalFirstThunk == 0)
		{
			break;
		}
		m_importDescriptor.push_back(importDescriptor);
	}
}

BOOL CImportDescriptor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwStyle = m_listDll.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listDll.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listDll.InsertColumn(0, L"DLL Name", LVCFMT_LEFT, 160);
	m_listDll.InsertColumn(1, L"Original First Thunk", LVCFMT_LEFT, 120);
	m_listDll.InsertColumn(2, L"Name(RVA)", LVCFMT_LEFT, 120);
	m_listDll.InsertColumn(3, L"FirstThunk", LVCFMT_LEFT, 120);

	m_listFun.SetExtendedStyle(dwStyle);
	m_listFun.InsertColumn(0, L"Thunk Rav", LVCFMT_LEFT, 80);
	m_listFun.InsertColumn(1, L"Thunk Offset", LVCFMT_LEFT, 80);
	m_listFun.InsertColumn(2, L"Thunk Value", LVCFMT_LEFT, 80);
	m_listFun.InsertColumn(3, L"Hint", LVCFMT_LEFT, 80);
	m_listFun.InsertColumn(4, L"API Name", LVCFMT_LEFT, 200);

	for (int i = 0; i < m_importDescriptor.size(); i++)
	{
		CString strTmp;
		DWORD dwFoa = m_pe->RvaToFoa(m_importDescriptor[i].Name);
		char *szName = (char*)m_pe->m_pFileMem + dwFoa;
		strTmp.Format(L"%s",CString(szName));
		m_listDll.InsertItem(i, strTmp);
		strTmp.Format(L"%08X", m_importDescriptor[i].OriginalFirstThunk);
		m_listDll.SetItemText(i, 1, strTmp);
		strTmp.Format(L"%08X", m_importDescriptor[i].Name);
		m_listDll.SetItemText(i, 2, strTmp);
		strTmp.Format(L"%08X", m_importDescriptor[i].FirstThunk);
		m_listDll.SetItemText(i, 3, strTmp);
	}
	return TRUE;  
}


void CImportDescriptor::OnNMClickListdll(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nIndex = m_listDll.GetSelectionMark();
	if (nIndex >= 0 && nIndex < m_importDescriptor.size())
	{
		m_listFun.DeleteAllItems();
		DWORD dwThunk = m_importDescriptor[nIndex].OriginalFirstThunk;
		
		int i = 0;
		while (true)
		{
			DWORD dwThunkValue = *(DWORD*)((char*)m_pe->m_pFileMem + m_pe->RvaToFoa(dwThunk));
			if (dwThunkValue == 0)
			{
				break;
			}
			CString strTmp;
			strTmp.Format(L"%08X", dwThunk);
			m_listFun.InsertItem(i, strTmp);
			strTmp.Format(L"%08X", m_pe->FoaToRva(dwThunk));
			m_listFun.SetItemText(i, 1, strTmp);
			strTmp.Format(L"%08X", dwThunkValue);
			m_listFun.SetItemText(i, 2, strTmp);
			WORD wHint = *(WORD*)((char*)m_pe->m_pFileMem + m_pe->RvaToFoa(dwThunkValue));
			strTmp.Format(L"%04X", wHint);
			m_listFun.SetItemText(i, 3, strTmp);
			char *szName = (char*)m_pe->m_pFileMem + m_pe->RvaToFoa(dwThunkValue+2);
			strTmp.Format(L"%s", CString(szName));
			m_listFun.SetItemText(i, 4, strTmp);
			dwThunk += 4;
			i++;
		}
	}
	*pResult = 0;
}
