#pragma once


// COptionalHead 对话框

class COptionalHead : public CDialogEx
{
	DECLARE_DYNAMIC(COptionalHead)

public:
	COptionalHead(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionalHead();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_OPTFILEHEAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetOptionalHead32(IMAGE_OPTIONAL_HEADER32 *pOptionalHeader32);
	void SetOptionalHead64(IMAGE_OPTIONAL_HEADER64 *pOptionalHeader64);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	IMAGE_OPTIONAL_HEADER32 *pOptionalHeader32;
	IMAGE_OPTIONAL_HEADER64 *pOptionalHeader64;
	CString m_strMagic;
	CString m_strMajorLinkerVersion;
	CString m_strMinorLinkerVersion;
	CString m_strSizeOfCode;
	CString m_strSizeOfInitData;
	CString m_strSizeOfUninitData;
	CString m_strEntryPoint;
	CString m_strBaseOfCode;
	CString m_strBaseOfData;
	CString m_strImageBase;
	CString m_strSectionAlignment;
	CString m_strFileAlignment;
	CString m_strMajorOSVersion;
	CString m_strMinorOSVersion;
	CString m_strMajorImageVersion;
	CString m_strMinorImageVersion;
	CString m_strMajorSubsystemVersion;
	CString m_strMinorSubsystemVersion;
	CString m_strWin32VersionValue;
	CString m_strSizeOfImage;
	CString m_strSizeOfHeaders;
	CString m_strCheckSum;
	CString m_strSubsystem;
	CString m_strDllCharacteristics;
	CString m_strSizeOfStackReserve;
	CString m_strSizeOfStackCommit;
	CString m_strSizeOfHeapReserve;
	CString m_strSizeOfHeapCommit;
	CString m_strLoaderFlags;
	CString m_strNumberOfRvaAndSizes;
};
