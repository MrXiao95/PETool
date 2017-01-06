// SectionHeadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "SectionHeadDlg.h"
#include "afxdialogex.h"

#define LISTNAME 0 //L"名称"
#define LISTVA   1 //"内存中的偏移"
#define LISTVSIZE 2 //"内存中的大小"
#define LISTRAW  3 //"文件中的偏移"
#define LISTFSIZE 4 //"文件中的大小"
#define LISTFLAG 5 //"标志"

// CSectionHeadDlg 对话框

IMPLEMENT_DYNAMIC(CSectionHeadDlg, CDialogEx)

CSectionHeadDlg::CSectionHeadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SECTIONHEAD, pParent)
	, m_pSectionHead(NULL)
	, m_nSection(0)
	, m_strNumber(_T("数目：0"))
{

}

CSectionHeadDlg::~CSectionHeadDlg()
{
}

void CSectionHeadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSECTION, m_listSection);
	DDX_Text(pDX, IDC_STATICNUMBER, m_strNumber);
}


BEGIN_MESSAGE_MAP(CSectionHeadDlg, CDialogEx)
END_MESSAGE_MAP()


// CSectionHeadDlg 消息处理程序
void CSectionHeadDlg::SetSetcionHead(IMAGE_SECTION_HEADER *pSectionHead,int nSection)
{
	if (pSectionHead)
	{
		m_nSection = nSection;
		m_pSectionHead = pSectionHead;
	}
}

void CSectionHeadDlg::ShowSectionHead()
{
	m_strNumber.Format(L"数目：%d",m_nSection);
	for (int i = m_nSection - 1; i >= 0; i--) 
	{
		int nRow = m_listSection.InsertItem(LISTNAME, CString(m_pSectionHead[i].Name));
		CString strTemp;
		strTemp.Format(L"%08X", m_pSectionHead[i].VirtualAddress);
		m_listSection.SetItemText(nRow, LISTVA, strTemp);
		strTemp.Format(L"%08X", m_pSectionHead[i].Misc.VirtualSize);
		
		m_listSection.SetItemText(nRow, LISTVSIZE, strTemp);
		strTemp.Format(L"%08X", m_pSectionHead[i].PointerToRawData);
		
		m_listSection.SetItemText(nRow, LISTRAW, strTemp);
		strTemp.Format(L"%08X", m_pSectionHead[i].SizeOfRawData);
		
		m_listSection.SetItemText(nRow, LISTFSIZE, strTemp);
		strTemp.Format(L"%08X", m_pSectionHead[i].Characteristics);
		m_listSection.SetItemText(nRow, LISTFLAG, strTemp);
	}
}

BOOL CSectionHeadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwStyle = m_listSection.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listSection.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listSection.InsertColumn(LISTNAME, L"名称", LVCFMT_LEFT, 80);
	m_listSection.InsertColumn(LISTVA, L"内存中的偏移", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTVSIZE, L"内存中的大小", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTRAW, L"文件中的偏移", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTFSIZE, L"文件中的大小", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTFLAG, L"标志", LVCFMT_LEFT, 70);
	if (m_pSectionHead)
	{
		ShowSectionHead();
		UpdateData(FALSE);
	}
	return FALSE; 
}
