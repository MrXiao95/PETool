#pragma once


// CPEFileInfo 对话框

class CPEInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPEInfoDlg)

public:
	CPEInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
