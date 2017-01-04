#pragma once
#include "afxwin.h"
#include "Definition.h"
#include "pe.h"
// CFileInfoDlg �Ի���

class CFileInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileInfoDlg)

public:
	CFileInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileInfoDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FILEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	void SetPeFileInfo(CPE* pe);
private:
	CEdit m_editFileInfo;
	CString m_strFileInfo;
};
