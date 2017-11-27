#pragma once

/**************************************************
@brief:painter calss ,graphic stuff
@file:YPainter.h
@version:1.0
@company:casino
@author:yantao
@email:what951006@163.com
@time:2017-11-25 14:32:37
**************************************************/

#include "YObject.h"

class YPainter :public YObject
{
public:
	YPainter(YObject*pParent);

	~YPainter(void);

	void DrawLine(int x,int y,int x2,int y2);

	void DrawImage();
};

