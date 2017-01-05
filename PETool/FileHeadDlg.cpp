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
	, m_strMachine(_T(""))
	, m_strNumOfSections(_T(""))
	, m_strTimeDateStamp(_T(""))
	, m_strPointSymbolTab(_T(""))
	, m_strNumberOfSymbols(_T(""))
	, m_strSizeOfOptHeader(_T(""))
	, m_strCharateristics(_T(""))
{

}

CFileHeadDlg::~CFileHeadDlg()
{
}

void CFileHeadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITMACHINE, m_strMachine);
	DDX_Text(pDX, IDC_EDITNUMBERSEC, m_strNumOfSections);
	DDX_Text(pDX, IDC_EDITTIMERDATA, m_strTimeDateStamp);
	DDX_Text(pDX, IDC_EDITPOINTTOSYMBOL, m_strPointSymbolTab);
	DDX_Text(pDX, IDC_EDITNUMOFSYSTEM, m_strNumberOfSymbols);
	DDX_Text(pDX, IDC_EDITSIZEOFOPTIONHEAD, m_strSizeOfOptHeader);
	DDX_Text(pDX, IDC_EDITCHARATERISTICS, m_strCharateristics);
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

void CFileHeadDlg::SetFileHead(IMAGE_FILE_HEADER* fileHead)
{
	if (fileHead)
	{
		m_pFileHead = fileHead;
		ShowFileHead();
	}
}

void CFileHeadDlg::ShowFileHead()
{
	m_strMachine.Format(L"%04x",m_pFileHead->Machine);
	m_strNumOfSections.Format(L"%04x",m_pFileHead->NumberOfSections);
	m_strTimeDateStamp.Format(L"%08x", m_pFileHead->TimeDateStamp);
	m_strPointSymbolTab.Format(L"%08x", m_pFileHead->PointerToSymbolTable);
	m_strNumberOfSymbols.Format(L"%08x", m_pFileHead->NumberOfSymbols);
	m_strSizeOfOptHeader.Format(L"%04x", m_pFileHead->SizeOfOptionalHeader);
	m_strCharateristics.Format(L"%04x", m_pFileHead->Characteristics);
}