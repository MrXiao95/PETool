#pragma once


// CHexDlg �Ի���

class CHexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHexDlg)

public:
	CHexDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHexDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_HEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};