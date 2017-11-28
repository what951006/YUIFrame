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

void YPainter::FillRect(int x,int y,int x2,int y2)
{
	
}

void YPainter::FillRect(const YRect &re)
{

}
