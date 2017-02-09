#pragma once
#include "PE.h"
#include "afxcmn.h"
#include <vector>
using namespace std;
// CImportDescriptor �Ի���

class CImportDescriptor : public CDialogEx
{
	DECLARE_DYNAMIC(CImportDescriptor)

public:
	CImportDescriptor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CImportDescriptor();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_IMPORTDESCRIPTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void SetImportDescriptor(CPE* pe);
	virtual BOOL OnInitDialog();

private:
	CPE *m_pe;
	CListCtrl m_listDll;
	CListCtrl m_listFun;
	vector<IMAGE_IMPORT_DESCRIPTOR> m_importDescriptor;
public:
	afx_msg void OnNMClickListdll(NMHDR *pNMHDR, LRESULT *pResult);
};
