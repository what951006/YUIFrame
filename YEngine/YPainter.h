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

#include "YUIObject.h"

class YPainter
{
public:
	YPainter(HDC &dc,YUIObject*pParent);

	~YPainter(void);

	void DrawLine(int x,int y,int x2,int y2);

	void DrawImage();

	void FillRect(int x,int y,int w,int h);

	void FillRect(const YRect &re);

	HDC m_dc;
	HDC m_memDC;
	HBITMAP m_hbitmap;
	YUIObject *m_pParent;
};

