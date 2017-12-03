#pragma once

/**************************************************
@brief:push button
@file:YButton.h
@version:1.0
@company:casino
@author:yantao
@email:what951006@163.com
@time:2017-11-25 13:56:51
**************************************************/
#include "YUIObject.h"

class YButton :public YUIObject
{
public:
	YButton(const string &str,YUIObject*obj);

	~YButton(void);

	void SetText(const string &str);
	virtual void DrawWindow(HDC dc);
protected:

	virtual void OnMouseLClicked();
	
	string m_strText;
};

