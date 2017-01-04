#pragma once


// CHexDlg 对话框

class CHexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHexDlg)

public:
	CHexDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHexDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_HEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
