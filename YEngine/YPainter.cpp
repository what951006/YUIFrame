#include "stdafx.h"
#include "YPainter.h"
#include "YUIObject.h"


YPainter::YPainter(HDC&dc,YUIObject*pParent)
	:m_dc(dc)
	,m_pParent(pParent)
	,m_pPen(NULL)
{
	m_re=pParent->GetGeometryFromMain();
}
	


YPainter::~YPainter(void)
{

}

void YPainter::DrawLine(int x,int y,int x2,int y2)
{
	Graphics gr(m_dc);
	gr.DrawLine(m_pPen,m_re.x+x,m_re.y+y,m_re.x+x2,m_re.y+y2);


}

void YPainter::FillRect(const SolidBrush&br,int x,int y,int w,int h)
{
	//SolidBrush br(Color(240,240,240,255));
	Graphics gr(m_dc);
	gr.FillRectangle(&br,m_re.x+x,m_re.y+y,m_re.width+w,m_re.height+h);

}

void YPainter::FillRect(const SolidBrush&br,const YRect &re)
{
	Graphics gr(m_dc);
	gr.FillRectangle(&br,m_re.x+re.x,m_re.y+re.y,m_re.width+re.width,m_re.height+re.height);
}
