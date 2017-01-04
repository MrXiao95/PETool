// HexDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "HexDlg.h"
#include "afxdialogex.h"


// CHexDlg 对话框

IMPLEMENT_DYNAMIC(CHexDlg, CDialogEx)

CHexDlg::CHexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_HEX, pParent)
{

}

CHexDlg::~CHexDlg()
{
}

void CHexDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_editHex);
}


BEGIN_MESSAGE_MAP(CHexDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHexDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHexDlg::OnBnClickedCancel)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CHexDlg 消息处理程序


void CHexDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CHexDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void CHexDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

   if (m_editHex.m_hWnd)
   {
       CRect rt;
       GetClientRect(rt);
       m_editHex.MoveWindow(rt);
   }
}


BOOL CHexDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_editHex.SetOptions(TRUE, TRUE, TRUE, TRUE);
    m_editHex.SetBPR(16);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CHexDlg::SetHexData(byte* p, int len)
{
    m_editHex.SetData(p, len);
}