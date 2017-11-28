#pragma once

/**************************************************
@brief:messagebox,like the windows original messagebox
@file:
@version:
@company:
@author:
@email:
@time:
**************************************************/

#include "YUIObject.h"



enum YMB_TYPE
	{
		YMB_OK,
		YMB_YES,
		YMB_CANCEL,
		YMB_NO
};

class YMessageBox :public YUIObject
{
	

public:
	static YMB_TYPE Show(YUIObject*pParent);
protected:
	YMessageBox(void);
	~YMessageBox(void);


};

