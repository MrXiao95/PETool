#pragma once
#include "afxcmn.h"


// CSectionHeadDlg 对话框

class CSectionHeadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSectionHeadDlg)

public:
	CSectionHeadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSectionHeadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SECTIONHEAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void SetSetcionHead(IMAGE_SECTION_HEADER *pSectionHead, int nSection);
	void ShowSectionHead();
private:
	int m_nSection;
	IMAGE_SECTION_HEADER *m_pSectionHead;
	CListCtrl m_listSection;
	CString m_strNumber;
};
