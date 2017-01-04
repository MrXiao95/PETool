// PEFileInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "PEInfoDlg.h"
#include "afxdialogex.h"


// CPEFileInfo 对话框

IMPLEMENT_DYNAMIC(CPEInfoDlg, CDialogEx)

CPEInfoDlg::CPEInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_PEINFO, pParent)
{

}

CPEInfoDlg::~CPEInfoDlg()
{
}

void CPEInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPEInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPEInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPEInfoDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPEFileInfo 消息处理程序


void CPEInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CPEInfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}
