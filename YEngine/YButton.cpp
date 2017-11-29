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

	YRect re=this->GetGeometryFromMain();
	int x=re.x;
	int y=re.y;
	int w=re.width;
	int h=re.height;
	
	p.DrawLine(x,y,x+w,y);
	p.DrawLine(x+w,y,x+w,h+y);
	p.DrawLine(x+w,h+y,x,h+y);
	p.DrawLine(x,h+y,x,y);
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