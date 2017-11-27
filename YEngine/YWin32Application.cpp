#include "stdafx.h"
#include "YWin32Application.h"


HINSTANCE YWin32Application::s_instance=NULL;
vector<HPMAP> YWin32Application::s_hvec;
bool YWin32Application::s_exit=false;
YWin32Application* YWin32Application::s_pApp=nullptr;
mutex g_mutex;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		break;
	case WM_CREATE:
		for(HPMAP hp : YWin32Application::GetHwndList())
			{
				if(hp.hwnd == hWnd)
					hp.pObj->DrawWindow();
			}
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YObject*pMain=YWin32Application::GetObjectByHWND(hWnd);
			if(pResult)
			   YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_DOWN_L,xPos,yPos);
		}
		break;
	case WM_LBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YObject*pMain=YWin32Application::GetObjectByHWND(hWnd);
			if(pResult)
			{
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_UP_L,xPos,yPos);
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YObject*pMain=YWin32Application::GetObjectByHWND(hWnd);
			if(pResult)
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_DOWN_R,xPos,yPos);
		}
		break;
	case WM_RBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			YObject*pResult= YWin32Application::GetEvent()->GetJudgeChild(hWnd,YPoint(xPos,yPos));
			YObject*pMain=YWin32Application::GetObjectByHWND(hWnd);
			if(pResult)
				YWin32Application::GetEvent()->SendEvent(pResult,pMain,MOUSE_PRESS_UP_R,xPos,yPos);
		}
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc=BeginPaint(hWnd,&ps);
			for(HPMAP hp:YWin32Application::GetHwndList())
			{
				if(hp.hwnd == hWnd)
					hp.pObj->DrawWindow();
			}    
			EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		if(YWin32Application::GetHwndList()[0].hwnd==hWnd)
			YWin32Application::QuitApp();
		YWin32Application::RemoveOneHwnd(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




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
	MSG msg;
	while (!s_exit)
	{
		g_mutex.lock();
		for(HPMAP hp:s_hvec)
			if (PeekMessage (&msg,hp.hwnd, 0, 0, PM_REMOVE)) 
			{ 
				if (msg.message == WM_QUIT)
					return 0; 
				TranslateMessage (&msg) ; 
				DispatchMessage (&msg) ; 
			} 
			else 
			{ 
				Update();
			} 
		g_mutex.unlock();
		Sleep(10);
	}
	return 1;
}



void YWin32Application::Update()
{
	YObject::Update();
	/*Here is your code !!*/
	for(HPMAP hp : s_hvec)
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
YObject* YWin32Application::GetObjectByHWND(HWND hwnd)
{
	for(auto hp  :  s_hvec)
	{
		if(hp.hwnd==hwnd)
			return hp.pObj;
	}
	return nullptr;
}