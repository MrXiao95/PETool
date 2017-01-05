#pragma once


// CDosHeaderDlg 对话框

class CDosHeaderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDosHeaderDlg)

public:
	CDosHeaderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDosHeaderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DOSHEAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_strMagic;
};
