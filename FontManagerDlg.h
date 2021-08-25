
// FontManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "AppData.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "InfoCtrl.h"
#include "resource.h"
// CFontManagerDlg �Ի���
class CFontManagerDlg : public CDialogEx
{
// ����
public:
	CFontManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��


	
	

// �Ի�������
	enum { IDD = IDD_FONTMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:

	CString cFontKey;	// ��¼�б����������

	// ���������
	CInfoCtrl pInfoCtrl;	// ���������
	//std::vector<CString> FontList;	//��������

	// �ؼ�����
	CButton m_Button_B;		// ��ť B
	CButton m_Button_C;
	CButton m_Button_D;		// ��ť D

	CComboBox m_Combo_Font;	// �����б�
	CListCtrl m_List_Left;	// ����б�
	CListCtrl m_List_Right;	// �ұ��б�

	CButton m_CheckDouble;	// ��ѡ��ʽ
	CButton m_CheckOne;		// ��ѡ��ť��ʽ

	CButton m_Double_CheckB;	// ��ѡ��B��C��D��
	CButton m_Double_CheckC;
	CButton m_Double_CheckD;

	CButton m_Radio_B;		// ��ѡ��ťB��C��D��All�ؼ�
	CButton m_Radio_C;
	CButton	m_Radio_D;
	CButton	m_Radio_All;

	CEdit m_EditFont;	// �༭��
	CString m_strEditFont;	// �༭������


	// ���ֿ�����б��
	afx_msg void InserItemFont(CString strKey);

	// ����B��C��D��ť�¼�
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonD();

	// ������ĸ���
	afx_msg void OnCbnSelchangeComboFont();

	// ������ѡ��ʽ
	afx_msg void OnBnClickedCheckDouble();

	// ������ѡ��ѡ��BCD
	afx_msg void OnBnClickedCheckB();
	afx_msg void OnBnClickedCheckC();
	afx_msg void OnBnClickedCheckD();
	// ���ݸ�ѡ��ת̬��ʾ�ֿ�
	afx_msg void ISClickedCheck(int nIsCheck, CString strKey);

	// ������ѡ��ť��ʽ
	afx_msg void OnBnClickedCheckOne();
	// ������ѡ��B
	afx_msg void OnBnClickedRadioB();
	afx_msg void OnBnClickedRadioC();
	afx_msg void OnBnClickedRadioD();
	afx_msg void OnBnClickedRadioAll();

	// �����б��ѡ��
	afx_msg void OnLvnItemchangedListLeft(NMHDR *pNMHDR, LRESULT *pResult);
	
	// �����ֿⰴť
	afx_msg void OnBnClickedButtonAdd();
	// ɾ���ֿⰴť
	afx_msg void OnBnClickedButtonDelete();
	// �����ɾ��������ˢ���б��
	afx_msg void LoadListCtrl();
	// ���水ť
	afx_msg void OnBnClickedButtonSave();
	// ȡ����ť
	afx_msg void OnBnClickedCancel();
};
