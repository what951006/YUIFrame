#include "stdafx.h"
#include "YFont.h"


YFont::YFont(HDC &dc)
	:m_dc(dc)
{
	ZeroMemory(&m_logfont,   sizeof(LOGFONT));   
	m_logfont.lfCharSet   =   GB2312_CHARSET;   
	m_logfont.lfHeight   =  12;      //设置字体的大小
	SetFontFamily("微软雅黑");
	m_hFont  =  CreateFontIndirect(&m_logfont);   
	SelectObject(dc,m_hFont);

	
}


YFont::~YFont(void)
{
	DeleteObject(m_hFont);
}

void YFont::SetFontFamily(const string &str)
{
	wsprintf(m_logfont.lfFaceName,L"%s",str.c_str());
}

int YFont::GetStrWidth(const string &str)
{
	TEXTMETRIC metric;
	GetTextMetrics(m_dc,&metric);
	return metric.tmAveCharWidth *str.length();
}

