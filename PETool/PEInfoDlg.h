#pragma once
#include "afxwin.h"
#include "PE.h"

// CPEFileInfo �Ի���

class CPEInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPEInfoDlg)

public:
	CPEInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEInfoDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetPeStruct(CPE *pe);

	void ShowNtHead(const CPE * pe, const byte * pBaseAdd);

	void ShowOptionalHeader(const CPE * pe, const byte * pBaseAdd);

	void ShowOptionalHeader64(const CPE * pe, const byte * pBaseAdd);

	void ShowDataDirectory64(const CPE * pe, const byte * pBaseAdd);

	void ShowOptionalHeader32(const CPE * pe, const byte * pBaseAdd);

	void ShowDataDirectory32(const CPE * pe, const byte * pBaseAdd);

	void ShowDosHead(const CPE * pe, const byte * pBaseAdd);

	void ShowSectionHead(const CPE * pe, const byte * pBaseAdd);

private:
	CString m_strPeStruct;
	CEdit m_editPE;
};
