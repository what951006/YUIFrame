#pragma once

/**************************************************
@brief:Ymessagebox,like the windows ordinary messagebox
@file:YMessage.h
@version:1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-12-02 14:17:39
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

	virtual bool OnEventOccoured(EventObject &obj);


	YButton *m_btn;
};

