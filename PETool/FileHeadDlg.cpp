// FileHeadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "FileHeadDlg.h"
#include "afxdialogex.h"


// CFileHeadDlg �Ի���

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


// CFileHeadDlg ��Ϣ�������


void CFileHeadDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CFileHeadDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CFileHeadDlg::SetFileHead(IMAGE_FILE_HEADER& fileHead)
{
	m_pFileHead = &fileHead;
}

void CFileHeadDlg::ShowFileHead()
{
}