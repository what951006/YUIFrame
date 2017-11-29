#include "stdafx.h"
#include "YButton.h"
#include "YPainter.h"
#include "YMessageBox.h"

YButton::YButton(YUIObject*obj)
	:YUIObject(obj)
{

}


YButton::~YButton(void)
{

}
void YButton::DrawWindow(HDC &dc)
{
	YUIObject::DrawWindow(dc);
	YPainter p(dc,this);
	Pen pen(Color( 0,0,0));
	p.SetPen(pen);
	
	p.DrawLine(0,0,m_re.width,0);
	p.DrawLine(m_re.width,0,m_re.width,m_re.height);
	p.DrawLine(m_re.width,m_re.height,0,m_re.height);
	p.DrawLine(0,m_re.height,0,0);
}

void YButton::OnMouseDown(const YPoint pt)
{
	YMessageBox::Show(this);
}
void YButton::OnMouseUp(const YPoint pt)
{

}
void YButton::OnMouseMove(const YPoint pos)
{
	char buf[128]={0};
	sprintf_s(buf,"MainWindows :  x:%d , y:%d",pos.x,pos.y);

	SetWindowTextA(this->GetHwnd(),buf);
}