
// FontManagerDlg.cpp : 实现文件
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
// 用于记录列表框显示内容的Key
CString strFontkey;
//定义bool 类型isOK，用于判断是否点击了保存，修改数据后为false，保存过为true
bool isOK = true;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CFontManagerDlg 对话框




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

	ON_BN_CLICKED(IDC_BUTTON_B, &CFontManagerDlg::OnBnClickedButtonB)	// 单击按钮
	ON_BN_CLICKED(IDC_BUTTON_C, &CFontManagerDlg::OnBnClickedButtonC)	
	ON_BN_CLICKED(IDC_BUTTON_D, &CFontManagerDlg::OnBnClickedButtonD)

	ON_CBN_SELCHANGE(IDC_COMBO_Font, &CFontManagerDlg::OnCbnSelchangeComboFont)	// 下拉框的更改
	ON_BN_CLICKED(IDC_CHECK_Double, &CFontManagerDlg::OnBnClickedCheckDouble)	// 复选框方式

	ON_BN_CLICKED(IDC_CHECK_B, &CFontManagerDlg::OnBnClickedCheckB)	// 复选框 B
	ON_BN_CLICKED(IDC_CHECK_C, &CFontManagerDlg::OnBnClickedCheckC)	// 复选框 C
	ON_BN_CLICKED(IDC_CHECK_D, &CFontManagerDlg::OnBnClickedCheckD)	// 复选框 D

	ON_BN_CLICKED(IDC_CHECK_One, &CFontManagerDlg::OnBnClickedCheckOne)	// 单选框按钮方式
	ON_BN_CLICKED(IDC_RADIO_B, &CFontManagerDlg::OnBnClickedRadioB)		// 单击单选框B
	ON_BN_CLICKED(IDC_RADIO_C, &CFontManagerDlg::OnBnClickedRadioC)
	ON_BN_CLICKED(IDC_RADIO_D, &CFontManagerDlg::OnBnClickedRadioD)
	ON_BN_CLICKED(IDC_RADIO_All, &CFontManagerDlg::OnBnClickedRadioAll)	// 单击单选框 全部

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_Left, &CFontManagerDlg::OnLvnItemchangedListLeft)	// 更改列表框选项
	ON_BN_CLICKED(IDC_BUTTON_Add, &CFontManagerDlg::OnBnClickedButtonAdd)	// 加入字库按钮
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CFontManagerDlg::OnBnClickedButtonDelete)	// 删除字库按钮
	ON_BN_CLICKED(IDC_BUTTON_Save, &CFontManagerDlg::OnBnClickedButtonSave)	// 保存按钮
	ON_BN_CLICKED(IDCANCEL, &CFontManagerDlg::OnBnClickedCancel)	// 取消按钮
END_MESSAGE_MAP()


// CFontManagerDlg 消息处理程序

BOOL CFontManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// staAppData.ReadzikuTxt();

	// 复选框初始不可用
	m_Double_CheckB.EnableWindow(FALSE);
	m_Double_CheckC.EnableWindow(FALSE);
	m_Double_CheckD.EnableWindow(FALSE);

	// 单选初始不可用，无默认选项
	m_Radio_B.EnableWindow(FALSE);
	m_Radio_C.EnableWindow(FALSE);
	m_Radio_D.EnableWindow(FALSE);
	m_Radio_All.EnableWindow(FALSE);

	// 初始显示 B 类字库
	strFontkey.Format(_T("B"));
	OnBnClickedButtonB();

	// 初始默认保存按钮为灰
	GetDlgItem(IDC_BUTTON_Save)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFontManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFontManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 字库内容插入列表
