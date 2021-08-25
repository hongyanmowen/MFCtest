
// FontManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FontManager.h"
#include "FontManagerDlg.h"
#include "afxdialogex.h"

#include "MyIsExit.h"
#include "AppData.h"
#include "FontControl.h"
#include "InfoCtrl.h"

#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ���ڼ�¼�б����ʾ���ݵ�Key
CString strFontkey;
//����bool ����isOK�������ж��Ƿ����˱��棬�޸����ݺ�Ϊfalse�������Ϊtrue
bool isOK = true;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFontManagerDlg �Ի���




CFontManagerDlg::CFontManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFontManagerDlg::IDD, pParent)
	, m_strEditFont(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
}

void CFontManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_B, m_Button_B);
	DDX_Control(pDX, IDC_BUTTON_C, m_Button_C);
	DDX_Control(pDX, IDC_BUTTON_D, m_Button_D);

	DDX_Control(pDX, IDC_COMBO_Font, m_Combo_Font);
	DDX_Control(pDX, IDC_LIST_Left, m_List_Left);
	DDX_Control(pDX, IDC_LIST_Right, m_List_Right);

	DDX_Control(pDX, IDC_CHECK_Double, m_CheckDouble);
	DDX_Control(pDX, IDC_CHECK_One, m_CheckOne);
	DDX_Control(pDX, IDC_CHECK_B, m_Double_CheckB);
	DDX_Control(pDX, IDC_CHECK_C, m_Double_CheckC);
	DDX_Control(pDX, IDC_CHECK_D, m_Double_CheckD);
	DDX_Control(pDX, IDC_RADIO_B, m_Radio_B);
	DDX_Control(pDX, IDC_RADIO_C, m_Radio_C);
	DDX_Control(pDX, IDC_RADIO_D, m_Radio_D);
	DDX_Control(pDX, IDC_RADIO_All, m_Radio_All);
	DDX_Control(pDX, IDC_EDIT_Font, m_EditFont);
	DDX_Text(pDX, IDC_EDIT_Font, m_strEditFont);
}

BEGIN_MESSAGE_MAP(CFontManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_B, &CFontManagerDlg::OnBnClickedButtonB)	// ������ť
	ON_BN_CLICKED(IDC_BUTTON_C, &CFontManagerDlg::OnBnClickedButtonC)	
	ON_BN_CLICKED(IDC_BUTTON_D, &CFontManagerDlg::OnBnClickedButtonD)

	ON_CBN_SELCHANGE(IDC_COMBO_Font, &CFontManagerDlg::OnCbnSelchangeComboFont)	// ������ĸ���
	ON_BN_CLICKED(IDC_CHECK_Double, &CFontManagerDlg::OnBnClickedCheckDouble)	// ��ѡ��ʽ

	ON_BN_CLICKED(IDC_CHECK_B, &CFontManagerDlg::OnBnClickedCheckB)	// ��ѡ�� B
	ON_BN_CLICKED(IDC_CHECK_C, &CFontManagerDlg::OnBnClickedCheckC)	// ��ѡ�� C
	ON_BN_CLICKED(IDC_CHECK_D, &CFontManagerDlg::OnBnClickedCheckD)	// ��ѡ�� D

	ON_BN_CLICKED(IDC_CHECK_One, &CFontManagerDlg::OnBnClickedCheckOne)	// ��ѡ��ť��ʽ
	ON_BN_CLICKED(IDC_RADIO_B, &CFontManagerDlg::OnBnClickedRadioB)		// ������ѡ��B
	ON_BN_CLICKED(IDC_RADIO_C, &CFontManagerDlg::OnBnClickedRadioC)
	ON_BN_CLICKED(IDC_RADIO_D, &CFontManagerDlg::OnBnClickedRadioD)
	ON_BN_CLICKED(IDC_RADIO_All, &CFontManagerDlg::OnBnClickedRadioAll)	// ������ѡ�� ȫ��

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_Left, &CFontManagerDlg::OnLvnItemchangedListLeft)	// �����б��ѡ��
	ON_BN_CLICKED(IDC_BUTTON_Add, &CFontManagerDlg::OnBnClickedButtonAdd)	// �����ֿⰴť
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CFontManagerDlg::OnBnClickedButtonDelete)	// ɾ���ֿⰴť
	ON_BN_CLICKED(IDC_BUTTON_Save, &CFontManagerDlg::OnBnClickedButtonSave)	// ���水ť
	ON_BN_CLICKED(IDCANCEL, &CFontManagerDlg::OnBnClickedCancel)	// ȡ����ť
