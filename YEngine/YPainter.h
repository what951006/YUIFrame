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
#include "YFont.h"
class YPainter
{
public:
	YPainter(HDC &dc,YUIObject*pParent);

	~YPainter(void);

	void SetPen(const Pen& pen){ if(m_pPen) delete m_pPen;m_pPen = pen.Clone();}

	void SetFont(const YFont &font);

	void SetTransparent(int value);

	YFont& GetFont(){return *m_pFont;}

	void SetFontColor(int r, int g ,int b);

	void DrawLine(int x,int y,int x2,int y2);

	void DrawImage(Image &image,int x,int y,int w,int h);

	void FillRect(const SolidBrush&br,int x,int y,int w,int h);

	void FillRect(const SolidBrush&br,const YRect &re);

	void DrawText(const string &str,int x, int y);

	HDC GetMemDC(){return m_memDC;}

private:
	
	HDC m_dc;
	HDC m_memDC;
	Pen *m_pPen;
	Graphics *m_pGraphic;
	YUIObject *m_pParent;
	YFont *m_pFont;
	HBITMAP m_bitmap;
	int m_tranValue;
};

