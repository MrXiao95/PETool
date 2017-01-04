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
}


BEGIN_MESSAGE_MAP(CHexDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHexDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHexDlg::OnBnClickedCancel)
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
