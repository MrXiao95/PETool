// DosHeaderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "DosHeaderDlg.h"
#include "afxdialogex.h"


// CDosHeaderDlg 对话框

IMPLEMENT_DYNAMIC(CDosHeaderDlg, CDialogEx)

CDosHeaderDlg::CDosHeaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_DOSHEAD, pParent)
	, m_strMagic(_T(""))
	, m_strCblp(_T(""))
	, m_strCp(_T(""))
	, m_strCrlc(_T(""))
	, m_strCparhdr(_T(""))
	, m_strMinalloc(_T(""))
	, m_strMaxalloc(_T(""))
	, m_strSs(_T(""))
	, m_strSp(_T(""))
	, m_strCsum(_T(""))
	, m_strIp(_T(""))
	, m_strCs(_T(""))
	, m_strLfarlc(_T(""))
	, m_strOvno(_T(""))
	, m_strRes(_T(""))
	, m_strOemid(_T(""))
	, m_strOeminfo(_T(""))
	, m_strRes2(_T(""))
	, m_strLfanew(_T(""))
	, m_pDosHead(NULL)
{

}

CDosHeaderDlg::~CDosHeaderDlg()
{
}

void CDosHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITMAGIC, m_strMagic);
	DDX_Text(pDX, IDC_EDITCBLP, m_strCblp);
	DDX_Text(pDX, IDC_EDITCP, m_strCp);
	DDX_Text(pDX, IDC_EDITCRLC, m_strCparhdr);
	DDX_Text(pDX, IDC_EDITCPARHDR, m_strCparhdr);
	DDX_Text(pDX, IDC_EDITMINALLOC, m_strMinalloc);
	DDX_Text(pDX, IDC_EDITMAXALLOC, m_strMaxalloc);
	DDX_Text(pDX, IDC_EDITSS, m_strSs);
	DDX_Text(pDX, IDC_EDITSP, m_strSp);
	DDX_Text(pDX, IDC_EDITCSUM, m_strCsum);
	DDX_Text(pDX, IDC_EDITIP, m_strIp);
	DDX_Text(pDX, IDC_EDITCS, m_strCs);
	DDX_Text(pDX, IDC_EDITLFARLC, m_strLfarlc);
	DDX_Text(pDX, IDC_EDITOVNO, m_strOvno);
	DDX_Text(pDX, IDC_EDITRES, m_strRes);
	DDX_Text(pDX, IDC_EDITOEMID, m_strOemid);
	DDX_Text(pDX, IDC_EDITOEMINFO, m_strOeminfo);
	DDX_Text(pDX, IDC_EDITRES2, m_strRes2);
	DDX_Text(pDX, IDC_EDITLFANEW, m_strLfanew);
}


BEGIN_MESSAGE_MAP(CDosHeaderDlg, CDialogEx)
END_MESSAGE_MAP()


// CDosHeaderDlg 消息处理程序
void CDosHeaderDlg::SetDosHeder(IMAGE_DOS_HEADER* pDosHead)
{
	if (pDosHead != NULL)
	{
		m_pDosHead = pDosHead;
		ShowDosHead();
	}
}

void CDosHeaderDlg::ShowDosHead()
{
	m_strMagic.Format(L"%04x",m_pDosHead->e_magic);
	m_strCblp.Format(L"%04x", m_pDosHead->e_cblp);
	m_strCp.Format(L"%04x", m_pDosHead->e_cp);
	m_strCrlc.Format(L"%04x", m_pDosHead->e_crlc);
	m_strCparhdr.Format(L"%04x", m_pDosHead->e_cparhdr);
	m_strMinalloc.Format(L"%04x", m_pDosHead->e_minalloc);
	m_strMaxalloc.Format(L"%04x", m_pDosHead->e_maxalloc);
	m_strSs.Format(L"%04x", m_pDosHead->e_ss);
	m_strSp.Format(L"%04x", m_pDosHead->e_sp);
	m_strCsum.Format(L"%04x", m_pDosHead->e_csum);
	m_strIp.Format(L"%04x", m_pDosHead->e_ip);
	m_strCs.Format(L"%04x", m_pDosHead->e_cs);
	m_strLfarlc.Format(L"%04x", m_pDosHead->e_lfarlc);
	m_strOvno.Format(L"%04x", m_pDosHead->e_ovno);
	for (int i=0;i<4;i++)
	{
		CString strTmp;
		strTmp.Format(L"%04x",m_pDosHead->e_res[i]);
		m_strRes += strTmp;
	}
	m_strOemid.Format(L"%04x", m_pDosHead->e_oemid);
	m_strOeminfo.Format(L"%04x", m_pDosHead->e_oeminfo);
	for (int i = 0; i < 10; i++)
	{
		CString strTmp;
		strTmp.Format(L"%04x", m_pDosHead->e_res2[i]);
		m_strRes2 += strTmp;
	}
	m_strLfanew.Format(L"%08x", m_pDosHead->e_lfanew);//4
}