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

YMB_TYPE YMessageBox::Show(YUIObject*pParent)
{
	YDialog dlg(pParent->GetHwnd());
	//YUIObject *pobj=YWin32Application::GetUIObjectByHWND(pParent->GetHwnd());
	YPoint &&pos=YPoint::MapFromGlobal(pParent);
	YRect &&re=pParent->GetGeometry();
	dlg.SetGeometry(pos.x+(re.width-200)/2,pos.y+(re.height-100)/2,200,100);
	dlg.Modal();
	return YMB_OK;
}
