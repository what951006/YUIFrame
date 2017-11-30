#include "stdafx.h"
#include "YDialog.h"
#include "YWin32Application.h"


LRESULT CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{

	switch (message) 
	{
	  case WM_DESTROY:
		  {
			  PostQuitMessage(0);
			  YWin32Application::RemoveOneHwnd(hwnd);
			  return 0;
		  }
	  case WM_ERASEBKGND:
		  return 1;
	  case WM_PAINT:
		  {
			  YRect &&re= YWin32Application::GetUIObjectByHWND(hwnd)->GetGeometry();
			  PAINTSTRUCT ps;
			  HDC hdc=BeginPaint(hwnd,&ps);
			  HDC memDc= CreateCompatibleDC(hdc);
			  HBITMAP bitmap= CreateCompatibleBitmap(hdc,re.width,re.height);
			  SelectObject(memDc,bitmap);

			  YWin32Application::GetUIObjectByHWND(hwnd)->DrawWindow(memDc);

			  BitBlt(hdc,0,0,re.width,re.height,memDc,0,0,SRCCOPY);
			 
			  ReleaseDC(hwnd,memDc);
		      DeleteDC(memDc);
			  DeleteObject(bitmap);
			  EndPaint(hwnd,&ps);
		  }
	  case WM_SIZE:
		  {
			  int width  = LOWORD(lParam);
			  int height = HIWORD(lParam);

			  RECT re;
			  GetWindowRect(hwnd,&re);
			  YUIObject*pResult=YWin32Application::GetUIObjectByHWND(hwnd);	
			  if(pResult)
				  YWin32Application::GetEvent()->SendEvent(pResult,pResult,WINDOWS_SIZE_CHANGED,re.left,re.top,width,height);
		  }
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

YDialog::YDialog(HWND hwnd)
	:YUIObject(nullptr,false)
	,m_Parhwnd(hwnd)
{
	m_pParent=nullptr;
	YRegisterClass();
	InitInstance(GetYClassName(),_T("YModal"));
	YUIObject * pUI=YWin32Application::GetUIObjectByHWND(hwnd);
	SetGeometry(pUI->GetGeometry());

	YWin32Application::AddHwnd(GetHwnd(),this);
}

YDialog::~YDialog(void)
{
	
}


void YDialog::YRegisterClass()
{
	HBRUSH BGBru=CreateSolidBrush(RGB(180,180,180));
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= DialogProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= YWin32Application::GetInstance();
	wcex.hIcon			= LoadIcon(YWin32Application::GetInstance(), MAKEINTRESOURCE(IDI_YENGINE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= BGBru;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= GetYClassName();
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);
}


void YDialog::InitInstance(LPCWSTR classname,LPCWSTR title)
{
	m_hRootWnd= CreateWindow(
			classname,
			title,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			m_Parhwnd,
			NULL,
			(HINSTANCE)GetWindowLong(m_Parhwnd, GWL_HINSTANCE),
			NULL);
}

int YDialog::Modal()
{
	EnableWindow(m_Parhwnd,FALSE);
	Show();
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	EnableWindow(m_Parhwnd,TRUE);
	SetForegroundWindow(m_Parhwnd);
	return 1;
}


