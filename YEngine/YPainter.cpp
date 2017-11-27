#include "stdafx.h"
#include "YPainter.h"
#include "YUIObject.h"


YPainter::YPainter(YObject*pParent)
	:YObject(pParent)
{

}


YPainter::~YPainter(void)
{

}

void YPainter::DrawLine(int x,int y,int x2,int y2)
{
	if(GetParent())
	{
		YUIObject *obj=dynamic_cast<YUIObject*>(GetParent());

		HWND hwnd=obj->GetHwnd();
		HDC dc=GetDC(hwnd);
		
		Pen myPen(Color(88, 88, 88, 0), 1);
		Graphics gr(dc);
		gr.DrawLine(&myPen,x,y,x2,y2);
		
		ReleaseDC(hwnd,dc);
	}

}