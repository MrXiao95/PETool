
// PEToolDlg.h : ͷ�ļ�
//

#pragma once
#include "FileInfoDlg.h"
#include "PEInfoDlg.h"
#include "Hexdlg.h"
// CPEToolDlg �Ի���
class CPEToolDlg : public CDialogEx
{
// ����
public:
	CPEToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PETOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
private:
    CToolBar m_wndToolBar;
	CMFCTabCtrl m_tabView;
	CFileInfoDlg m_fileInfoDlg;
	CPEInfoDlg m_peInfoDlg;
	CHexDlg m_hexDlg;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuWebsite();
};
