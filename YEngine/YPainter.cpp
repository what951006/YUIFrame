#include "stdafx.h"
#include "YPainter.h"
#include "YUIObject.h"


YPainter::YPainter(HDC&dc,YUIObject*pParent)
	:m_dc(dc)
	,m_pParent(pParent)
	,m_pPen(NULL)
	,m_tranValue(255)
{
	//if it is window,show nothing
	YRect &&re = pParent->GetGeometryFromMain();
	m_memDC=CreateCompatibleDC(dc);
	SetBkMode(m_memDC,TRANSPARENT);
	m_bitmap=CreateCompatibleBitmap(dc,re.width,re.height);
	SelectObject(m_memDC,m_bitmap);
	BitBlt(m_memDC,0,0,re.width,re.height,m_dc,re.x,re.y,SRCCOPY);
	

	m_pGraphic = new Graphics(m_memDC);
	m_pFont = new YFont(m_memDC);

}
	


YPainter::~YPainter(void)
{
	BLENDFUNCTION bn;
	bn.AlphaFormat = 0;
	bn.BlendFlags = 0;
	bn.BlendOp = AC_SRC_OVER;
	bn.SourceConstantAlpha =m_tranValue; //透明度设置，0为不透明；255为完全透明

	AlphaBlend(m_dc,m_pParent->GetX(),m_pParent->GetY(),m_pParent->GetWidth(),m_pParent->GetHeight(),m_memDC,0,0,m_pParent->GetWidth(),m_pParent->GetHeight(),bn);  
	DeleteDC(m_memDC);
	DeleteObject(m_bitmap);

	delete m_pPen;
	delete m_pGraphic;
	delete m_pFont;
}

void YPainter::SetFont(const YFont &font)
{
	delete m_pFont;
	m_pFont=new YFont(m_memDC);
	*m_pFont=font;
}

void YPainter::SetTransparent(int value)
{
	m_tranValue=value;
}

void YPainter::SetFontColor(int r, int g ,int b)
{
	SetTextColor(m_memDC,RGB(r,g,b));
}


void YPainter::DrawLine(int x,int y,int x2,int y2)
{
	m_pGraphic->DrawLine(m_pPen,x,y,x2,y2);
}

void YPainter::DrawImage(Image &image,int x,int y,int w,int h)
{
	m_pGraphic->SetInterpolationMode(Gdiplus::InterpolationModeDefault); 
	m_pGraphic->DrawImage(&image, x,y,w,h); 

}

void YPainter::FillRect(const SolidBrush&br,int x,int y,int w,int h)
{
	m_pGraphic->FillRectangle(&br,x,y,w,h);

}

void YPainter::FillRect(const SolidBrush&br,const YRect &re)
{
	m_pGraphic->FillRectangle(&br,re.x,re.y,re.width,re.height);
}

void YPainter::DrawText(const string &str,int x, int y)
{
	RECT re;
	re.left=x;
	re.right=x+200;
	re.top=y;
	re.bottom=y+200;
	DrawTextA(m_memDC,str.c_str(),str.length(),&re, DT_SINGLELINE | DT_WORD_ELLIPSIS);//DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS
}
