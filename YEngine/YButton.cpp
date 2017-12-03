#include "stdafx.h"
#include "YButton.h"
#include "YPainter.h"
#include "YMessageBox.h"
#include "YButton.h"

YButton::YButton(const string &str,YUIObject*obj)
	:YUIObject(obj)
	,m_strText(str)
{
	m_bEnter=false;
	m_bPress=false;
	
}


YButton::~YButton(void)
{

}

void YButton::SetText(const string &str)
{
	m_strText=str;
	Update();
}

/*
	first thing is to paint parent and  second painting children
*/
void YButton::DrawWindow(HDC dc)
{
	YPainter p(dc,this);
	Pen pen(Color( 255,55,55,55));
	p.SetPen(pen);
	
	p.DrawLine(0,0,m_re.width,0);
	p.DrawLine(m_re.width-1,0,m_re.width-1,m_re.height);
	p.DrawLine(m_re.width-1,m_re.height-1,0,m_re.height-1);
	p.DrawLine(0,m_re.height,0,0);

	if(!m_bEnter)
	{
		SolidBrush br(Color(188,188,188));
		p.FillRect(br,0,0,GetWidth(),GetHeight());
	}
	else
	{
		SolidBrush br(Color(155,155,155));
		p.FillRect(br,0,0,GetWidth(),GetHeight());
	}

	if(m_bPress)
	{
		SolidBrush br(Color(0,120,200));
		p.FillRect(br,0,0,GetWidth(),GetHeight());
	}

	YFont &font=p.GetFont();
	int width=font.GetStrWidth(m_strText);
	p.SetFontColor(66,66,66);
	p.DrawText(m_strText,(m_re.width-width)/2,(m_re.height-font.GetFontHeight())/2);

	YUIObject::DrawWindow(dc);
}

void YButton::OnMouseLClicked()
{
	//YMessageBox::Show(this);
}
