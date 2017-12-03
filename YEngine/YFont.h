#pragma once

/**************************************************
@brief:the font class of YUIFrame
@file:YFont.h
@version:1.0
@company:casino
@author:yantao
@email:what951006@163.com
@time:2017-12-03 17:13:04
**************************************************/

class YFont
{
public:
	YFont(HDC &dc);
	~YFont(void);

	void SetFontFamily(const string &str);

	void SetFontSize(int size);

	int GetStrWidth(const string &str);

	int GetFontHeight(){return m_logfont.lfHeight;}


	LOGFONT   m_logfont;
	HFONT   m_hFont ;
	HDC m_dc;
};

