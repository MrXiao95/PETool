#pragma once
#include "afxcmn.h"
#include "PE.h"
#include <vector>
using namespace std;
// CExportDirectoryDlg �Ի���

typedef struct EXPORTDIRECTORY
{
	DWORD nID;
	DWORD dwRVA;
	DWORD dwOffset;
	CString strName;
}EXPORTDIRECTORY,*PEXPORTDIRECTORY;

class CExportDirectoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExportDirectoryDlg)

public:
	CExportDirectoryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExportDirectoryDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPORTDIRECTORY_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	void SetExportDirectory(CPE *pe);
	void ShowExportDirectory();
private:
	CListCtrl m_listFun;
	vector<EXPORTDIRECTORY> m_exportDirectory;
	CString m_strTime;
	CString m_strNameRav;
	CString m_strSatartID;
	CString m_strFunCount;
	CString m_strFunCountByName;
	CString m_strFunTabRva;
	CString m_strNameTabRva;
	CString m_strIDTabRva;
	CString m_strDLLName;
};
