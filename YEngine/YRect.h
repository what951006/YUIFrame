#pragma once
#include "YPoint.h"
/**************************************************
@brief:rect class
@file:YRect.h
@version:1.0
@company:casino
@author:yantao
@email:what951006@163.com
@time:2017-11-25 14:14:47
**************************************************/

struct YRect
{
public:
	int x;
	int y;
	int width;
	int height;

	YRect(int x=0,int y=0,int w=0,int h=0)
	{
		this->x	=x;
		this->y	=y;
		this->width=w;
		this->height=h;
	}

	bool IsContained(const YPoint &pos)
	{
		return x <= pos.x && pos.x <= x+width && y <= pos.y && pos.y<= y+height; 
	}
};

