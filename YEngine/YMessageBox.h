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

#include "YDialog.h"
#include "YButton.h"


enum YMB_TYPE
	{
		YMB_OK,
		YMB_YES,
		YMB_CANCEL,
		YMB_NO
};

class YMessageBox :public YDialog
{
	

public:
	static YMB_TYPE Show(YUIObject*pParent);

protected:
	YMessageBox(YUIObject*pParent);
	~YMessageBox(void);

	virtual bool OnEventOccoured(EventObject obj);


	YButton *m_btn;
};

