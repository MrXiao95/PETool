// BaseRelocDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool.h"
#include "BaseRelocDlg.h"
#include "afxdialogex.h"


// CBaseRelocDlg �Ի���

IMPLEMENT_DYNAMIC(CBaseRelocDlg, CDialogEx)

CBaseRelocDlg::CBaseRelocDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_BASERELOC, pParent)
{

}

CBaseRelocDlg::~CBaseRelocDlg()
{
}

void CBaseRelocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSECTION, m_listSection);
	DDX_Control(pDX, IDC_LISTBLOCK, m_listBlock);
}


BEGIN_MESSAGE_MAP(CBaseRelocDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBaseRelocDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LISTSECTION, &CBaseRelocDlg::OnNMClickListsection)
END_MESSAGE_MAP()


// CBaseRelocDlg ��Ϣ�������


void CBaseRelocDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


BOOL CBaseRelocDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwStyle = m_listSection.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listSection.SetExtendedStyle(dwStyle); //������չ���

	m_listSection.InsertColumn(0, L"����", LVCFMT_LEFT, 60);
	m_listSection.InsertColumn(1, L"����", LVCFMT_LEFT, 200);
	m_listSection.InsertColumn(2, L"RVA", LVCFMT_LEFT, 100);
	m_listSection.InsertColumn(3, L"��Ŀ", LVCFMT_LEFT, 140);

	m_listBlock.SetExtendedStyle(dwStyle); //������չ���

	m_listBlock.InsertColumn(0, L"����", LVCFMT_LEFT, 60);
	m_listBlock.InsertColumn(1, L"RVA", LVCFMT_LEFT, 100);
	m_listBlock.InsertColumn(2, L"ƫ��", LVCFMT_LEFT, 110);
	m_listBlock.InsertColumn(3, L"����", LVCFMT_LEFT, 160);
	m_listBlock.InsertColumn(3, L"FAR��ַ", LVCFMT_LEFT, 100);

	for (int i = m_baseReloc.size()-1; i >=0 ; i--)
	{
		CString strTmp;
		strTmp.Format(L"%02d",i+1);
		int nRow = m_listSection.InsertItem(0, strTmp);
		m_listSection.SetItemText(nRow,1,CString(m_pe->GetSectionNameOfRAV(m_baseReloc[i].VirtualAddress)));
		strTmp.Format(L"%08X",m_baseReloc[i].VirtualAddress);
		m_listSection.SetItemText(nRow, 2, strTmp);
		strTmp.Format(L"%d", m_baseReloc[i].SizeOfBlock/sizeof(WORD)-4);
		m_listSection.SetItemText(nRow, 3, strTmp);
	}
	return TRUE;
}

void CBaseRelocDlg::SetBaseReloc(CPE *pe)
{
	m_pe = pe;
	vector<IMAGE_BASE_RELOCATION>().swap(m_baseReloc);
	vector<DWORD>().swap(m_baseRelocFoa);
	DWORD dwFoa = 0;
	if (pe->m_pOptionalHeader32)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader32->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	}
	else if (pe->m_pOptionalHeader64)
	{
		dwFoa = pe->RvaToFoa(pe->m_pOptionalHeader64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	}
	else
	{
		return;
	}
	IMAGE_BASE_RELOCATION baseReloc;
	int nOffset = 0;
	while (true)
	{
		memcpy(&baseReloc,((byte*)pe->m_pFileMem)+dwFoa+nOffset, sizeof(IMAGE_BASE_RELOCATION));
		if (baseReloc.SizeOfBlock == 0 || baseReloc.VirtualAddress == 0)
		{
			break;
		}
		m_baseRelocFoa.push_back(nOffset+dwFoa);
		nOffset += baseReloc.SizeOfBlock;
		m_baseReloc.push_back(baseReloc);
	}
}


void CBaseRelocDlg::OnNMClickListsection(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nIndex = m_listSection.GetSelectionMark();
	if (nIndex >= 0 && nIndex < m_baseReloc.size())
	{
		m_listBlock.DeleteAllItems();
		DWORD dwFoa = m_baseRelocFoa[nIndex]+8;
		for (int i = 0; i < m_baseReloc[nIndex].SizeOfBlock / sizeof(WORD)-4; i++)
		{
			CString strTmp;
			strTmp.Format(L"%02d", i + 1);
			m_listBlock.InsertItem(i, strTmp);
			
			WORD wData = *(WORD*)((byte*)m_pe->m_pFileMem + dwFoa);
			WORD wDataLow = wData^0x3000;
			strTmp.Format(L"%08X", m_baseReloc[nIndex].VirtualAddress + wDataLow);
			m_listBlock.SetItemText(i, 1, strTmp);

			strTmp.Format(L"%08X", m_pe->RvaToFoa(m_baseReloc[nIndex].VirtualAddress) + wDataLow);
			m_listBlock.SetItemText(i, 2, strTmp);
			
			strTmp.Format(L"%08X", *(DWORD*)((byte*)m_pe->m_pFileMem + m_pe->RvaToFoa(m_baseReloc[nIndex].VirtualAddress) + wDataLow));
			m_listBlock.SetItemText(i, 3, strTmp);
			if (wData & 0x3000)
			{
				strTmp = L"HIGHLOW(3)";
			}
			else
			{
				strTmp = L"ABSOLUTE(0)";
			}
			m_listBlock.SetItemText(i, 4, strTmp);
			dwFoa += 2;
		}
	}
	*pResult = 0;
}
