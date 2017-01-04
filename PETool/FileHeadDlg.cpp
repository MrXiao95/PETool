// FileHeadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "FileHeadDlg.h"
#include "afxdialogex.h"


// CFileHeadDlg 对话框

IMPLEMENT_DYNAMIC(CFileHeadDlg, CDialogEx)

CFileHeadDlg::CFileHeadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_FILEHEAD, pParent)
{

}

CFileHeadDlg::~CFileHeadDlg()
{
}

void CFileHeadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileHeadDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFileHeadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFileHeadDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFileHeadDlg 消息处理程序


void CFileHeadDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CFileHeadDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CFileHeadDlg::SetFileHead(IMAGE_FILE_HEADER& fileHead)
{
	m_pFileHead = &fileHead;
}

void CFileHeadDlg::ShowFileHead()
{
}