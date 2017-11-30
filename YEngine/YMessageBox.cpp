#include "stdafx.h"
#include "YMessageBox.h"
#include "YUIObject.h"
#include "YWin32Application.h"
#include "YDialog.h"
YMessageBox::YMessageBox(void)
{
}


YMessageBox::~YMessageBox(void)
{
}

bool YMessageBox::OnEventOccoured(EventObject obj)
{
	return YUIObject::OnEventOccoured(obj);
}

YMB_TYPE YMessageBox::Show(YUIObject*pParent)
{
	HWND &&hwnd=pParent->GetHwnd();
	YDialog dlg(hwnd);
	YUIObject *pMainDlg=YWin32Application::GetUIObjectByHWND(hwnd);
	YRect &&re=pMainDlg->GetGeometry();
	dlg.SetGeometry(re.x+(re.width-300)/2,re.y+(re.height-200)/2,300,200);
	dlg.Modal();
	return YMB_OK;
}
