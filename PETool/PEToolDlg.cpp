
// PEToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool.h"
#include "PEToolDlg.h"
#include "afxdialogex.h"
#include "FileHeadDlg.h"
#include "DosHeaderDlg.h"
#include "SectionHeadDlg.h"
#include "DataDirectory.h"
#include "ExportDirectoryDlg.h"
#include "OptionalHead.h"
#include "BaseRelocDlg.h"
#include "ImportDescriptor.h"
#include "BoundImportDlg.h"
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TOOLBARHIGH 30

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPEToolDlg 对话框



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
	ON_WM_SIZE()
	ON_COMMAND(IDM_MENU_WEBSITE, &CPEToolDlg::OnMenuWebsite)
	ON_COMMAND(IDM_MENU_OPEN, &CPEToolDlg::OnMenuOpen)
	ON_COMMAND(IDM_MENU_EXIT, &CPEToolDlg::OnMenuExit)
	ON_COMMAND(IDM_MENU_EXPORTDESCRIPTOR, &CPEToolDlg::OnMenuExportdescriptor)
	ON_MESSAGE(WM_USER_SHOWEXPORTDIRCTORY,&CPEToolDlg::ShowExportDirctory)
	ON_MESSAGE(WM_USER_SHOWBASERELOC, &CPEToolDlg::ShowBaseReloc)
	ON_MESSAGE(WM_USER_SHOWIMPORT, &CPEToolDlg::ShowImport)
	ON_COMMAND(IDM_IMAGE_BOUND_IMPORT, &CPEToolDlg::OnImageBoundImport)
END_MESSAGE_MAP()


// CPEToolDlg 消息处理程序

BOOL CPEToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetWindowText(MAINWINDOWTITLE);

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_BORDER|
        WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS |
        CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
    {
        EndDialog(IDCANCEL);
    }
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST, 0);
    CRect rt;
    GetClientRect(rt);
    m_wndToolBar.MoveWindow(rt.left, rt.top, rt.right, TOOLBARHIGH-5);
	rt.top += TOOLBARHIGH;
	rt.bottom -= 2;
	rt.left += 2;
	rt.right += 2;
	m_tabView.Create(CMFCTabCtrl::STYLE_3D_VS2005, rt, this, 10010);
	m_tabView.SetLocation(CMFCTabCtrl::LOCATION_TOP);
	m_tabView.ModifyTabStyle(CMFCTabCtrl::STYLE_3D_ONENOTE);
	m_tabView.EnableAutoColor(FALSE);
	m_tabView.SetTabBorderSize(0);
	m_tabView.HideSingleTab(FALSE);
	m_tabView.EnableTabSwap(FALSE);
	m_tabView.ShowWindow(SW_SHOW);
	m_tabView.SetActiveTabBoldFont(TRUE);

	m_fileInfoDlg.Create(IDD_DLG_FILEINFO, &m_tabView);
	m_peInfoDlg.Create(IDD_DLG_PEINFO, &m_tabView);
	m_hexDlg.Create(IDD_DLG_HEX, &m_tabView);


	m_tabView.AddTab(&m_fileInfoDlg, L"文件信息");
	m_tabView.AddTab(&m_peInfoDlg, L"PE结构");
	m_tabView.AddTab(&m_hexDlg, L"十六进制");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPEToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPEToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPEToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_fileInfoDlg.m_hWnd)
	{
		CRect rt;
		GetClientRect(rt);
		rt.top += TOOLBARHIGH;
		rt.bottom -= 2;
		rt.left += 2;
		rt.right += 2;

		m_tabView.MoveWindow(rt);
	}
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

//DOS头
void CPEToolDlg::OnMenuDoshead()
{
	CDosHeaderDlg dlg;
	dlg.SetDosHeder(m_pe.m_pDosHead);
	dlg.DoModal();
}

//标准PE头
void CPEToolDlg::OnMenuFilehead()
{
	CFileHeadDlg dlg;
	dlg.SetFileHead(m_pe.m_pFileHead);
	dlg.DoModal();
}

//可选PE头
void CPEToolDlg::OnMenuOpthead()
{
	COptionalHead dlg;

	if (m_pe.m_pOptionalHeader32)
	{
		dlg.SetOptionalHead32(m_pe.m_pOptionalHeader32);
	}
	else if(m_pe.m_pOptionalHeader64)
	{
		dlg.SetOptionalHead64(m_pe.m_pOptionalHeader64);
	}

	dlg.DoModal();
}

//数据目录表
void CPEToolDlg::OnMenuDatadirectory()
{
	CDataDirectory dlg;
	if (m_pe.m_pOptionalHeader32)
	{
		dlg.SetDataDirectory(m_pe.m_pOptionalHeader32->DataDirectory);
		dlg.DoModal();
	}
	else if (m_pe.m_pOptionalHeader64)
	{
		dlg.SetDataDirectory(m_pe.m_pOptionalHeader64->DataDirectory);
		dlg.DoModal();
	}
	else
	{
		dlg.SetDataDirectory(NULL);
		dlg.DoModal();
	}
}

//节表
void CPEToolDlg::OnMenuSectiontable()
{
	CSectionHeadDlg dlg;
	dlg.SetSetcionHead(m_pe.m_pSectionHead,m_pe.m_nSection);
	dlg.DoModal();
}

//绑定导入表
void CPEToolDlg::OnImageBoundImport()
{
	CBoundImportDlg dlg;
	dlg.SetBoundImport(&m_pe);
	dlg.DoModal();
}

//导出表
void CPEToolDlg::OnMenuExportdescriptor()
{
	PostMessage(WM_USER_SHOWEXPORTDIRCTORY);
}

//导入表
void CPEToolDlg::OnMenuImportdescriptor()
{
	CImportDescriptor dlg;
	dlg.SetImportDescriptor(&m_pe);
	dlg.DoModal();
}

//调试信息
void CPEToolDlg::OnMenuDebuginfo()
{
	MessageBox(L"调试信息");

}

//关于
void CPEToolDlg::OnMenuAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
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
			LoadFile(CString(szFilePath));
		}
		else
		{
			MessageBox(L"只能加载可执行文件");
		}
	}
	else
	{
		MessageBox(L"一次只能加载一个文件");
	}
	DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CPEToolDlg::OnMenuWebsite()
{
	ShellExecute(NULL, _T("open"), L"http://www.dbgpro.com", NULL, NULL, SW_SHOW);
}

void CPEToolDlg::LoadFile(CString& strPath)
{
	string sttTmp = CStringA(strPath);
	if (0 == m_pe.ReadPeFile(sttTmp.data()))
	{
		CString strErrMsg;
		strErrMsg.Format(L"%s \r\n无法打开！请检查文件是否被占用，或者文件是否存在！！！",strPath);
		MessageBox(strErrMsg);
		return ;
	}

	m_fileInfoDlg.SetPeFileInfo(&m_pe);
	m_peInfoDlg.SetPeStruct(&m_pe);
    m_hexDlg.SetHexData((byte*)m_pe.m_pFileMem,m_pe.m_nFileSize);
}

void CPEToolDlg::OnMenuOpen()
{
	CFileDialog dlg(TRUE, NULL, NULL
		,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, L"EXE(*.exe)|*.exe|DLL(*.dll) |*.dll||");
	if (dlg.DoModal() == IDOK)
	{
		CString strPath  = dlg.GetPathName();
		LoadFile(strPath);
	}
}

void CPEToolDlg::OnMenuExit()
{
	PostQuitMessage(0);
}

LRESULT CPEToolDlg::ShowExportDirctory(WPARAM wParam, LPARAM lParam)
{
	CExportDirectoryDlg dlg;

	dlg.SetExportDirectory(&m_pe);
	dlg.DoModal();

	return 0;
}

LRESULT CPEToolDlg::ShowBaseReloc(WPARAM wParam, LPARAM lParam)
{
	CBaseRelocDlg dlg;
	dlg.SetBaseReloc(&m_pe);
	dlg.DoModal();

	return 0;
}

LRESULT CPEToolDlg::ShowImport(WPARAM wParam, LPARAM lParam)
{
	OnMenuImportdescriptor();

	return 0;
}
