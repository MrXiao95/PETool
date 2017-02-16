#pragma once
#include "PE.h"
#include "afxcmn.h"
#include <vector>
using namespace std;
// CBoundImportDlg 对话框

typedef struct _IMAGEBOUNDIMPORT {
	DWORD   TimeDateStamp;
	CString OffsetModuleName;
	WORD    NumberOfModuleForwarderRefs;
} IMAGEBOUNDIMPORT, *PIMAGEBOUNDIMPORT;

class CBoundImportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBoundImportDlg)

public:
	CBoundImportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBoundImportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_BOUNDIMPORTDESCRIPTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void SetBoundImport(CPE *pe);
	virtual BOOL OnInitDialog();

private:
	CListCtrl m_listDll;
	CListCtrl m_listDllRef;
	vector<IMAGEBOUNDIMPORT> m_vecBoundImport;
	CPE *m_pe;
};
