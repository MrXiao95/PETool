
// PEToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "PEToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPEToolDlg �Ի���



CPEToolDlg::CPEToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPEToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPEToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_MENU_ABOUT, &CPEToolDlg::OnMenuAbout)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	ON_COMMAND(IDC_MENU_DOSHEAD, &CPEToolDlg::OnMenuDoshead)
	ON_COMMAND(IDM_MENU_FILEHEAD, &CPEToolDlg::OnMenuFilehead)
	ON_COMMAND(IDM_MENU_OPTHEAD, &CPEToolDlg::OnMenuOpthead)
	ON_COMMAND(IDM_MENU_DATADIRECTORY, &CPEToolDlg::OnMenuDatadirectory)
	ON_COMMAND(IDM_MENU_SECTIONTABLE, &CPEToolDlg::OnMenuSectiontable)
	ON_COMMAND(IDM_MENU_IMPORTDESCRIPTOR, &CPEToolDlg::OnMenuImportdescriptor)
	ON_COMMAND(IDM_MENU_DEBUGINFO, &CPEToolDlg::OnMenuDebuginfo)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CPEToolDlg ��Ϣ�������

BOOL CPEToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD |
        WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS |
        CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
    {
        EndDialog(IDCANCEL);
    }
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST, 0);
    CRect rt;
    GetClientRect(rt);
    m_wndToolBar.MoveWindow(rt.left, rt.top, rt.right, 30);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPEToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPEToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPEToolDlg::OnMenuAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

BOOL CPEToolDlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult) 
{
	if (GetRoutingFrame() != NULL)
	{
		return FALSE;
	}

	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	TCHAR szFullText[512];
	CString strTipText;
	UINT nID = pNMHDR->idFrom;

	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		nID = ::GetDlgCtrlID((HWND)nID);
	}

	if (nID != 0)
	{
		AfxLoadString(nID, szFullText);
		strTipText = szFullText;

		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			_wcstombsz(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
		}
		else
		{
			lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}

		*pResult = 0;

		::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE |SWP_NOSIZE | SWP_NOMOVE | SWP_NOOWNERZORDER); 
	}
	return TRUE;
}

//DOSͷ
void CPEToolDlg::OnMenuDoshead()
{
	MessageBox(L"DOSͷ");
}

//��׼PEͷ
void CPEToolDlg::OnMenuFilehead()
{
	MessageBox(L"��׼PEͷ");

}

//��ѡPEͷ
void CPEToolDlg::OnMenuOpthead()
{
	MessageBox(L"��ѡPEͷ");

}

//����Ŀ¼��
void CPEToolDlg::OnMenuDatadirectory()
{
	MessageBox(L"����Ŀ¼��");

}

//�ڱ�
void CPEToolDlg::OnMenuSectiontable()
{
	MessageBox(L"�ڱ�");

}

//�����
void CPEToolDlg::OnMenuImportdescriptor()
{
	MessageBox(L"�����");

}

//������Ϣ
void CPEToolDlg::OnMenuDebuginfo()
{
	MessageBox(L"������Ϣ");

}


void CPEToolDlg::OnDropFiles(HDROP hDropInfo)
{
	int nCount;
	TCHAR szFilePath[MAX_PATH] = { 0 };
	nCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (nCount == 1)
	{
		DragQueryFile(hDropInfo, 0, szFilePath, sizeof(szFilePath));
		CString strExt = PathFindExtension(szFilePath);
		if (strExt.CompareNoCase(L".dll") == 0 || strExt.CompareNoCase(L".exe") == 0)
		{
		}
		else
		{
			MessageBox(L"ֻ�ܼ��ؿ�ִ���ļ�");
		}
	}
	else
	{
		MessageBox(L"һ��ֻ�ܼ���һ���ļ�");
	}
	DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}