void CFontManagerDlg::InserItemFont(CString strKey)
{
	// 先判断列表是否有内容
	int nItem = m_List_Left.GetItemCount();	// 列表中数据的数量
	int nSize = 0;
	std::vector<CString> FontList;	//声明容器
	//FontList pfontList;
	// 提取对应字库到容器 FontList
	

	pInfoCtrl.GetFont(strKey[0], FontList);	
	nSize = FontList.size();	// 判断字库大小
	if (nSize == 0)
	{
		MessageBox(_T("该字库无内容！！！"));
		return;
	}
	if ( nItem != 0)
	{
		// nSize += nItem;

		// 将字库内容插入后面
		if (nItem < 15)	// 原先内容小于15
		{
			for (int i = nItem; i < 15; i++)	// 先插满15
			{
				int j = 0;
				m_List_Left.InsertItem(i, FontList.at(j));	
				j++;
			}
			for (int i = 0; i < (nSize-nItem); i++)	// 再将剩余的插入右侧
			{
				int j = 15 - nItem;
				m_List_Right.InsertItem(i, FontList.at(j));
				j++;
			}
		}
		
		if (nItem >= 15)	// 若大于15个，把剩余内容插入到右边
		{
			for (int i = (nItem-15); i < nSize; i++)
			{
				int j = 0;
				m_List_Right.InsertItem(i, FontList.at(j));
				j++;
			}
		}
	}
	

	// 如果列表框无内容，将字库内容的前15个插入左边
	if (nSize < 15)
	{
		for (int i = 0; i < nSize; i++)
		{
			m_List_Left.InsertItem(i, FontList.at(i));	
		}
	}
	
	if (nSize >= 15)	// 若大于15个，前15个插入左边,剩余内容插入到右边
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

	UpdateData(FALSE);	//	刷新列表框
	return;
}

// 单击B按钮
void CFontManagerDlg::OnBnClickedButtonB()
{
	// TODO: 在此添加控件通知处理程序代码

	// 暂时全部删除
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();
	UpdateData(FALSE);

	CString strKey ;	//声明索引
	strKey.Format(_T("B"));
	// 字库内容插入列表
	InserItemFont(strKey);

	// 复选框方式、单选按钮方式均设置为未选择状态
	m_CheckDouble.SetCheck(0);
	m_CheckOne.SetCheck(0);
	OnBnClickedCheckDouble();

	strFontkey = strKey;	// 记录列表框数据名称

	UpdateData(FALSE);
}

// 单击C按钮
void CFontManagerDlg::OnBnClickedButtonC()
{
	// TODO: 在此添加控件通知处理程序代码
	// 暂时全部删除
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();

	CString strKey ;	//声明索引
	strKey.Format(_T("C"));

	// 字库内容插入列表
	InserItemFont(strKey);

	// 复选框方式、单选按钮方式均设置为未选择状态
	m_CheckDouble.SetCheck(0);
	m_CheckOne.SetCheck(0);

	OnBnClickedCheckDouble();

	strFontkey = strKey;	// 记录列表框数据名称

	UpdateData(FALSE);
}

// 单击D按钮
void CFontManagerDlg::OnBnClickedButtonD()
{
	// TODO: 在此添加控件通知处理程序代码
	// 暂时全部删除
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();

	CString strKey ;	//声明索引
	strKey.Format(_T("D"));

	// 字库内容插入列表
	InserItemFont(strKey);

	// 复选框方式、单选按钮方式均设置为未选择状态
	m_CheckDouble.SetCheck(0);
	m_CheckOne.SetCheck(0);
	OnBnClickedCheckDouble();

	strFontkey = strKey;	// 记录列表框数据名称

	UpdateData(FALSE);
}

// 下拉框的更改
void CFontManagerDlg::OnCbnSelchangeComboFont()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	// 获取下拉框选中的哪一项
	int nChoice = m_Combo_Font.GetCurSel();

	// 选“ 空 ” 时，
	if ( nChoice == 0)
	{
		// 清空左右列表框
		m_List_Left.DeleteAllItems();
		m_List_Right.DeleteAllItems();
	}
	// 选 B 时对应显示右边列表框
	if ( nChoice == 1)
	{
		OnBnClickedButtonB();
	}
	// 选 C 时对应显示右边列表框
	if ( nChoice == 2)
	{
		OnBnClickedButtonC();
	}
	// 选 D 时对应显示右边列表框
	if ( nChoice == 3)
	{
		OnBnClickedButtonD();
	}
}

// 复选框方式
void CFontManagerDlg::OnBnClickedCheckDouble()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取复选框的选中状态
	int nCheck = m_CheckDouble.GetCheck();
	if (nCheck == 0)	// 未选中
	{	
		/*CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_B);
		pBtn->SetCheck(0);*/
		// 设置为未选择状态
		m_Double_CheckB.SetCheck(0);
		m_Double_CheckC.SetCheck(0);
		m_Double_CheckD.SetCheck(0);
		// 复选框BCD不可用
		m_Double_CheckB.EnableWindow(FALSE);
		m_Double_CheckC.EnableWindow(FALSE);
		m_Double_CheckD.EnableWindow(FALSE);
		
	}
	if (nCheck == 1)	// 选中
	{	
		// 复选框BCD不可用
		m_Double_CheckB.EnableWindow(TRUE);
		m_Double_CheckC.EnableWindow(TRUE);
		m_Double_CheckD.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	return;
}

