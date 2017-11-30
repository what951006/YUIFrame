#include "stdafx.h"
#include "YPainter.h"
#include "YUIObject.h"


YPainter::YPainter(HDC&dc,YUIObject*pParent)
	:m_dc(dc)
	,m_pParent(pParent)
	,m_pPen(NULL)
	,m_graphic(dc)
{
	m_re=pParent->GetGeometryFromMain();
	
}
	


YPainter::~YPainter(void)
{
	delete m_pPen;
}

void YPainter::DrawLine(int x,int y,int x2,int y2)
{
	m_graphic.DrawLine(m_pPen,m_re.x+x,m_re.y+y,m_re.x+x2,m_re.y+y2);
	/*
	MoveToEx(m_dc, m_re.x+x, m_re.y+y, NULL);
	LineTo(m_dc,m_re.x+x2,m_re.y+y2);
*/
}

void YPainter::DrawImage(Image &image,int x,int y,int w,int h)
{
	m_graphic.SetInterpolationMode(Gdiplus::InterpolationModeDefault); 
	m_graphic.DrawImage(&image, m_re.x+x,m_re.y+y,w,h); 

}

void YPainter::FillRect(const SolidBrush&br,int x,int y,int w,int h)
{
	m_graphic.FillRectangle(&br,m_re.x+x,m_re.y+y,m_re.width+w,m_re.height+h);

}

void YPainter::FillRect(const SolidBrush&br,const YRect &re)
{
	m_graphic.FillRectangle(&br,m_re.x+re.x,m_re.y+re.y,m_re.width+re.width,m_re.height+re.height);
}
