// FileInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "FileInfoDlg.h"
#include "afxdialogex.h"


// CFileInfoDlg 对话框

IMPLEMENT_DYNAMIC(CFileInfoDlg, CDialogEx)

CFileInfoDlg::CFileInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_FILEINFO, pParent)
{

}

CFileInfoDlg::~CFileInfoDlg()
{
}

void CFileInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITFILEINFO, m_editFileInfo);
}


BEGIN_MESSAGE_MAP(CFileInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFileInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFileInfoDlg::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFileInfoDlg 消息处理程序


void CFileInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CFileInfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void CFileInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_editFileInfo.m_hWnd)
	{
		CRect rt;
		GetClientRect(rt);

		m_editFileInfo.MoveWindow(rt);
	}
}
