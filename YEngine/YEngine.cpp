// YEngine.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "YEngine.h"
#include "YWin32Application.h"
#include "MainWindow.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	YWin32Application app(hInstance);

	MainWindow mw;
	mw.setClassName(L"YUIObject");
	mw.YRegisterClass();
	mw.InitInstance();
	YWin32Application::AddHwnd(mw.GetHwnd(),&mw);

	mw.SetGeometry(800,800,400,400);
	mw.Show();

	return app.Run();
}