END_MESSAGE_MAP()


// CFontManagerDlg ��Ϣ�������

BOOL CFontManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// staAppData.ReadzikuTxt();

	// ��ѡ���ʼ������
	m_Double_CheckB.EnableWindow(FALSE);
	m_Double_CheckC.EnableWindow(FALSE);
	m_Double_CheckD.EnableWindow(FALSE);

	// ��ѡ��ʼ�����ã���Ĭ��ѡ��
	m_Radio_B.EnableWindow(FALSE);
	m_Radio_C.EnableWindow(FALSE);
	m_Radio_D.EnableWindow(FALSE);
	m_Radio_All.EnableWindow(FALSE);

	// ��ʼ��ʾ B ���ֿ�
	strFontkey.Format(_T("B"));
	OnBnClickedButtonB();

	// ��ʼĬ�ϱ��水ťΪ��
	GetDlgItem(IDC_BUTTON_Save)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFontManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFontManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFontManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �ֿ����ݲ����б�
void CFontManagerDlg::InserItemFont(CString strKey)
{
	// ���ж��б��Ƿ�������
	int nItem = m_List_Left.GetItemCount();	// �б������ݵ�����
	int nSize = 0;
	std::vector<CString> FontList;	//��������
	//FontList pfontList;
	// ��ȡ��Ӧ�ֿ⵽���� FontList
	

	pInfoCtrl.GetFont(strKey[0], FontList);	
	nSize = FontList.size();	// �ж��ֿ��С
	if (nSize == 0)
	{
		MessageBox(_T("���ֿ������ݣ�����"));
		return;
	}
	if ( nItem != 0)
	{
		// nSize += nItem;

		// ���ֿ����ݲ������
		if (nItem < 15)	// ԭ������С��15
		{
			for (int i = nItem; i < 15; i++)	// �Ȳ���15
			{
				int j = 0;
				m_List_Left.InsertItem(i, FontList.at(j));	
				j++;
			}
			for (int i = 0; i < (nSize-nItem); i++)	// �ٽ�ʣ��Ĳ����Ҳ�
			{
				int j = 15 - nItem;
				m_List_Right.InsertItem(i, FontList.at(j));
				j++;
			}
		}
		
		if (nItem >= 15)	// ������15������ʣ�����ݲ��뵽�ұ�
		{
			for (int i = (nItem-15); i < nSize; i++)
			{
				int j = 0;
				m_List_Right.InsertItem(i, FontList.at(j));
				j++;
			}
		}
	}
	

	// ����б�������ݣ����ֿ����ݵ�ǰ15���������
	if (nSize < 15)
	{
		for (int i = 0; i < nSize; i++)
		{
			m_List_Left.InsertItem(i, FontList.at(i));	
		}
	}
	
	if (nSize >= 15)	// ������15����ǰ15���������,ʣ�����ݲ��뵽�ұ�
	{
		for (int i = 0; i < 15; i++)
		{
			m_List_Left.InsertItem(i, FontList.at(i));	
		}

		for (int j = 15; j < nSize; j++)
		{
			int k = 0;
			m_List_Right.InsertItem(k, FontList.at(j));
			k++;
		}
	}

	UpdateData(FALSE);	//	ˢ���б��
	return;
}

// ����B��ť
void CFontManagerDlg::OnBnClickedButtonB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ʱȫ��ɾ��
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();
	UpdateData(FALSE);

	CString strKey ;	//��������
	strKey.Format(_T("B"));
	// �ֿ����ݲ����б�
	InserItemFont(strKey);

	// ��ѡ��ʽ����ѡ��ť��ʽ������Ϊδѡ��״̬
	m_CheckDouble.SetCheck(0);
	m_CheckOne.SetCheck(0);
	OnBnClickedCheckDouble();

	strFontkey = strKey;	// ��¼�б����������

	UpdateData(FALSE);
}

