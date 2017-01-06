// SectionHeadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "SectionHeadDlg.h"
#include "afxdialogex.h"

#define LISTNAME 0 //L"����"
#define LISTVA   1 //"�ڴ��е�ƫ��"
#define LISTVSIZE 2 //"�ڴ��еĴ�С"
#define LISTRAW  3 //"�ļ��е�ƫ��"
#define LISTFSIZE 4 //"�ļ��еĴ�С"
#define LISTFLAG 5 //"��־"

// CSectionHeadDlg �Ի���

IMPLEMENT_DYNAMIC(CSectionHeadDlg, CDialogEx)

CSectionHeadDlg::CSectionHeadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SECTIONHEAD, pParent)
	, m_pSectionHead(NULL)
	, m_nSection(0)
	, m_strNumber(_T("��Ŀ��0"))
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


// CSectionHeadDlg ��Ϣ�������
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
	m_strNumber.Format(L"��Ŀ��%d",m_nSection);
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
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listSection.SetExtendedStyle(dwStyle); //������չ���

	m_listSection.InsertColumn(LISTNAME, L"����", LVCFMT_LEFT, 80);
	m_listSection.InsertColumn(LISTVA, L"�ڴ��е�ƫ��", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTVSIZE, L"�ڴ��еĴ�С", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTRAW, L"�ļ��е�ƫ��", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTFSIZE, L"�ļ��еĴ�С", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(LISTFLAG, L"��־", LVCFMT_LEFT, 70);
	if (m_pSectionHead)
	{
		ShowSectionHead();
		UpdateData(FALSE);
	}
	return FALSE; 
}
