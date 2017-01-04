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
	, m_strPeStruct(_T(""))
{

}

CPEInfoDlg::~CPEInfoDlg()
{
}

void CPEInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITPE, m_strPeStruct);
	DDX_Control(pDX, IDC_EDITPE, m_editPE);
}


BEGIN_MESSAGE_MAP(CPEInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPEInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPEInfoDlg::OnBnClickedCancel)
	ON_WM_SIZE()
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


void CPEInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_editPE.m_hWnd)
	{
		CRect rt;
		GetClientRect(rt);

		m_editPE.MoveWindow(rt);
	}
}

void CPEInfoDlg::SetPeStruct(CPE *pe)
{

}

