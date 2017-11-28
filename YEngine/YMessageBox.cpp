#include "stdafx.h"
#include "YMessageBox.h"
#include "YUIObject.h"


YMessageBox::YMessageBox(void)
{
}


YMessageBox::~YMessageBox(void)
{
}

YMB_TYPE YMessageBox::Show(YUIObject*pParent)
{
	YUIObject pMessage;
	pMessage.setClassName(L"YUIMessageBox");
	pMessage.YRegisterClass();
	pMessage.InitInstance();

	pMessage.SetGeometry(100,100,100,100);

	 EnableWindow(pParent->GetHwnd(), FALSE);
	MSG msg;
    while (GetMessage(&msg, pMessage.GetHwnd(), 0, 0)) 
	{
	    TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    EnableWindow(pParent->GetHwnd(), TRUE);
    SetForegroundWindow(pParent->GetHwnd());

	return YMB_OK;
}
