#pragma once
#include "afxwin.h"


// CDataDirectory 对话框

class CDataDirectory : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDirectory)

public:
	CDataDirectory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataDirectory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DATADIRECTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void SetDataDirectory(IMAGE_DATA_DIRECTORY* pDataDirectory);
	void ShowDataDirectory();
	virtual BOOL OnInitDialog();

private:
	IMAGE_DATA_DIRECTORY* m_pDataDirectory;

	CString m_strExportRva;
	CString m_strExportSize;

	CString m_strImportRva;
	CString m_strImportSize;

	CString m_strResRva;
	CString m_strResSize;

	CString m_strExceptionRva;
	CString m_strExceptionSize;

	CString m_strSecurityRva;
	CString m_strSecuritySize;

	CString m_strBaseRelocRva;
	CString m_strBaseRelocSize;

	CString m_strDebugRva;
	CString m_strDebugSize;

	CString m_strArchitectureRva;
	CString m_strArchitectureSize;

	CString m_strGlobalPtrRva;
	CString m_strGlobalPtrSize;

	CString m_strTlsRva;
	CString m_strTlsSize;

	CString m_strConfigRva;
	CString m_strConfigSize;

	CString m_strBoundImportRva;
	CString m_strBoundImportSize;

	CString m_strIatRva;
	CString m_strIatSize;

	CString m_strDelayImportRva;
	CString m_strDelayImportSize;

	CString m_strComRva;
	CString m_strComSize;

	CString m_strReserverRva;
	CString m_strReserverSize;
	CButton m_btnExport;
public:
	afx_msg void OnBnClickedBtnexport();
	afx_msg void OnBnClickedBtnreloc();
};