// ����C��ť
void CFontManagerDlg::OnBnClickedButtonC()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ʱȫ��ɾ��
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();

	CString strKey ;	//��������
	strKey.Format(_T("C"));

	// �ֿ����ݲ����б�
	InserItemFont(strKey);

	// ��ѡ��ʽ����ѡ��ť��ʽ������Ϊδѡ��״̬
	m_CheckDouble.SetCheck(0);
	m_CheckOne.SetCheck(0);

	OnBnClickedCheckDouble();

	strFontkey = strKey;	// ��¼�б����������

	UpdateData(FALSE);
}

// ����D��ť
void CFontManagerDlg::OnBnClickedButtonD()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ʱȫ��ɾ��
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();

	CString strKey ;	//��������
	strKey.Format(_T("D"));

	// �ֿ����ݲ����б�
	InserItemFont(strKey);

	// ��ѡ��ʽ����ѡ��ť��ʽ������Ϊδѡ��״̬
	m_CheckDouble.SetCheck(0);
	m_CheckOne.SetCheck(0);
	OnBnClickedCheckDouble();

	strFontkey = strKey;	// ��¼�б����������

	UpdateData(FALSE);
}

// ������ĸ���
void CFontManagerDlg::OnCbnSelchangeComboFont()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	// ��ȡ������ѡ�е���һ��
	int nChoice = m_Combo_Font.GetCurSel();

	// ѡ�� �� �� ʱ��
	if ( nChoice == 0)
	{
		// ��������б��
		m_List_Left.DeleteAllItems();
		m_List_Right.DeleteAllItems();
	}
	// ѡ B ʱ��Ӧ��ʾ�ұ��б��
	if ( nChoice == 1)
	{
		OnBnClickedButtonB();
	}
	// ѡ C ʱ��Ӧ��ʾ�ұ��б��
	if ( nChoice == 2)
	{
		OnBnClickedButtonC();
	}
	// ѡ D ʱ��Ӧ��ʾ�ұ��б��
	if ( nChoice == 3)
	{
		OnBnClickedButtonD();
	}
}

// ��ѡ��ʽ
void CFontManagerDlg::OnBnClickedCheckDouble()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ��ѡ���ѡ��״̬
	int nCheck = m_CheckDouble.GetCheck();
	if (nCheck == 0)	// δѡ��
	{	
		/*CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_B);
		pBtn->SetCheck(0);*/
		// ����Ϊδѡ��״̬
		m_Double_CheckB.SetCheck(0);
		m_Double_CheckC.SetCheck(0);
		m_Double_CheckD.SetCheck(0);
		// ��ѡ��BCD������
		m_Double_CheckB.EnableWindow(FALSE);
		m_Double_CheckC.EnableWindow(FALSE);
		m_Double_CheckD.EnableWindow(FALSE);
		
	}
	if (nCheck == 1)	// ѡ��
	{	
		// ��ѡ��BCD������
		m_Double_CheckB.EnableWindow(TRUE);
		m_Double_CheckC.EnableWindow(TRUE);
		m_Double_CheckD.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	return;
}

// ��ѡ��ѡ��B
void CFontManagerDlg::OnBnClickedCheckB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strKey ;	//��������
	strKey.Format(_T("B"));
	int nIsCheckB = m_Double_CheckC.GetCheck();

	// ���ݸ�ѡ��״̬��ʾ�ֿ�
	ISClickedCheck(nIsCheckB, strKey);
}

// ��ѡ��ѡ��C
void CFontManagerDlg::OnBnClickedCheckC()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strKey ;	//��������
	strKey.Format(_T("C"));
	int nIsCheckC = m_Double_CheckC.GetCheck();

}

