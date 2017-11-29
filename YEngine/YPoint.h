#pragma once
/**************************************************
@brief:point class
@file:YPoint.h
@version:1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-25 17:54:59
**************************************************/

class YUIObject;

class YPoint
{
public:
	YPoint(int x=0,int y=0){this->x=x;this->y=y;}
	int x;
	int y;

	static YPoint MapFromMain(YUIObject* des);

	static YPoint MapFromGlobal(YUIObject* des);

	YPoint &operator +=(const YPoint &pos);

	YPoint &operator -=(const YPoint &pos);
	
};

