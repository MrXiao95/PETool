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
	m_strPeStruct = L"================================================================================================\r\nDOS首部 结构说明：\r\n\r\n";
	CString strTmp;
	DWORD dosSub = (byte*)&(pe->m_pDosHead->e_lfanew) - (byte*)(pe->m_pDosHead) + sizeof(DWORD) - 1;
	strTmp.Format(L"MZ header：       [地址(RAW)范围:0x00000000 - 0x%08X] [长度:0040h] [名称:IMAGE_DOS_HEADER] [DOS文件头.]\r\n", dosSub);
	m_strPeStruct += strTmp;
	strTmp.Format(L"DOS stub header：[地址(RAW)范围:0x%08X - 0x%08X][长度:00a0h][名称:DOS STUB][DOS下有效的EXE文件格式, 存根(长度不定).]\r\n", dosSub+1,pe->m_pDosHead->e_lfanew-1);
	m_strPeStruct += strTmp;

	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";
	m_strPeStruct += L"IMAGE_DOS_HEADER (DOS文件头)结构如下：\r\n\r\n";
	strTmp.Format(L"e_magic：    [地址(RAW):0x00000000] [长度:02h] [数据:0x%X] [Magic number.][DOS可执行文件标记\"MZ\"头,定义为\"5A4Dh\",定值.]\r\n",pe->m_pDosHead->e_magic);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cblp：     [地址(RAW):0x00000002] [长度:02h] [数据:0x%4X] [Bytes on last page of file.]\r\n",pe->m_pDosHead->e_cblp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cp：	     [地址(RAW):0x00000004] [长度:02h] [数据:0x%4X] [Pages in file.]\r\n",pe->m_pDosHead->e_cp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_crlc：     [地址(RAW):0x00000006] [长度:02h] [数据:0x%4X] [Relocations.]\r\n",pe->m_pDosHead->e_crlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cparhdr：  [地址(RAW):0x00000008] [长度:02h] [数据:0x%04X] [Size of header in paragraphs.]\r\n",pe->m_pDosHead->e_cparhdr);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_minalloc： [地址(RAW):0x0000000a] [长度:02h] [数据:0x%04X] [Minimum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_minalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_maxalloc： [地址(RAW):0x0000000c] [长度:02h] [数据:0x%04X] [Maximum extra paragraphs needed.]\r\n", pe->m_pDosHead->e_maxalloc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ss：       [地址(RAW):0x0000000e] [长度:02h] [数据:0x%04X] [Initial(relative) SS value.]\r\n", pe->m_pDosHead->e_ss);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_sp：       [地址(RAW):0x00000010] [长度:02h] [数据:0x%04X] [Initial SP value.]\r\n", pe->m_pDosHead->e_sp);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_csum：     [地址(RAW):0x00000012] [长度:02h] [数据:0x%04X] [Checksum.]\r\n", pe->m_pDosHead->e_csum);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ip：       [地址(RAW):0x00000014] [长度:02h] [数据:0x%04X] [Initial IP value.] [DOS代码入口IP.]\r\n", pe->m_pDosHead->e_ip);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_cs：       [地址(RAW):0x00000016] [长度:02h] [数据:0x%04X] [Initial(relative) CS value.] [DOS代码的入口CS.]\r\n", pe->m_pDosHead->e_cs);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfarlc：   [地址(RAW):0x00000018] [长度:02h] [数据:0x%04X] [File address of relocation table.]\r\n", pe->m_pDosHead->e_lfarlc);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_ovno：     [地址(RAW):0x0000001a] [长度:02h] [数据:0x%04X] [Overlay number.]\r\n", pe->m_pDosHead->e_ovno);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res[4]：   [地址(RAW):0x0000001c] [长度:08h] [数据:0x0000000000000000] [Reserved words.]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oemid：    [地址(RAW):0x00000024] [长度:02h] [数据:0x%04X] [OEM identifier(for e_oeminfo).]\r\n", pe->m_pDosHead->e_oemid);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_oeminfo：  [地址(RAW):0x00000026] [长度:02h] [数据:0x%04X] [OEM information; e_oemid specific.]\r\n", pe->m_pDosHead->e_oeminfo);
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_res2[10]： [地址(RAW):0x00000028] [长度:14h] [数据:0x0000000000000000000000000000000000000000] [Reserved words.] [长度为\"20\".]\r\n");
	m_strPeStruct += strTmp;
	strTmp.Format(L"e_lfanew：   [地址(RAW):0x0000003c] [长度:04h] [数据:0x000000E0] [偏移量:0x%08X] [File address of new exe header.] [PE文件头地址.]\r\n", pe->m_pDosHead->e_lfanew);
	m_strPeStruct += strTmp;
	m_strPeStruct += L"------------------------------------------------------------------------------------------------\r\n";

	m_strPeStruct += L"================================================================================================\r\n";
	UpdateData(FALSE);
}