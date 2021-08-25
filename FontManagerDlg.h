
// FontManagerDlg.h : 头文件
//

#pragma once
#include "AppData.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "InfoCtrl.h"
#include "resource.h"
// CFontManagerDlg 对话框
class CFontManagerDlg : public CDialogEx
{
// 构造
public:
	CFontManagerDlg(CWnd* pParent = NULL);	// 标准构造函数


	
	

// 对话框数据
	enum { IDD = IDD_FONTMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:

	CString cFontKey;	// 记录列表框数据名称

	// 类对象声明
	CInfoCtrl pInfoCtrl;	// 控制类对象
	//std::vector<CString> FontList;	//声明容器

	// 控件变量
	CButton m_Button_B;		// 按钮 B
	CButton m_Button_C;
	CButton m_Button_D;		// 按钮 D

	CComboBox m_Combo_Font;	// 下拉列表
	CListCtrl m_List_Left;	// 左边列表
	CListCtrl m_List_Right;	// 右边列表

	CButton m_CheckDouble;	// 复选框方式
	CButton m_CheckOne;		// 单选按钮方式

	CButton m_Double_CheckB;	// 复选框，B、C、D组
	CButton m_Double_CheckC;
	CButton m_Double_CheckD;

	CButton m_Radio_B;		// 单选按钮B、C、D、All控件
	CButton m_Radio_C;
	CButton	m_Radio_D;
	CButton	m_Radio_All;

	CEdit m_EditFont;	// 编辑框
	CString m_strEditFont;	// 编辑框内容


	// 将字库插入列表框
	afx_msg void InserItemFont(CString strKey);

	// 单击B、C、D按钮事件
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonD();

	// 下拉框的更改
	afx_msg void OnCbnSelchangeComboFont();

	// 单击复选框方式
	afx_msg void OnBnClickedCheckDouble();

	// 单击复选框选项BCD
	afx_msg void OnBnClickedCheckB();
	afx_msg void OnBnClickedCheckC();
	afx_msg void OnBnClickedCheckD();
	// 根据复选框转态显示字库
	afx_msg void ISClickedCheck(int nIsCheck, CString strKey);

	// 单击单选框按钮方式
	afx_msg void OnBnClickedCheckOne();
	// 单击单选框B
	afx_msg void OnBnClickedRadioB();
	afx_msg void OnBnClickedRadioC();
	afx_msg void OnBnClickedRadioD();
	afx_msg void OnBnClickedRadioAll();

	// 更改列表框选项
	afx_msg void OnLvnItemchangedListLeft(NMHDR *pNMHDR, LRESULT *pResult);
	
	// 加入字库按钮
	afx_msg void OnBnClickedButtonAdd();
	// 删除字库按钮
	afx_msg void OnBnClickedButtonDelete();
	// 加入或删除后重新刷新列表框
	afx_msg void LoadListCtrl();
	// 保存按钮
	afx_msg void OnBnClickedButtonSave();
	// 取消按钮
	afx_msg void OnBnClickedCancel();
};
