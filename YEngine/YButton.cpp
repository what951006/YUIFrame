#include "stdafx.h"
#include "YButton.h"
#include "YPainter.h"


YButton::YButton(YUIObject*obj)
	:YUIObject(obj)
{

}


YButton::~YButton(void)
{

}
void YButton::DrawWindow()
{
	YUIObject::DrawWindow();
	YRect re=this->GetGeometryFromMain();

	int x=re.x;
	int y=re.y;
	int w=re.width;
	int h=re.height;

	
	
	


	YPainter p(this);
	
	p.DrawLine(x,y,x+w,y);
	p.DrawLine(x+w,y,x+w,h+y);
	p.DrawLine(x+w,h+y,x,h+y);
	p.DrawLine(x,h+y,x,y);

	
}

void YButton::OnMouseDown(const YPoint pt)
{
	char buf[128]={0};
	sprintf(buf,"PushButton down:  x:%d , y:%d",pt.x,pt.y);
	MessageBoxA(NULL,buf,"Hello",NULL);
}
void YButton::OnMouseUp(const YPoint pt)
{

}
void YButton::OnMouseMove(const YPoint pt)
{
		
}