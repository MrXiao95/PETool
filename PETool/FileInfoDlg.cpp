// FileInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "FileInfoDlg.h"
#include "afxdialogex.h"

static CString g_strSubSystem[15] = 
{ L"未知的子系统"
, L"不需要子系统（如驱动程序）"
, L"Windows图形界面"
, L"Windows控制台界面"
, L"未知"
, L"OS/2控制台"
, L"未知"
, L"POSIX控制台界面"
, L"不需要子系统"
, L"Windows CE图形界面"
, L"EFI应用程序"
, L"EFI引导服务设备"
, L"EFI运行时间驱动"
, L"EFI只读存储器"
, L"X-Box" };

// CFileInfoDlg 对话框

IMPLEMENT_DYNAMIC(CFileInfoDlg, CDialogEx)

CFileInfoDlg::CFileInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_FILEINFO, pParent)
	, m_strFileInfo(_T(""))

{
}

CFileInfoDlg::~CFileInfoDlg()
{
}

void CFileInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITFILEINFO, m_editFileInfo);
	DDX_Text(pDX, IDC_EDITFILEINFO, m_strFileInfo);
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


BOOL CFileInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_strFileInfo += L"\r\n";
	m_strFileInfo += L"================================================================================================\r\n";
	m_strFileInfo += L"提示：请把要查看的文件拖拽到该窗口中!\r\n";
	m_strFileInfo += L"================================================================================================\r\n";
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CFileInfoDlg::SetPeFileInfo(CPE* pe)
{
	CString strTmp;
	m_strFileInfo = L"\r\n";
	m_strFileInfo += L"================================================================================================\r\n";
	//文件路径
	strTmp.Format(L"文件路径               ：\"%s\"\r\n\r\n",CString(pe->m_szPath));
	m_strFileInfo += strTmp;
	//文件创建时间
	time_t timeDateStamp = pe->m_pFileHead->TimeDateStamp;
	tm tmBegin;
	localtime_s(&tmBegin, &timeDateStamp);

	strTmp.Format(L"文件创建时间       ：%04d.%02d.%02d     %02d:%02d:%02d\r\n"
		, tmBegin.tm_year+1900,tmBegin.tm_mon+1,tmBegin.tm_mday
		,tmBegin.tm_hour,tmBegin.tm_min,tmBegin.tm_sec);

	m_strFileInfo += strTmp;
	//文件大小
	strTmp.Format(L"文件大小               ：%d 字节\r\n",pe->m_nFileSize);
	m_strFileInfo += strTmp;
	//运行平台
	if (pe->m_pOptionalHeader32)
	{
		m_strFileInfo += L"运行平台               ：Windows32位\r\n";
	}
	else
	{
		m_strFileInfo += L"运行平台               ：Windows64位\r\n";
	}
	//PE文件头地址
	strTmp.Format(L"PE文件头地址       ：0x%08x\r\n",pe->m_pDosHead->e_lfanew);
	m_strFileInfo += strTmp;
	//基地址 入口点EP(RVA)
	DWORD dwEntryPoint = 0;
	WORD dwSubsystem;
	if (pe->m_pOptionalHeader32)
	{ 
		strTmp.Format(L"基地址                   ：0x%08x\r\n", pe->m_pOptionalHeader32->ImageBase);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"入口点EP(RVA)      ：0x%08x\r\n", pe->m_pOptionalHeader32->AddressOfEntryPoint);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"入口点OEP(RAW)  ：0x%08x\r\n", pe->RvaToRaw(dwEntryPoint = pe->m_pOptionalHeader32->AddressOfEntryPoint));
		strTmp.MakeUpper();
		dwSubsystem = pe->m_pOptionalHeader32->Subsystem;
		m_strFileInfo += strTmp;
	}
	else
	{
		strTmp.Format(L"基地址                   ：0x%08x\r\n", pe->m_pOptionalHeader64->ImageBase);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"入口点EP(RVA)      ：0x%08x\r\n", pe->m_pOptionalHeader64->AddressOfEntryPoint);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"入口点OEP(RAW)  ：0x%08x\r\n", pe->RvaToRaw(dwEntryPoint = pe->m_pOptionalHeader64->AddressOfEntryPoint));
		strTmp.MakeUpper();
		dwSubsystem = pe->m_pOptionalHeader64->Subsystem;
		m_strFileInfo += strTmp;
	}
	
	//入口点EP所在节
	for (int i = 0; i < pe->m_nSection; i++)
	{
		if (dwEntryPoint >= pe->m_pSectionHead[i].VirtualAddress && dwEntryPoint <= pe->m_pSectionHead[i].VirtualAddress + pe->m_pSectionHead[i].SizeOfRawData)
		{
			char szName[9] = {0};
			memcpy(szName, pe->m_pSectionHead[i].Name,8);
			strTmp.Format(L"入口点EP所在节   ：[%s] [%d / %d]\r\n", CString(szName),i+1, pe->m_nSection);
			m_strFileInfo += strTmp;
			break;
		}
	}
	//区段数目
	CString strSecNames;
	for (int i = 0; i < pe->m_nSection; i++)
	{
		CString strName;
		strName.Format(L"    [%s]", CString(pe->m_pSectionHead[i].Name));
		strSecNames += strName;
	}
	strTmp.Format(L"区段数目               ：%d个\t%s\r\n",  pe->m_nSection,strSecNames);
	m_strFileInfo += strTmp;
	//子系统
	strTmp.Format(L"子系统                   ：%s\r\n", g_strSubSystem[dwSubsystem]);
	m_strFileInfo += strTmp;
	m_strFileInfo += L"================================================================================================\r\n";
	UpdateData(FALSE);
}