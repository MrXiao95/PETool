#pragma once


// CFileHeadDlg 对话框

class CFileHeadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileHeadDlg)

public:
	CFileHeadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileHeadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FILEHEAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void SetFileHead(IMAGE_FILE_HEADER& fileHead);
private:
	void ShowFileHead();
private:
	IMAGE_FILE_HEADER* m_pFileHead;
};
