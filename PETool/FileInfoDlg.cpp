// FileInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "FileInfoDlg.h"
#include "afxdialogex.h"

static CString g_strSubSystem[15] = 
{ L"δ֪����ϵͳ"
, L"����Ҫ��ϵͳ������������"
, L"Windowsͼ�ν���"
, L"Windows����̨����"
, L"δ֪"
, L"OS/2����̨"
, L"δ֪"
, L"POSIX����̨����"
, L"����Ҫ��ϵͳ"
, L"Windows CEͼ�ν���"
, L"EFIӦ�ó���"
, L"EFI���������豸"
, L"EFI����ʱ������"
, L"EFIֻ���洢��"
, L"X-Box" };

// CFileInfoDlg �Ի���

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


// CFileInfoDlg ��Ϣ�������


void CFileInfoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CFileInfoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_strFileInfo += L"��ʾ�����Ҫ�鿴���ļ���ק���ô�����!\r\n";
	m_strFileInfo += L"================================================================================================\r\n";
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CFileInfoDlg::SetPeFileInfo(CPE* pe)
{
	CString strTmp;
	m_strFileInfo = L"\r\n";
	m_strFileInfo += L"================================================================================================\r\n";
	//�ļ�·��
	strTmp.Format(L"�ļ�·��               ��\"%s\"\r\n\r\n",CString(pe->m_szPath));
	m_strFileInfo += strTmp;
	//�ļ�����ʱ��
	time_t timeDateStamp = pe->m_pFileHead->TimeDateStamp;
	tm tmBegin;
	localtime_s(&tmBegin, &timeDateStamp);

	strTmp.Format(L"�ļ�����ʱ��       ��%04d.%02d.%02d     %02d:%02d:%02d\r\n"
		, tmBegin.tm_year+1900,tmBegin.tm_mon+1,tmBegin.tm_mday
		,tmBegin.tm_hour,tmBegin.tm_min,tmBegin.tm_sec);

	m_strFileInfo += strTmp;
	//�ļ���С
	strTmp.Format(L"�ļ���С               ��%d �ֽ�\r\n",pe->m_nFileSize);
	m_strFileInfo += strTmp;
	//����ƽ̨
	if (pe->m_pOptionalHeader32)
	{
		m_strFileInfo += L"����ƽ̨               ��Windows32λ\r\n";
	}
	else
	{
		m_strFileInfo += L"����ƽ̨               ��Windows64λ\r\n";
	}
	//PE�ļ�ͷ��ַ
	strTmp.Format(L"PE�ļ�ͷ��ַ       ��0x%08x\r\n",pe->m_pDosHead->e_lfanew);
	m_strFileInfo += strTmp;
	//����ַ ��ڵ�EP(RVA)
	DWORD dwEntryPoint = 0;
	WORD dwSubsystem;
	if (pe->m_pOptionalHeader32)
	{ 
		strTmp.Format(L"����ַ                   ��0x%08x\r\n", pe->m_pOptionalHeader32->ImageBase);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"��ڵ�EP(RVA)      ��0x%08x\r\n", pe->m_pOptionalHeader32->AddressOfEntryPoint);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"��ڵ�OEP(RAW)  ��0x%08x\r\n", pe->RvaToRaw(dwEntryPoint = pe->m_pOptionalHeader32->AddressOfEntryPoint));
		strTmp.MakeUpper();
		dwSubsystem = pe->m_pOptionalHeader32->Subsystem;
		m_strFileInfo += strTmp;
	}
	else
	{
		strTmp.Format(L"����ַ                   ��0x%08x\r\n", pe->m_pOptionalHeader64->ImageBase);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"��ڵ�EP(RVA)      ��0x%08x\r\n", pe->m_pOptionalHeader64->AddressOfEntryPoint);
		strTmp.MakeUpper();
		m_strFileInfo += strTmp;
		strTmp.Format(L"��ڵ�OEP(RAW)  ��0x%08x\r\n", pe->RvaToRaw(dwEntryPoint = pe->m_pOptionalHeader64->AddressOfEntryPoint));
		strTmp.MakeUpper();
		dwSubsystem = pe->m_pOptionalHeader64->Subsystem;
		m_strFileInfo += strTmp;
	}
	
	//��ڵ�EP���ڽ�
	for (int i = 0; i < pe->m_nSection; i++)
	{
		if (dwEntryPoint >= pe->m_pSectionHead[i].VirtualAddress && dwEntryPoint <= pe->m_pSectionHead[i].VirtualAddress + pe->m_pSectionHead[i].SizeOfRawData)
		{
			char szName[9] = {0};
			memcpy(szName, pe->m_pSectionHead[i].Name,8);
			strTmp.Format(L"��ڵ�EP���ڽ�   ��[%s] [%d / %d]\r\n", CString(szName),i+1, pe->m_nSection);
			m_strFileInfo += strTmp;
			break;
		}
	}
	//������Ŀ
	CString strSecNames;
	for (int i = 0; i < pe->m_nSection; i++)
	{
		CString strName;
		strName.Format(L"    [%s]", CString(pe->m_pSectionHead[i].Name));
		strSecNames += strName;
	}
	strTmp.Format(L"������Ŀ               ��%d��\t%s\r\n",  pe->m_nSection,strSecNames);
	m_strFileInfo += strTmp;
	//��ϵͳ
	strTmp.Format(L"��ϵͳ                   ��%s\r\n", g_strSubSystem[dwSubsystem]);
	m_strFileInfo += strTmp;
	m_strFileInfo += L"================================================================================================\r\n";
	UpdateData(FALSE);
}