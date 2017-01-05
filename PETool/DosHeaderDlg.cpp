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
{

}

CDosHeaderDlg::~CDosHeaderDlg()
{
}

void CDosHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITMAGIC, m_strMagic);
}


BEGIN_MESSAGE_MAP(CDosHeaderDlg, CDialogEx)
END_MESSAGE_MAP()


// CDosHeaderDlg 消息处理程序
