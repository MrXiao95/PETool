#pragma once
#include "afxcmn.h"
#include "PE.h"
#include <vector>
using namespace std;
// CBaseRelocDlg �Ի���

class CBaseRelocDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseRelocDlg)

public:
	CBaseRelocDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseRelocDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_BASERELOC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void SetBaseReloc(CPE *pe);
private:
	CListCtrl m_listSection;
	CListCtrl m_listBlock;
	vector<IMAGE_BASE_RELOCATION> m_baseReloc;
	vector<DWORD> m_baseRelocFoa;
	CPE *m_pe;
public:
	afx_msg void OnNMClickListsection(NMHDR *pNMHDR, LRESULT *pResult);
};
