#pragma once


// CDosHeaderDlg �Ի���

class CDosHeaderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDosHeaderDlg)

public:
	CDosHeaderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDosHeaderDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DOSHEAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_strMagic;
};
