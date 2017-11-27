#pragma once
#include "YObject.h"
/**************************************************
@brief:event class!
@file:YEvent.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-20 15:32:28
**************************************************/
class YPoint;
struct YRect;



class YEvent :public YObject
{
public:
	YEvent(YObject*pParent);

	~YEvent(void);

	void SendEvent(YObject*obj,YObject*pMain,EventType evtype,int x=0,int y=0);

	void Update();

	YObject* GetJudgeChild(HWND hwnd,const YPoint pos);

	
private:

	YObject* FindObjHelper(YRect re,YObject*,const YPoint);

	queue<EventObject> m_que;
};















