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
public:
	void SetDosHeder(IMAGE_DOS_HEADER* pDosHead);
private:
	void ShowDosHead();
private:
	IMAGE_DOS_HEADER *m_pDosHead;

	CString m_strMagic;
	CString m_strCblp;
	CString m_strCp;
	CString m_strCrlc;
	CString m_strCparhdr;
	CString m_strMinalloc;
	CString m_strMaxalloc;
	CString m_strSs;
	CString m_strSp;
	CString m_strCsum;
	CString m_strIp;
	CString m_strCs;
	CString m_strLfarlc;
	CString m_strOvno;
	CString m_strRes;
	CString m_strOemid;
	CString m_strOeminfo;
	CString m_strRes2;
	CString m_strLfanew;
};
