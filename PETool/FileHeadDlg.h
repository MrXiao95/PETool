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
	void SetFileHead(IMAGE_FILE_HEADER* fileHead);
private:
	void ShowFileHead();
private:
	IMAGE_FILE_HEADER* m_pFileHead;
	
	CString m_strMachine;// 运行平台
	CString m_strNumOfSections;// 区段数目
	CString m_strTimeDateStamp;// 时间戳
	CString m_strPointSymbolTab;// Pointer to COFF
	CString m_strNumberOfSymbols;// COFF table size
	CString m_strSizeOfOptHeader;// 可选PE头大小
	CString m_strCharateristics;// 特征
};
