#include "StdAfx.h"
#include "InfoCtrl.h"


CInfoCtrl::CInfoCtrl(void)
{
	//在信息控制类的构造函数中进行数据对象的初始化
	m_cData.ReadFile();
}


CInfoCtrl::~CInfoCtrl(void)
{
}

void CInfoCtrl::GetFont(char strKey, std::vector<CString>& FontList)
{
	//直接用数据类对象的方法来完成需求，将strKey对应的所有数据放入容器FontList中
	FontList = m_cData.GetAll(strKey);
	return;
}

void CInfoCtrl::AddFont(char cFontKey , CString strAdd)
{
	m_cData.Insert(strAdd, cFontKey);
}

BOOL CInfoCtrl::FindDeleFont(CString cFontKey, CString strFind)
{
	if (m_cData.Del(strFind, cFontKey[0]))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CInfoCtrl::FindFont(CString strkey, CString strFind)
{
	int tIndex = m_cData.FindTypePos(strkey[0]);
	if (tIndex < 0)
	{
		return FALSE;
	}
	if (m_cData.FindNamePos(strFind, tIndex) >= 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CInfoCtrl::DeleFont(CString strkey, CString strFind)
{
	if (m_cData.Del(strFind, strkey[0]))
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CInfoCtrl::saveFont()
{
	if(m_cData.WriteFile())
	{
		return TRUE;
	}
	return FALSE;
}