// 复选框选项B
void CFontManagerDlg::OnBnClickedCheckB()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey ;	//声明索引
	strKey.Format(_T("B"));
	int nIsCheckB = m_Double_CheckC.GetCheck();

	// 根据复选框状态显示字库
	ISClickedCheck(nIsCheckB, strKey);
}

// 复选框选项C
void CFontManagerDlg::OnBnClickedCheckC()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey ;	//声明索引
	strKey.Format(_T("C"));
	int nIsCheckC = m_Double_CheckC.GetCheck();

}

// 复选框选项D
void CFontManagerDlg::OnBnClickedCheckD()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 根据复选框状态显示字库
void CFontManagerDlg::ISClickedCheck(int nIsCheck, CString strKey)
{
	// 提取对应字库到容器 FontList
	 //pInfoCtrl.GetFont(strKey , FontList);	

	int nCheckB = m_Double_CheckB.GetCheck();
	int nCheckC = m_Double_CheckB.GetCheck();
	int nCheckD = m_Double_CheckB.GetCheck();
	int nCheck = nCheckB + nCheckC + nCheckD;	// 判断选中了几个复选框

	if (nCheck > 1)
	{
		// 加入字库、删除字库按钮不可用
		GetDlgItem(IDC_BUTTON_Add)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Delete)->EnableWindow(FALSE);
	}

	if (nIsCheck == FALSE)	// 原来未选中,单击选中加入字库
	{	
		InserItemFont(strKey);
	}
	if (nIsCheck == TRUE)	// 原来选中，单击取消选中，将对应数据撤出字库
	{	
		// 暂时全部删除
		m_List_Left.DeleteAllItems();
		m_List_Right.DeleteAllItems();
		UpdateData(FALSE);


	}
	UpdateData(FALSE);
	return;
}

// 单选框按钮方式，是否选中
void CFontManagerDlg::OnBnClickedCheckOne()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取复选框的选中状态
	int nCheck = m_CheckOne.GetCheck();
	if (nCheck == 0)	// 单选框按钮方式未选中
	{	
		// 清空选项
		m_Radio_B.SetCheck(FALSE);
		m_Radio_C.SetCheck(FALSE);
		m_Radio_D.SetCheck(FALSE);
		m_Radio_All.SetCheck(FALSE);
		// 不可用
		m_Radio_B.EnableWindow(FALSE);
		m_Radio_C.EnableWindow(FALSE);
		m_Radio_D.EnableWindow(FALSE);
		m_Radio_All.EnableWindow(FALSE);
	}
	if (nCheck == 1)	// 单选框按钮方式被选中
	{	
		// 可用
		m_Radio_B.EnableWindow(TRUE);
		m_Radio_C.EnableWindow(TRUE);
		m_Radio_D.EnableWindow(TRUE);
		m_Radio_All.EnableWindow(TRUE);

	}
	
	UpdateData(FALSE);
	return;
}

// 单击单选框B
void CFontManagerDlg::OnBnClickedRadioB()
{
	// TODO: 在此添加控件通知处理程序代码
	// 单选，先清空之前的内容
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();
	UpdateData(FALSE);

	CString strKey ;	//声明索引
	strKey.Format(_T("B"));
	cFontKey.Format(_T("B"));
	// 字库内容插入列表
	InserItemFont(strKey);

	//cFontKey ='B';	// 记录列表框数据名称

	// 加入字库、删除字库按钮可用
	GetDlgItem(IDC_BUTTON_Add)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Delete)->EnableWindow(TRUE);

	UpdateData(FALSE);
}

// 单击单选框C
void CFontManagerDlg::OnBnClickedRadioC()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 单击单选框D
void CFontManagerDlg::OnBnClickedRadioD()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 单击单选框全部
void CFontManagerDlg::OnBnClickedRadioAll()
{
	// TODO: 在此添加控件通知处理程序代码
	// 全选，先清空之前的内容
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();
	UpdateData(FALSE);

	CString strKeyB, strKeyC,strKeyD;	//声明索引
	strKeyB.Format(_T("B"));
	strKeyC.Format(_T("C"));
	strKeyD.Format(_T("D"));
	// 字库内容插入列表
	InserItemFont(strKeyB);
	InserItemFont(strKeyC);
	InserItemFont(strKeyD);

	// 加入字库、删除字库按钮不可用
	GetDlgItem(IDC_BUTTON_Add)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Delete)->EnableWindow(FALSE);

	UpdateData(FALSE);
}


