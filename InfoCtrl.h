#pragma once

#include <cstringt.h>
#include <vector>


#include "Data.h"

class CInfoCtrl
{
public:
	CInfoCtrl(void);
	~CInfoCtrl(void);
	
public:
	//�������B\C\D ��Ȼ��Ѷ�Ӧ������д�봫�������
	void GetFont(char strKey, std::vector<CString>& FontList);
	
	// �����ֿ�����B\C\D,���¼����ַ���strAdd�����仯���������������
	void AddFont(char cFontKey , CString strAdd);

	// �����ֿ�����B\C\D  strFind�� ����strFind �Ƿ����
	// ����ɾ�������棬��Ϊ��
	BOOL FindDeleFont(CString cFontKey, CString strFind);

	//  ����strFind �Ƿ����
	BOOL FindFont(CString strkey, CString strFind);

	// ����ɾ�������棬��Ϊ��
	BOOL DeleFont(CString strkey, CString strFind);

	// ���棬����ǰ���ж��ֿ�������û�з����仯
	// δ�仯����false�� �����仯���ر��沢����true
	BOOL saveFont();

	
private:
	//����
private:
	CData m_cData;
};

