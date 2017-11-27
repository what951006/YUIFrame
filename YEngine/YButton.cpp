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

	int x=GetGeometry().x;
	int y=GetGeometry().y;
	int w=GetGeometry().width;
	int h=GetGeometry().height;

	YObject*parent=this;
	while(parent =parent->GetParent())
	{
		YUIObject * p=dynamic_cast<YUIObject*>(parent);
		if(p && !p->IsWindow())
		{
			x += p->GetGeometry().x;
			y +=p->GetGeometry().y;
		}
	}


	YPainter p(this);
	
	p.DrawLine(x,y,x+w,y);
	p.DrawLine(x+w,y,x+w,h+y);
	p.DrawLine(x+w,h+y,x,h+y);
	p.DrawLine(x,h+y,x,y);

	
}

void YButton::OnMouseDown(const YPoint pt)
{
	
}
void YButton::OnMouseUp(const YPoint pt)
{

}
void YButton::OnMouseMove(const YPoint pt)
{
		
}