// PEFileInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "PEInfoDlg.h"
#include "afxdialogex.h"


// CPEFileInfo �Ի���

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


// CPEFileInfo ��Ϣ�������


void CPEInfoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CPEInfoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_strPeStruct = L"================================================================================================\r\nDOS�ײ� �ṹ˵����\r\n\r\n";
	CString strTmp;
	DWORD dosSub = (byte*)&(pe->m_pDosHead->e_lfanew) - (byte*)(pe->m_pDosHead) + sizeof(DWORD) - 1;
	strTmp.Format(L"MZ header��       [��ַ(RAW)��Χ:0x00000000 - 0x%08X] [����:0040h] [����:IMAGE_DOS_HEADER] [DOS�ļ�ͷ.]\r\n", dosSub);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DOS stub header��[��ַ(RAW)��Χ:0x%08X - 0x%08X][����:00a0h][����:DOS STUB][DOS����Ч��EXE�ļ���ʽ, ���(���Ȳ���).]\r\n", dosSub+1,pe->m_pDosHead->e_lfanew-1);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DOS_HEADER (DOS�ļ�ͷ)�ṹ���£�\r\n\r\n";
	strTmp.Format(L"e_magic��    [��ַ(RAW):0x00000000] [����:02h] [����:0x%X] [Magic number.][DOS��ִ���ļ����\"MZ\"ͷ,����Ϊ\"5A4Dh\",��ֵ.]\r\n",pe->m_pDosHead->e_magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cblp��     [��ַ(RAW):0x00000002] [����:02h] [����:0x%4X] [Bytes on last page of file.]\r\n",pe->m_pDosHead->e_cblp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cp��	     [��ַ(RAW):0x00000004] [����:02h] [����:0x%4X] [Pages in file.]\r\n",pe->m_pDosHead->e_cp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_crlc��     [��ַ(RAW):0x00000006] [����:02h] [����:0x%4X] [Relocations.]\r\n",pe->m_pDosHead->e_crlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cparhdr��  [��ַ(RAW):0x00000008] [����:02h] [����:0x%04X] [Size of header in paragraphs.]\r\n",pe->m_pDosHead->e_cparhdr);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_minalloc�� [��ַ(RAW):0x0000000a] [����:02h] [����:0x%04X] [Minimum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_minalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_maxalloc�� [��ַ(RAW):0x0000000c] [����:02h] [����:0x%04X] [Maximum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_maxalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ss��       [��ַ(RAW):0x0000000e] [����:02h] [����:0x%04X] [Initial(relative) SS value.]\r\n", pe->m_pDosHead->e_ss);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_sp��       [��ַ(RAW):0x00000010] [����:02h] [����:0x%04X] [Initial SP value.]\r\n", pe->m_pDosHead->e_sp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_csum��     [��ַ(RAW):0x00000012] [����:02h] [����:0x%04X] [Checksum.]\r\n", pe->m_pDosHead->e_csum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ip��       [��ַ(RAW):0x00000014] [����:02h] [����:0x%04X] [Initial IP value.] [DOS�������IP.]\r\n", pe->m_pDosHead->e_ip);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cs��       [��ַ(RAW):0x00000016] [����:02h] [����:0x%04X] [Initial(relative) CS value.] [DOS��������CS.]\r\n", pe->m_pDosHead->e_cs);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfarlc��   [��ַ(RAW):0x00000018] [����:02h] [����:0x%04X] [File address of relocation table.]\r\n", pe->m_pDosHead->e_lfarlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ovno��     [��ַ(RAW):0x0000001a] [����:02h] [����:0x%04X] [Overlay number.]\r\n", pe->m_pDosHead->e_ovno);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res[4]��   [��ַ(RAW):0x0000001c] [����:08h] [����:0x0000000000000000] [Reserved words.]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oemid��    [��ַ(RAW):0x00000024] [����:02h] [����:0x%04X] [OEM identifier(for e_oeminfo).]\r\n", pe->m_pDosHead->e_oemid);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oeminfo��  [��ַ(RAW):0x00000026] [����:02h] [����:0x%04X] [OEM information; e_oemid specific.]\r\n", pe->m_pDosHead->e_oeminfo);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res2[10]�� [��ַ(RAW):0x00000028] [����:14h] [����:0x0000000000000000000000000000000000000000] [Reserved words.] [����Ϊ\"20\".]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfanew��   [��ַ(RAW):0x0000003c] [����:04h] [����:0x000000E0] [ƫ����:0x%08X] [File address of new exe header.] [PE�ļ�ͷ��ַ.]\r\n", pe->m_pDosHead->e_lfanew);
	m_strPeStruct += strTmp;
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";

	m_strPeStruct += L"================================================================================================\r\n";
	UpdateData(FALSE);
}