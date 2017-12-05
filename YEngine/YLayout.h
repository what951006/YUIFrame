#pragma once
/**************************************************
@brief: the base layout class for widget
@file:Layout.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-12-05 12:47:37
**************************************************/
#include "YObject.h"
#include "YUIObject.h"

class YLayout :public YObject
{
public:
	YLayout(YUIObject*parent);

	~YLayout(void);


	list<YUIObject*> m_list;
};