// 更改Left列表框选项
void CFontManagerDlg::OnLvnItemchangedListLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	// 先清空原有的内容
	//m_strEditFont = '\0';
	UpdateData(FALSE);

	CString strText;
	// 获取列表框中选中的索引
	int nItem = m_List_Left.GetSelectionMark();
	// 获取该索引的内容
	strText = m_List_Left.GetItemText(nItem, 0);

	// m_List_Left.GetItemData(nItem);
	// 将内容添加到编辑框
	m_strEditFont = strText;
	//SetDlgItemText(IDC_EDIT_Font, strText);

	UpdateData(FALSE);
	*pResult = 0;
}

// 加入字库按钮
void CFontManagerDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_strEditFont.GetLength() == 0)
	{
		MessageBox(TEXT("编辑框内容为空！！"));
		return;
	}

	// 列表框总数
	/*int nItem = m_List_Left.GetItemCount();*/
	// 新加的内容插入末尾
	//m_List_Left.InsertItem((nItem+1), m_strEditFont);

	 if (pInfoCtrl.FindFont(strFontkey, m_strEditFont) == TRUE)
	 {
		 MessageBox(TEXT("添加的内容已存在！！"));
	 }
	 else
	 {
		 pInfoCtrl.AddFont(strFontkey[0], m_strEditFont);
	 }

	 // 刷新添加后的列表框
	 LoadListCtrl();
	UpdateData(FALSE);
}

// 删除字库按钮
void CFontManagerDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_strEditFont.GetLength() == FALSE)
	{
		MessageBox(TEXT("编辑框内容为空！！"));
	}
	// 检索列表框中是否存在要删除的内容
	if (pInfoCtrl.FindFont(strFontkey, m_strEditFont) == FALSE)
	{
		MessageBox(TEXT("要删除的内容不存在！！"));
	}
	else
	{
		pInfoCtrl.DeleFont(strFontkey, m_strEditFont);
	}
	// 刷新删除后的列表
	LoadListCtrl();
	UpdateData(FALSE);

	// 删除选中行
	// 获取列表框中选中的索引
	//int nItem = m_List_Left.GetSelectionMark();
	//m_List_Left.DeleteItem(nItem);

}

// 加入或删除后重新刷新列表框
void CFontManagerDlg::LoadListCtrl()
{
	// 刷新前先清空之前的内容
	m_List_Left.DeleteAllItems();
	m_List_Right.DeleteAllItems();

	std::vector<CString> FontList;	//声明容器

	// 提取对应字库到容器 FontList
	pInfoCtrl.GetFont(strFontkey[0] , FontList);	
	int nSize = FontList.size();	// 判断字库大小
	if (nSize == 0)
	{
		MessageBox(_T("该字库无内容！！！"));
		return;
	}
	// 将字库内容的前15个插入左边
	for (int i = 0; i < 15; i++)
	{
		m_List_Left.InsertItem(i, FontList.at(i));	
	}
	if (nSize >= 15)	// 若大于15个，把剩余内容插入到右边
	{
		for (int i = 0; i < nSize; i++)
		{
			m_List_Right.InsertItem(i, FontList.at(i));
		}
	}

	// 保存按钮为亮
	GetDlgItem(IDC_BUTTON_Save)->EnableWindow(TRUE);

	UpdateData(FALSE);	//	刷新列表框

	isOK = false;	// 记录修改
	return;
}

// 保存按钮
void CFontManagerDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	// 把当前内容（包括B、C、D）存入ziku.txt文件
	pInfoCtrl.saveFont();
	isOK = true;	// 记录保存

	// 存按钮为灰
	GetDlgItem(IDC_BUTTON_Save)->EnableWindow(FALSE);
}

// 取消按钮
void CFontManagerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断是否保存
	if (isOK == false)
	{
		CMyIsExit Dlg;
		Dlg.DoModal();
	}
	else{ CDialogEx::OnCancel();}

}