// ��ѡ��ѡ��D
void CFontManagerDlg::OnBnClickedCheckD()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// ���ݸ�ѡ��״̬��ʾ�ֿ�
void CFontManagerDlg::ISClickedCheck(int nIsCheck, CString strKey)
{
	// ��ȡ��Ӧ�ֿ⵽���� FontList
	 //pInfoCtrl.GetFont(strKey , FontList);	

	int nCheckB = m_Double_CheckB.GetCheck();
	int nCheckC = m_Double_CheckB.GetCheck();
	int nCheckD = m_Double_CheckB.GetCheck();
	int nCheck = nCheckB + nCheckC + nCheckD;	// �ж�ѡ���˼�����ѡ��

	if (nCheck > 1)
	{
		// �����ֿ⡢ɾ���ֿⰴť������
		GetDlgItem(IDC_BUTTON_Add)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Delete)->EnableWindow(FALSE);
	}

	if (nIsCheck == FALSE)	// ԭ��δѡ��,����ѡ�м����ֿ�
	{	
		InserItemFont(strKey);
	}
	if (nIsCheck == TRUE)	// ԭ��ѡ�У�����ȡ��ѡ�У�����Ӧ���ݳ����ֿ�
	{	
		// ��ʱȫ��ɾ��
		m_List_Left.DeleteAllItems();
		m_List_Right.DeleteAllItems();
		UpdateData(FALSE);


	}
	UpdateData(FALSE);
	return;
}

// ��ѡ��ť��ʽ���Ƿ�ѡ��
void CFontManagerDlg::OnBnClickedCheckOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ��ѡ���ѡ��״̬
	int nCheck = m_CheckOne.GetCheck();
	if (nCheck == 0)	// ��ѡ��ť��ʽδѡ��
	{	
		// ���ѡ��
		m_Radio_B.SetCheck(FALSE);
		m_Radio_C.SetCheck(FALSE);
		m_Radio_D.SetCheck(FALSE);
		m_Radio_All.SetCheck(FALSE);
		// ������
		m_Radio_B.EnableWindow(FALSE);
		m_Radio_C.EnableWindow(FALSE);
		m_Radio_D.EnableWindow(FALSE);
		m_Radio_All.EnableWindow(FALSE);
	}
	if (nCheck == 1)	// ��ѡ��ť��ʽ��ѡ��
	{	
		// ����
		m_Radio_B.EnableWindow(TRUE);
		m_Radio_C.EnableWindow(TRUE);
		m_Radio_D.EnableWindow(TRUE);
		m_Radio_All.EnableWindow(TRUE);

	}
	
	UpdateData(FALSE);
	return;
}

// ������ѡ��B
void CFontManagerDlg::OnBnClickedRadioB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ѡ�������֮ǰ������
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();
	UpdateData(FALSE);

	CString strKey ;	//��������
	strKey.Format(_T("B"));
	cFontKey.Format(_T("B"));
	// �ֿ����ݲ����б�
	InserItemFont(strKey);

	//cFontKey ='B';	// ��¼�б����������

	// �����ֿ⡢ɾ���ֿⰴť����
	GetDlgItem(IDC_BUTTON_Add)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Delete)->EnableWindow(TRUE);

	UpdateData(FALSE);
}

// ������ѡ��C
void CFontManagerDlg::OnBnClickedRadioC()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// ������ѡ��D
void CFontManagerDlg::OnBnClickedRadioD()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// ������ѡ��ȫ��
void CFontManagerDlg::OnBnClickedRadioAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ȫѡ�������֮ǰ������
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();
	UpdateData(FALSE);

	CString strKeyB, strKeyC,strKeyD;	//��������
	strKeyB.Format(_T("B"));
	strKeyC.Format(_T("C"));
	strKeyD.Format(_T("D"));
	// �ֿ����ݲ����б�
	InserItemFont(strKeyB);
	InserItemFont(strKeyC);
	InserItemFont(strKeyD);

	// �����ֿ⡢ɾ���ֿⰴť������
	GetDlgItem(IDC_BUTTON_Add)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Delete)->EnableWindow(FALSE);

	UpdateData(FALSE);
}


