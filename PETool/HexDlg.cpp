// HexDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "HexDlg.h"
#include "afxdialogex.h"


// CHexDlg �Ի���

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


// CHexDlg ��Ϣ�������


void CHexDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CHexDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
