#pragma once


// CFileHeadDlg �Ի���

class CFileHeadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileHeadDlg)

public:
	CFileHeadDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileHeadDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FILEHEAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void SetFileHead(IMAGE_FILE_HEADER* fileHead);
private:
	void ShowFileHead();
private:
	IMAGE_FILE_HEADER* m_pFileHead;
	
	CString m_strMachine;// ����ƽ̨
	CString m_strNumOfSections;// ������Ŀ
	CString m_strTimeDateStamp;// ʱ���
	CString m_strPointSymbolTab;// Pointer to COFF
	CString m_strNumberOfSymbols;// COFF table size
	CString m_strSizeOfOptHeader;// ��ѡPEͷ��С
	CString m_strCharateristics;// ����
};
