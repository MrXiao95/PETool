// DosHeaderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "DosHeaderDlg.h"
#include "afxdialogex.h"


// CDosHeaderDlg �Ի���

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


// CDosHeaderDlg ��Ϣ�������
