
// PEToolDlg.h : 头文件
//

#pragma once
#include "FileInfoDlg.h"
#include "PEInfoDlg.h"
#include "Hexdlg.h"
#include "PE.h"


// CPEToolDlg 对话框
class CPEToolDlg : public CDialogEx
{
// 构造
public:
	CPEToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DLG_PETOOL };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuAbout();
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnMenuDoshead();
	afx_msg void OnMenuFilehead();
	afx_msg void OnMenuOpthead();
	afx_msg void OnMenuDatadirectory();
	afx_msg void OnMenuSectiontable();
	afx_msg void OnMenuImportdescriptor();
	afx_msg void OnMenuDebuginfo();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuWebsite();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuExportdescriptor();
	afx_msg LRESULT ShowExportDirctory(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ShowBaseReloc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ShowImport(WPARAM wParam, LPARAM lParam);
private:
	void LoadFile(CString& strPath);
private:
    CToolBar m_wndToolBar;
	CMFCTabCtrl m_tabView;
	CFileInfoDlg m_fileInfoDlg;
	CPEInfoDlg m_peInfoDlg;
	CHexDlg m_hexDlg;
	CPE m_pe;
};