// ����Left�б��ѡ��
void CFontManagerDlg::OnLvnItemchangedListLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����ԭ�е�����
	//m_strEditFont = '\0';
	UpdateData(FALSE);

	CString strText;
	// ��ȡ�б����ѡ�е�����
	int nItem = m_List_Left.GetSelectionMark();
	// ��ȡ������������
	strText = m_List_Left.GetItemText(nItem, 0);

	// m_List_Left.GetItemData(nItem);
	// ��������ӵ��༭��
	m_strEditFont = strText;
	//SetDlgItemText(IDC_EDIT_Font, strText);

	UpdateData(FALSE);
	*pResult = 0;
}

// �����ֿⰴť
void CFontManagerDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_strEditFont.GetLength() == 0)
	{
		MessageBox(TEXT("�༭������Ϊ�գ���"));
		return;
	}

	// �б������
	/*int nItem = m_List_Left.GetItemCount();*/
	// �¼ӵ����ݲ���ĩβ
	//m_List_Left.InsertItem((nItem+1), m_strEditFont);

	 if (pInfoCtrl.FindFont(strFontkey, m_strEditFont) == TRUE)
	 {
		 MessageBox(TEXT("��ӵ������Ѵ��ڣ���"));
	 }
	 else
	 {
		 pInfoCtrl.AddFont(strFontkey[0], m_strEditFont);
	 }

	 // ˢ����Ӻ���б��
	 LoadListCtrl();
	UpdateData(FALSE);
}

// ɾ���ֿⰴť
void CFontManagerDlg::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_strEditFont.GetLength() == FALSE)
	{
		MessageBox(TEXT("�༭������Ϊ�գ���"));
	}
	// �����б�����Ƿ����Ҫɾ��������
	if (pInfoCtrl.FindFont(strFontkey, m_strEditFont) == FALSE)
	{
		MessageBox(TEXT("Ҫɾ�������ݲ����ڣ���"));
	}
	else
	{
		pInfoCtrl.DeleFont(strFontkey, m_strEditFont);
	}
	// ˢ��ɾ������б�
	LoadListCtrl();
	UpdateData(FALSE);

	// ɾ��ѡ����
	// ��ȡ�б����ѡ�е�����
	//int nItem = m_List_Left.GetSelectionMark();
	//m_List_Left.DeleteItem(nItem);

}

// �����ɾ��������ˢ���б��
void CFontManagerDlg::LoadListCtrl()
{
	// ˢ��ǰ�����֮ǰ������
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();

	std::vector<CString> FontList;	//��������

	// ��ȡ��Ӧ�ֿ⵽���� FontList
	pInfoCtrl.GetFont(strFontkey[0] , FontList);	
	int nSize = FontList.size();	// �ж��ֿ��С
	if (nSize == 0)
	{
		MessageBox(_T("���ֿ������ݣ�����"));
		return;
	}
	// ���ֿ����ݵ�ǰ15���������
	for (int i = 0; i < 15; i++)
	{
		m_List_Left.InsertItem(i, FontList.at(i));	
	}
	if (nSize >= 15)	// ������15������ʣ�����ݲ��뵽�ұ�
	{
		for (int i = 0; i < nSize; i++)
		{
			m_List_Right.InsertItem(i, FontList.at(i));
		}
	}

	// ���水ťΪ��
	GetDlgItem(IDC_BUTTON_Save)->EnableWindow(TRUE);

	UpdateData(FALSE);	//	ˢ���б��

	isOK = false;	// ��¼�޸�
	return;
}

// ���水ť
void CFontManagerDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ѵ�ǰ���ݣ�����B��C��D������ziku.txt�ļ�
	pInfoCtrl.saveFont();
	isOK = true;	// ��¼����

	// �水ťΪ��
	GetDlgItem(IDC_BUTTON_Save)->EnableWindow(FALSE);
}

// ȡ����ť
void CFontManagerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ж��Ƿ񱣴�
	if (isOK == false)
	{
		CMyIsExit Dlg;
		Dlg.DoModal();
	}
	else{ CDialogEx::OnCancel();}

}
