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
	//friend class YObject;
public:
	YUIObject(YObject *pParent=nullptr,bool bCreate=true);

	~YUIObject(void);

	void CreateWin(LPCWSTR classname,LPCWSTR title);

	void SetGeometry(int x,int y,int w,int h,bool bMove=true);

	void SetGeometry(const YRect &re,bool bMove=true);

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
	bool InitInstance(LPCWSTR classname,LPCWSTR title);

	void Show(bool bShow=true);

	LPCWSTR GetYClassName(){return _T(YCLASS_NAME);}
	
	YRect GetGeometry(){return m_re;}

	YRect GetGeometryFromMain();

	YPoint GetPos(){return YPoint(m_re.x,m_re.y);}

	HWND GetHwnd(){return m_hRootWnd;}

	bool IsWindow(){return m_bWindow;}

	void SetWindowTitle(const string &str){ SetWindowTextA(GetHwnd(),str.c_str());}

	virtual void DrawWindow(HDC dc);

	virtual void Update() override;

	virtual bool OnEventOccoured(EventObject obj) override;

	virtual void OnMouseDown(const YPoint &point);

	virtual void OnMouseMove(const YPoint &point);

	virtual void OnMouseUp(const YPoint &point);

	virtual void OnMouseEnter(const YPoint &point);

	virtual void OnMouseLeave(const YPoint &point);

	virtual void OnMouseLClicked();

	void AddClickedObserver(){}

	void RemoveClickedObserver(){}

	void NotifyClicked(){}

	
	void SetEnterState(bool bEnter=true){m_bEnter=bEnter; Update();}

	void SetPressedState(bool bPress=true){m_bPress=bPress;Update();}

	bool IsShow(){return m_bShow;}

	int GetWidth(){return m_re.width;}

	int GetHeight(){return m_re.height;}

	int GetX(){return GetParent() ? m_re.x : 0;}
	
	int GetY(){return GetParent() ? m_re.y : 0;}
protected:
	YRect m_re;
	HBRUSH m_BGBru;
	HWND m_hRootWnd;
	bool m_bWindow;
	
	bool m_bEnter;
	bool m_bPress;
	bool m_bShow;
	//be used for enter leave event
};

