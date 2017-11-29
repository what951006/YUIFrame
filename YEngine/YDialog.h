#pragma once

/**************************************************
@brief:Dialog window!modal
@file:YDialog.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-29 10:18:47
**************************************************/

#include "YUIObject.h"
class YDialog :
	public YUIObject
{
public:
	YDialog(HWND hd);
	
	~YDialog(void);

	void YRegisterClass();

	void InitInstance(LPCWSTR classname,LPCWSTR title);

	int Modal();

	LPCWSTR GetYClassName(){return _T(YDLG_CLA_NAME);}


private:
	HWND m_Parhwnd;//parent's hwnd
};

