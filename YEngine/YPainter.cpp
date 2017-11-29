#include "stdafx.h"
#include "YPainter.h"
#include "YUIObject.h"


YPainter::YPainter(HDC&dc,YUIObject*pParent)
	:m_dc(dc)
	,m_pParent(pParent)
{

}
	


YPainter::~YPainter(void)
{
	ReleaseDC(m_pParent->GetHwnd(),m_memDC);
}

void YPainter::DrawLine(int x,int y,int x2,int y2)
{
	Pen pen(Color(200,200,0));
	Graphics gr(m_dc);
	gr.DrawLine(&pen,x,y,x2,y2);


}

void YPainter::FillRect(const SolidBrush&br,int x,int y,int w,int h)
{
	//SolidBrush br(Color(240,240,240,255));
	Graphics gr(m_dc);
	gr.FillRectangle(&br,x,y,w,h);

}

void YPainter::FillRect(const SolidBrush&br,const YRect &re)
{
	Graphics gr(m_dc);
	gr.FillRectangle(&br,re.x,re.y,re.width,re.height);
}
