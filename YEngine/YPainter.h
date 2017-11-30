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

	void SetPen(const Pen& pen){ if(m_pPen) delete m_pPen;m_pPen = pen.Clone();}

	void DrawLine(int x,int y,int x2,int y2);

	void DrawImage(Image &image,int x,int y,int w,int h);

	void FillRect(const SolidBrush&br,int x,int y,int w,int h);

	void FillRect(const SolidBrush&br,const YRect &re);

//private:

	YRect m_re;
	HDC m_dc;
	Pen *m_pPen;
	Graphics m_graphic;
	YUIObject *m_pParent;
};

