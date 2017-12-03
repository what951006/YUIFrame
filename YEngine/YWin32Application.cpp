#include "stdafx.h"
#include "YWin32Application.h"
#include "YUIObject.h"

HINSTANCE YWin32Application::s_instance=NULL;
vector<HPMAP> YWin32Application::s_hvec;
YWin32Application* YWin32Application::s_pApp=nullptr;
mutex g_mutex;


YUIObject *s_preMove=nullptr;	//previous uiobject that mouse is now on
YUIObject *s_prePress=nullptr;	//previous uiobject that mouse was pressed
BOOL s_bMouseTracking = FALSE; 


YWin32Application::YWin32Application(HINSTANCE instance)
	:m_Event(this)
{
	s_instance=instance;
	s_pApp=this;
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
}

YWin32Application::~YWin32Application(void)
{
	GdiplusShutdown(m_gdiplusToken);
}

int YWin32Application::Run()
{

	AllocConsole() ;

	MSG msg;
	while(GetMessage (&msg,NULL, 0, 0)) 
	{
		if(WM_QUIT==msg.message)
			break;

		TranslateMessage (&msg); 
		DispatchMessage (&msg); 
	}
	return 1;
}



void YWin32Application::Update()
{
	YObject::Update();
	/*Here is your code !!*/
	//lock_guard<mutex> lg(g_mutex);
	for(auto hp : s_hvec)
		hp.pObj->Update();
}


void YWin32Application::RemoveOneHwnd(HWND hwnd)
{
	lock_guard<mutex> lg(g_mutex);
	vector<HPMAP>::iterator it=s_hvec.begin();
	for(;it != s_hvec.end();it++)
	{
		if(hwnd == (*it).hwnd)
		{
			s_hvec.erase(it);
			break;
		}
	}
}

YUIObject* YWin32Application::GetUIObjectByHWND(HWND hwnd)
{
	lock_guard<mutex> lg(g_mutex);
	for(auto hp  :  s_hvec)
		if(hp.hwnd==hwnd)
			return hp.pObj;

	return nullptr;
}