#pragma once
/**************************************************
@brief: the UI object of all UI windows
@file: YUIObject.h
@version:v1.0
@company:casino.ltd
@author:yantao
@email:what951006@163.com
@time:2017-11-20 13:01:40
**************************************************/
#include "YObject.h"
#include "YRect.h"
#include "YPoint.h"

class YUIObject :public YObject
{
	friend class YObject;
public:
	YUIObject(YObject *pParent=nullptr);

	~YUIObject(void);

	void SetGeometry(int x,int y,int w,int h,bool bMove=true);

	/*
	@brief:Register class name
	@param:
	@return:
	*/
	void YRegisterClass();
	
	/*
	@brief:initialize instance
	@param:
	@return:true successful ,false failed
	*/
	bool InitInstance();

	void Show(bool bShow=true);

	virtual void DrawWindow(HDC &dc);

	LPCWSTR GetAppClassName(){return m_className;}

	void setClassName(LPCWSTR lpwstr){swprintf(m_className,sizeof(m_className), lpwstr);}

	YRect GetGeometry(){return m_re;}

	YRect GetGeometryFromMain();

	YPoint GetPos(){return YPoint(m_re.x,m_re.y);}

	HWND GetHwnd(){return m_hRootWnd;}

	bool IsWindow(){return m_bWindow;}


	virtual bool OnEventOccoured(EventObject obj) override;

	virtual void OnMouseDown(const YPoint point){}

	virtual void OnMouseMove(const YPoint point){}

	virtual void OnMouseUp(const YPoint point){}
private:
	YRect m_re;
	HBRUSH m_BGBru;
	HWND m_hRootWnd;
	bool m_bWindow;

	wchar_t m_className[24];
};

