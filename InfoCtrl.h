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
	//传入参数B\C\D ，然后把对应的文字写入传入的容器
	void GetFont(char strKey, std::vector<CString>& FontList);
	
	// 传入字库名称B\C\D,和新加入字符串strAdd，将变化更新至数据类对象
	void AddFont(char cFontKey , CString strAdd);

	// 传入字库名称B\C\D  strFind， 查找strFind 是否存在
	// 存在删除返回真，否为假
	BOOL FindDeleFont(CString cFontKey, CString strFind);

	//  查找strFind 是否存在
	BOOL FindFont(CString strkey, CString strFind);

	// 存在删除返回真，否为假
	BOOL DeleFont(CString strkey, CString strFind);

	// 保存，保存前先判断字库数据有没有发生变化
	// 未变化返回false； 发生变化返回保存并返回true
	BOOL saveFont();

	
private:
	//更新
private:
	CData m_cData;
};

